/* Copyright 2013, Ludwig-Maximilians Universität München,
   Authors: Tobias Schlüter & Johannes Rauch

   This file is part of GENFIT.

   GENFIT is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GENFIT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with GENFIT.  If not, see <http://www.gnu.org/licenses/>.
 */

/* This implements the simple Kalman fitter with no reference track
   that uses the stateSeed only until it forgets about it after the
   first few hits.  */

#include "KalmanFitter.h"

#include "Exception.h"
#include "KalmanFitterInfo.h"
#include "KalmanFitStatus.h"
#include "Track.h"
#include "TrackPoint.h"
#include "Tools.h"

#include <Math/ProbFunc.h>
#include <TDecompChol.h>
#include <TMatrixDSymEigen.h>
#include <algorithm>

using namespace genfit;


bool KalmanFitter::fitTrack(Track* tr, const AbsTrackRep* rep,
    double& chi2, double& ndf,
    int startId, int endId, int& nFailedHits)
{

  if (multipleMeasurementHandling_ == unweightedClosestToReference ||
      multipleMeasurementHandling_ == weightedClosestToReference ||
      multipleMeasurementHandling_ == unweightedClosestToReferenceWire ||
      multipleMeasurementHandling_ == weightedClosestToReferenceWire) {
    Exception exc("KalmanFitter::fitTrack ==> cannot use (un)weightedClosestToReference(Wire) as multiple measurement handling.",__LINE__,__FILE__);
    exc.setFatal();
    throw exc;
  }

  if (startId < 0)
    startId += tr->getNumPointsWithMeasurement();
  if (endId < 0)
    endId += tr->getNumPointsWithMeasurement();

  int direction(1);
  if (endId < startId)
    direction = -1;

  chi2 = 0;
  ndf = -1. * rep->getDim();

  nFailedHits = 0;

  if (debugLvl_ > 0) {
    std::cout << tr->getNumPointsWithMeasurement() << " TrackPoints w/ measurement in this track." << std::endl;
  }
  for (int i = startId; ; i+=direction) {
    TrackPoint *tp = tr->getPointWithMeasurement(i);
    assert(direction == +1 || direction == -1);

    if (debugLvl_ > 0) {
      std::cout << " process TrackPoint nr. " << i << " (" << tp << ")\n";
    }

    try {
      processTrackPoint(tp, rep, chi2, ndf, direction);
    }
    catch (Exception& e) {
      std::cerr << e.what();

      ++nFailedHits;
      if (maxFailedHits_<0 || nFailedHits <= maxFailedHits_) {
        tr->getPoint(i)->deleteFitterInfo(rep);

        if (i == endId)
          break;

        if (debugLvl_ > 0)
          std::cout << "There was an exception, try to continue with next TrackPoint " << i+direction << " \n";

        continue;
      }

      return false;
    }

    if (i == endId)
      break;
  }

  return true;
}


void KalmanFitter::processTrackWithRep(Track* tr, const AbsTrackRep* rep, bool)
{

  if (tr->getFitStatus(rep) != NULL && tr->getFitStatus(rep)->isTrackPruned()) {
    Exception exc("KalmanFitter::processTrack: Cannot process pruned track!", __LINE__,__FILE__);
    throw exc;
  }

  TrackPoint* trackPoint = tr->getPointWithMeasurement(0);

  if (trackPoint->hasFitterInfo(rep) &&
      dynamic_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(rep)) != NULL &&
      static_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(rep))->hasUpdate(-1)) {
    MeasuredStateOnPlane* update = static_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(rep))->getUpdate(-1);
    currentState_.reset(new MeasuredStateOnPlane(*update));
    if (debugLvl_ > 0)
      std::cout << "take backward update of previous iteration as seed \n";
  }
  if (rep != tr->getCardinalRep() &&
      trackPoint->hasFitterInfo(tr->getCardinalRep()) &&
      dynamic_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(tr->getCardinalRep())) != NULL &&
      static_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(tr->getCardinalRep()))->hasPredictionsAndUpdates() ) {
    if (debugLvl_ > 0)
      std::cout << "take smoothed state of cardinal rep fit as seed \n";
    TVector3 pos, mom;
    TMatrixDSym cov;
    const MeasuredStateOnPlane& fittedState = static_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(tr->getCardinalRep()))->getFittedState(true);
    tr->getCardinalRep()->getPosMomCov(fittedState, pos, mom, cov);
    currentState_.reset(new MeasuredStateOnPlane(rep));
    rep->setPosMomCov(*currentState_, pos, mom, cov);
    rep->setQop(*currentState_, tr->getCardinalRep()->getQop(fittedState));
  }
  else {
    currentState_.reset(new MeasuredStateOnPlane(rep));
    rep->setTime(*currentState_, tr->getTimeSeed());
    rep->setPosMomCov(*currentState_, tr->getStateSeed(), tr->getCovSeed());
    if (debugLvl_ > 0)
      std::cout << "take seed state of track as seed \n";
  }

  // Only after we have linearly propagated the error into the TrackRep can we
  // blow up the error in good faith.
  currentState_->blowUpCov(blowUpFactor_, resetOffDiagonals_, blowUpMaxVal_);

  double oldChi2FW(1.e6);
  double oldChi2BW(1.e6);
  double oldPvalFW(0.);

  double oldPvalBW = 0.;
  double chi2FW(0), ndfFW(0);
  double chi2BW(0), ndfBW(0);

  int nFailedHitsForward(0), nFailedHitsBackward(0);


  KalmanFitStatus* status = new KalmanFitStatus();
  tr->setFitStatus(status, rep);

  unsigned int nIt = 0;
  for(;;) {
    try {
      if (debugLvl_ > 0) {
        std::cout << "\033[1;21mstate pre" << std::endl;
        currentState_->Print();
        std::cout << "\033[0mfitting" << std::endl;
      }

      if (!fitTrack(tr, rep, chi2FW, ndfFW, 0, -1, nFailedHitsForward)) {
        status->setIsFitted(false);
        status->setIsFitConvergedFully(false);
        status->setIsFitConvergedPartially(false);
        status->setNFailedPoints(nFailedHitsForward);
        return;
      }

      if (debugLvl_ > 0) {
        std::cout << "\033[1;21mstate post forward" << std::endl;
        currentState_->Print();
        std::cout << "\033[0m";
      }

      // Backwards iteration:
      currentState_->blowUpCov(blowUpFactor_, resetOffDiagonals_, blowUpMaxVal_);  // blow up cov

      if (!fitTrack(tr, rep, chi2BW, ndfBW, -1, 0, nFailedHitsBackward)) {
        status->setIsFitted(false);
        status->setIsFitConvergedFully(false);
        status->setIsFitConvergedPartially(false);
        status->setNFailedPoints(nFailedHitsBackward);
        return;
      }

      if (debugLvl_ > 0) {
        std::cout << "\033[1;21mstate post backward" << std::endl;
        currentState_->Print();
        std::cout << "\033[0m";

        std::cout << "old chi2s: " << oldChi2BW << ", " << oldChi2FW
            << " new chi2s: " << chi2BW << ", " << chi2FW
            << " oldPvals " << oldPvalFW << ", " << oldPvalBW << std::endl;
      }
      ++nIt;

      double PvalBW = std::max(0.,ROOT::Math::chisquared_cdf_c(chi2BW, ndfBW));
      double PvalFW = (debugLvl_ > 0) ? std::max(0.,ROOT::Math::chisquared_cdf_c(chi2FW, ndfFW)) : 0; // Don't calculate if not debugging as this function potentially takes a lot of time.
      // See if p-value only changed little.  If the initial
      // parameters are very far off, initial chi^2 and the chi^2
      // after the first iteration will be both very close to zero, so
      // we need to force at least two iterations here.  Convergence
      // doesn't make much sense before running twice anyway.
      bool converged(false);
      bool finished(false);
      if (nIt >= minIterations_ && fabs(oldPvalBW - PvalBW) < deltaPval_)  {
        // if pVal ~ 0, check if chi2 has changed significantly
        if (chi2BW == 0) {
          finished = false;
        }
        else if (fabs(1 - fabs(oldChi2BW / chi2BW)) > relChi2Change_) {
          finished = false;
        }
        else {
          finished = true;
          converged = true;
        }

        if (PvalBW == 0.)
          converged = false;
      }

      if (finished) {
        if (debugLvl_ > 0) {
          std::cout << "Fit is finished! ";
          if(converged)
            std::cout << "Fit is converged! ";
          std::cout << "\n";
        }

        if (nFailedHitsForward == 0 && nFailedHitsBackward == 0)
          status->setIsFitConvergedFully(converged);
        else
          status->setIsFitConvergedFully(false);

        status->setIsFitConvergedPartially(converged);

        status->setNFailedPoints(std::max(nFailedHitsForward, nFailedHitsBackward));

        break;
      }
      else {
        oldPvalBW = PvalBW;
        oldChi2BW = chi2BW;
        if (debugLvl_ > 0) {
          oldPvalFW = PvalFW;
          oldChi2FW = chi2FW;
        }
        currentState_->blowUpCov(blowUpFactor_, resetOffDiagonals_, blowUpMaxVal_);  // blow up cov
      }

      if (nIt >= maxIterations_) {
        if (debugLvl_ > 0)
          std::cout << "KalmanFitter::number of max iterations reached!\n";
        break;
      }
    }
    catch(Exception& e) { // should not happen, but I leave it in for safety
      std::cerr << e.what();
      status->setIsFitted(false);
      status->setIsFitConvergedFully(false);
      status->setIsFitConvergedPartially(false);
      status->setNFailedPoints(std::max(nFailedHitsForward, nFailedHitsBackward));
      return;
    }
  }

  status->setIsFitted();
  double charge(0);
  TrackPoint* tp = tr->getPointWithMeasurementAndFitterInfo(0, rep);
  if (tp != NULL) {
    if (static_cast<KalmanFitterInfo*>(tp->getFitterInfo(rep))->hasBackwardUpdate())
      charge = static_cast<KalmanFitterInfo*>(tp->getFitterInfo(rep))->getBackwardUpdate()->getCharge();
  }
  status->setNFailedPoints(std::max(nFailedHitsForward, nFailedHitsBackward));
  status->setCharge(charge);
  status->setNumIterations(nIt);
  status->setForwardChi2(chi2FW);
  status->setBackwardChi2(chi2BW);
  status->setForwardNdf(std::max(0., ndfFW));
  status->setBackwardNdf(std::max(0., ndfBW));
}


void
KalmanFitter::processTrackPartially(Track* tr, const AbsTrackRep* rep, int startId, int endId) {

  if (tr->getFitStatus(rep) != NULL && tr->getFitStatus(rep)->isTrackPruned()) {
    Exception exc("KalmanFitter::processTrack: Cannot process pruned track!", __LINE__,__FILE__);
    throw exc;
  }

  if (startId < 0)
    startId += tr->getNumPointsWithMeasurement();
  if (endId < 0)
    endId += tr->getNumPointsWithMeasurement();

  int direction(1);
  if (endId < startId)
    direction = -1;


  TrackPoint* trackPoint = tr->getPointWithMeasurement(startId);
  TrackPoint* prevTrackPoint(NULL);


  if (direction == 1 && startId > 0)
    prevTrackPoint = tr->getPointWithMeasurement(startId - 1);
  else if (direction == -1 && startId < (int)tr->getNumPointsWithMeasurement() - 1)
    prevTrackPoint = tr->getPointWithMeasurement(startId + 1);


  if (prevTrackPoint != NULL &&
      prevTrackPoint->hasFitterInfo(rep) &&
      dynamic_cast<KalmanFitterInfo*>(prevTrackPoint->getFitterInfo(rep)) != NULL &&
      static_cast<KalmanFitterInfo*>(prevTrackPoint->getFitterInfo(rep))->hasUpdate(direction)) {
    currentState_.reset(new MeasuredStateOnPlane(*(static_cast<KalmanFitterInfo*>(prevTrackPoint->getFitterInfo(rep))->getUpdate(direction))));
    if (debugLvl_ > 0)
      std::cout << "take update of previous fitter info as seed \n";
  }
  else if (rep != tr->getCardinalRep() &&
      trackPoint->hasFitterInfo(tr->getCardinalRep()) &&
      dynamic_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(tr->getCardinalRep())) != NULL &&
      static_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(tr->getCardinalRep()))->hasPredictionsAndUpdates() ) {
    if (debugLvl_ > 0)
      std::cout << "take smoothed state of cardinal rep fit as seed \n";
    TVector3 pos, mom;
    TMatrixDSym cov;
    const MeasuredStateOnPlane& fittedState = static_cast<KalmanFitterInfo*>(trackPoint->getFitterInfo(tr->getCardinalRep()))->getFittedState(true);
    tr->getCardinalRep()->getPosMomCov(fittedState, pos, mom, cov);
    currentState_.reset(new MeasuredStateOnPlane(rep));
    rep->setPosMomCov(*currentState_, pos, mom, cov);
    rep->setQop(*currentState_, tr->getCardinalRep()->getQop(fittedState));
  }
  else {
    currentState_.reset(new MeasuredStateOnPlane(rep));
    rep->setTime(*currentState_, tr->getTimeSeed());
    rep->setPosMomCov(*currentState_, tr->getStateSeed(), tr->getCovSeed());
    if (debugLvl_ > 0)
      std::cout << "take seed of track as seed \n";
  }

  // if at first or last hit, blow up
  if (startId == 0 || startId == (int)tr->getNumPointsWithMeasurement() - 1) {
    currentState_->blowUpCov(blowUpFactor_, resetOffDiagonals_, blowUpMaxVal_);
    if (debugLvl_ > 0)
      std::cout << "blow up seed \n";
  }

  if (debugLvl_ > 0) {
    std::cout << "\033[1;21mstate pre" << std::endl;
    currentState_->Print();
    std::cout << "\033[0mfitting" << std::endl;
  }

  double chi2, ndf;
  int nFailedHits;
  fitTrack(tr, rep, chi2, ndf, startId, endId, nFailedHits); // return value has no consequences here

}


void
KalmanFitter::processTrackPoint(TrackPoint* tp,
    const AbsTrackRep* rep, double& chi2, double& ndf, int direction)
{
  assert(direction == -1 || direction == +1);

  if (!tp->hasRawMeasurements())
    return;

  bool newFi(!tp->hasFitterInfo(rep));

  KalmanFitterInfo* fi;
  if (newFi) {
    fi = new KalmanFitterInfo(tp, rep);
    tp->setFitterInfo(fi);
  }
  else
    fi = static_cast<KalmanFitterInfo*>(tp->getFitterInfo(rep));

  SharedPlanePtr plane;
  bool oldWeightsFixed(false);
  std::vector<double> oldWeights;

  // construct measurementsOnPlane if forward fit
  if (newFi) {
    // remember old weights
    oldWeights = fi->getWeights();
    oldWeightsFixed = fi->areWeightsFixed();

    // delete outdated stuff
    fi->deleteForwardInfo();
    fi->deleteBackwardInfo();
    fi->deleteMeasurementInfo();

    // construct plane with first measurement
    const std::vector< genfit::AbsMeasurement* >& rawMeasurements =  tp->getRawMeasurements();
    plane = rawMeasurements[0]->constructPlane(*currentState_);
  }
  else
    plane = fi->getPlane();

  double extLen = rep->extrapolateToPlane(*currentState_, plane);
  if (debugLvl_ > 0) {
    std::cout << "extrapolated by " << extLen << std::endl;
  }
  fi->setPrediction(currentState_->clone(), direction);
  MeasuredStateOnPlane *state = fi->getPrediction(direction);

  // construct new MeasurementsOnPlane
  if (newFi) {
    const std::vector< genfit::AbsMeasurement* >& rawMeasurements =  tp->getRawMeasurements();
    for (std::vector< genfit::AbsMeasurement* >::const_iterator it = rawMeasurements.begin(); it != rawMeasurements.end(); ++it) {
      fi->addMeasurementsOnPlane((*it)->constructMeasurementsOnPlane(*state));
    }
    if (oldWeights.size() == fi->getNumMeasurements()) {
      fi->setWeights(oldWeights);
      fi->fixWeights(oldWeightsFixed);
      if (debugLvl_ > 0) {
        std::cout << "set old weights \n";
      }
    }
    assert(fi->getPlane() == plane);
    assert(fi->checkConsistency());
  }

  if (debugLvl_ > 0) {
    std::cout << "its plane is at R = " << plane->getO().Perp()
	          << " with normal pointing along (" << plane->getNormal().X() << ", " << plane->getNormal().Y() << ", " << plane->getNormal().Z() << ")" << std::endl;
  }

  TVectorD stateVector(state->getState());
  TMatrixDSym cov(state->getCov());
  double chi2inc = 0;
  double ndfInc = 0;

  if (!squareRootFormalism_) {
    // update(s)
    const std::vector<MeasurementOnPlane *>& measurements = getMeasurements(fi, tp, direction);
    for (std::vector<MeasurementOnPlane *>::const_iterator it = measurements.begin(); it != measurements.end(); ++it) {
      const MeasurementOnPlane& mOnPlane = **it;
      const double weight = mOnPlane.getWeight();

      if (debugLvl_ > 0) {
        std::cout << "Weight of measurement: " << weight << "\n";
      }

      if (!canIgnoreWeights() && weight <= 1.01E-10) {
        if (debugLvl_ > 0) {
          std::cout << "Weight of measurement is almost 0, continue ... \n";
        }
        continue;
      }

      const TVectorD& measurement(mOnPlane.getState());
      const AbsHMatrix* H(mOnPlane.getHMatrix());
      // (weighted) cov
      const TMatrixDSym& V((!canIgnoreWeights() && weight < 0.99999) ?
          1./weight * mOnPlane.getCov() :
          mOnPlane.getCov());
      if (debugLvl_ > 1) {
        std::cout << "\033[31m";
        std::cout << "State prediction: "; stateVector.Print();
        std::cout << "Cov prediction: "; state->getCov().Print();
        std::cout << "\033[0m";
        std::cout << "\033[34m";
        std::cout << "measurement: "; measurement.Print();
        std::cout << "measurement covariance V: "; V.Print();
        //cov.Print();
        //measurement.Print();
      }

      TVectorD res(measurement - H->Hv(stateVector));
      if (debugLvl_ > 1) {
        std::cout << "Residual = (" << res(0);
        if (res.GetNrows() > 1)
          std::cout << ", " << res(1);
        std::cout << ")" << std::endl;
        std::cout << "\033[0m";
      }
      // If hit, do Kalman algebra.

      {
        // calculate kalman gain ------------------------------
        // calculate covsum (V + HCH^T) and invert
        TMatrixDSym covSumInv(cov);
        H->HMHt(covSumInv);
        covSumInv += V;
        tools::invertMatrix(covSumInv);

        TMatrixD CHt(H->MHt(cov));
        TVectorD update(TMatrixD(CHt, TMatrixD::kMult, covSumInv) * res);
        //TMatrixD(CHt, TMatrixD::kMult, covSumInv).Print();

        if (debugLvl_ > 1) {
          //std::cout << "STATUS:" << std::endl;
          //stateVector.Print();
          std::cout << "\033[32m";
          std::cout << "Update: "; update.Print();
          std::cout << "\033[0m";
          //cov.Print();
        }

        stateVector += update;
        covSumInv.Similarity(CHt); // with (C H^T)^T = H C^T = H C  (C is symmetric)
        cov -= covSumInv;
      }

      if (debugLvl_ > 1) {
        std::cout << "\033[32m";
        std::cout << "updated state: "; stateVector.Print();
        std::cout << "updated cov: "; cov.Print();
      }

      TVectorD resNew(measurement - H->Hv(stateVector));
      if (debugLvl_ > 1) {
        std::cout << "Residual New = (" << resNew(0);

        if (resNew.GetNrows() > 1)
          std::cout << ", " << resNew(1);
        std::cout << ")" << std::endl;
        std::cout << "\033[0m";
      }

      // Calculate chi²
      TMatrixDSym HCHt(cov);
      H->HMHt(HCHt);
      HCHt -= V;
      HCHt *= -1;

      tools::invertMatrix(HCHt);

      chi2inc += HCHt.Similarity(resNew);

      if (!canIgnoreWeights()) {
        ndfInc += weight * measurement.GetNrows();
      }
      else
        ndfInc += measurement.GetNrows();

      if (debugLvl_ > 0) {
        std::cout << "chi² increment = " << chi2inc << std::endl;
      }
    } // end loop over measurements
  } else {
    // The square-root formalism is applied only to the updates, not
    // the prediction even though the addition of the noise covariance
    // (which in implicit in the extrapolation) is probably the most
    // fragile part of the numerical procedure.  This would require
    // calculating the transport matrices also here, which would be
    // possible but is not done, as this is not the preferred form of
    // the Kalman Fitter, anyway.

    TDecompChol decompCov(cov);
    decompCov.Decompose();
    TMatrixD S(decompCov.GetU());

    const std::vector<MeasurementOnPlane *>& measurements = getMeasurements(fi, tp, direction);
    for (std::vector<MeasurementOnPlane *>::const_iterator it = measurements.begin(); it != measurements.end(); ++it) {
      const MeasurementOnPlane& mOnPlane = **it;
      const double weight = mOnPlane.getWeight();

      if (debugLvl_ > 0) {
        std::cout << "Weight of measurement: " << weight << "\n";
      }

      if (!canIgnoreWeights() && weight <= 1.01E-10) {
        if (debugLvl_ > 0) {
          std::cout << "Weight of measurement is almost 0, continue ... \n";
        }
        continue;
      }

      const TVectorD& measurement(mOnPlane.getState());
      const AbsHMatrix* H(mOnPlane.getHMatrix());
      // (weighted) cov
      const TMatrixDSym& V((!canIgnoreWeights() && weight < 0.99999) ?
          1./weight * mOnPlane.getCov() :
          mOnPlane.getCov());
      if (debugLvl_ > 1) {
        std::cout << "\033[31m";
        std::cout << "State prediction: "; stateVector.Print();
        std::cout << "Cov prediction: "; state->getCov().Print();
        std::cout << "\033[0m";
        std::cout << "\033[34m";
        std::cout << "measurement: "; measurement.Print();
        std::cout << "measurement covariance V: "; V.Print();
        //cov.Print();
        //measurement.Print();
      }

      TVectorD res(measurement - H->Hv(stateVector));
      if (debugLvl_ > 1) {
        std::cout << "Residual = (" << res(0);
        if (res.GetNrows() > 1)
          std::cout << ", " << res(1);
        std::cout << ")" << std::endl;
        std::cout << "\033[0m";
      }

      TDecompChol decompR(V);
      decompR.Decompose();
      const TMatrixD& R(decompR.GetU());

      TVectorD update(stateVector.GetNrows());
      tools::kalmanUpdateSqrt(S, res, R, H,
          update, S);
      stateVector += update;

      // Square root is such that
      //    cov = TMatrixDSym(TMatrixDSym::kAtA, S);

      if (debugLvl_ > 1) {
        std::cout << "\033[32m";
        std::cout << "updated state: "; stateVector.Print();
        std::cout << "updated cov: "; TMatrixDSym(TMatrixDSym::kAtA, S).Print() ;
      }

      res -= H->Hv(update);
      if (debugLvl_ > 1) {
        std::cout << "Residual New = (" << res(0);

        if (res.GetNrows() > 1)
          std::cout << ", " << res(1);
        std::cout << ")" << std::endl;
        std::cout << "\033[0m";
      }

      // Calculate chi²
      //
      // There's certainly a formula using matrix square roots, but
      // this is not so important numerically, so we stick with the
      // simpler formula.
      TMatrixDSym HCHt(TMatrixDSym::kAtA, H->MHt(S));
      HCHt -= V;
      HCHt *= -1;

      tools::invertMatrix(HCHt);

      chi2inc += HCHt.Similarity(res);

      if (!canIgnoreWeights()) {
        ndfInc += weight * measurement.GetNrows();
      }
      else
        ndfInc += measurement.GetNrows();

      if (debugLvl_ > 0) {
        std::cout << "chi² increment = " << chi2inc << std::endl;
      }
    } // end loop over measurements

    cov = TMatrixDSym(TMatrixDSym::kAtA, S);
  }

  currentState_->setStateCovPlane(stateVector, cov, plane);
  currentState_->setAuxInfo(state->getAuxInfo());

  chi2 += chi2inc;
  ndf += ndfInc;

  // set update
  KalmanFittedStateOnPlane* updatedSOP = new KalmanFittedStateOnPlane(*currentState_, chi2inc, ndfInc);
  fi->setUpdate(updatedSOP, direction);
}


// Modified from auto-generated streamer to deal with scoped_ptr correctly.
void KalmanFitter::Streamer(TBuffer &R__b)
{
  // Stream an object of class genfit::KalmanFitter.

  //This works around a msvc bug and should be harmless on other platforms
  typedef ::genfit::KalmanFitter thisClass;
  UInt_t R__s, R__c;
  if (R__b.IsReading()) {
    Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
    //This works around a msvc bug and should be harmless on other platforms
    typedef genfit::AbsKalmanFitter baseClass0;
    baseClass0::Streamer(R__b);
    MeasuredStateOnPlane *p = 0;
    R__b >> p;
    currentState_.reset(p);
    R__b.CheckByteCount(R__s, R__c, thisClass::IsA());
  } else {
    R__c = R__b.WriteVersion(thisClass::IsA(), kTRUE);
    //This works around a msvc bug and should be harmless on other platforms
    typedef genfit::AbsKalmanFitter baseClass0;
    baseClass0::Streamer(R__b);
    R__b << currentState_.get();
    R__b.SetByteCount(R__c, kTRUE);
  }
}
