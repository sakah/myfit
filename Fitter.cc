#include "Util.h"
#include "Fitter.h"

Fitter::Fitter() : fTrack(NULL), fNumHits(0)
{
   const int pdg = 11; // e-
   const double charge = TDatabasePDG::Instance()->GetParticle(pdg)->Charge()/(3.);
   fTrackRep = new genfit::RKTrackRep(pdg); // will be deleted by ~Track();
}

void Fitter::SetGeometry(char* geom_root)
{
   new TGeoManager("Geometry", "Geane geometry");
   TGeoManager::Import(geom_root);
}

void Fitter::SetMagField(char* fieldmap_txt)
{
   genfit::FieldManager::getInstance()->init(new genfit::FieldMap(fieldmap_txt));
}

void Fitter::SetMaterialEffects()
{
   // Kill EnergyLossBrems <= Important!!
   genfit::MaterialEffects* mateff=genfit::MaterialEffects::getInstance();
   //mateff->setEnergyLossBetheBloch(true);
   //mateff->setNoiseBetheBloch(true);
   //mateff->setNoiseCoulomb(true);
   mateff->setEnergyLossBrems(false);
   mateff->setNoiseBrems(false);
   mateff->init(new genfit::TGeoMaterialInterface());
}

void Fitter::ClearEvent()
{
   fNumHits = 0;
   fIsConverged = false;
   fChi2 = -100;
   fNDF  = -100;
   fPval = -100;
   gGeoManager->ResetState();
}

void Fitter::SetTrack(TVector3& pos_cm, TVector3& mom_GeV, TMatrixDSym& cov)
{
   // set inital value
   // smeared start state (Wish to get from track finding)
   genfit::MeasuredStateOnPlane stateSmeared(fTrackRep);
   fTrackRep->setPosMomCov(stateSmeared, pos_cm, mom_GeV, cov);

   // create track
   TVectorD seedState(6);
   TMatrixDSym seedCov(6);
   fTrackRep->get6DStateCov(stateSmeared, seedState, seedCov);
   fTrack = new genfit::Track(fTrackRep, seedState, seedCov);
}

void Fitter::AddHit(TVector3& w1, TVector3& w2, double w_r, double w_r_err)
{
   if (fNumHits >= MAX_WIRE_HIT) {
      fprintf(stderr,"Warning: Too many hits. Ignore this hit\n");
      return;
   }

   fWirePos1[fNumHits] = w1;
   fWirePos2[fNumHits] = w2;
   fDistHits[fNumHits] = w_r;

   TVectorD rawHitCoords(7);
   TMatrixDSym rawHitCov(7);
   rawHitCoords(0) = w1.X();
   rawHitCoords(1) = w1.Y();
   rawHitCoords(2) = w1.Z();
   rawHitCoords(3) = w2.X();
   rawHitCoords(4) = w2.Y();
   rawHitCoords(5) = w2.Z();
   rawHitCoords(6) = w_r;
   rawHitCov(0,0) = 0.0;
   rawHitCov(1,1) = 0.0;
   rawHitCov(2,2) = 0.0;
   rawHitCov(3,3) = 0.0;
   rawHitCov(4,4) = 0.0;
   rawHitCov(5,5) = 0.0;
   rawHitCov(6,6) = w_r_err*w_r_err;

   // Set hits to track
   int detId = 3; // dummy
   int hitId = fNumHits;
   genfit::WireMeasurement* measure = new genfit::WireMeasurement(rawHitCoords, rawHitCov, detId, hitId, NULL); // will be deleted by ~Track()
   measure->setMaxDistance(1.2);
   //measure->setLeftRightResolution(0); // default is 0 (auto)
   fTrack->insertMeasurement(measure);
   //fTrack->Print();

   fNumHits++;
}

void Fitter::DoFit()
{
   int nIter = 7;
   genfit::AbsKalmanFitter* fitter = new genfit::DAF();
   fitter->setMaxIterations(nIter);
   fitter->setMaxFailedHits(5); // this may affect on fitting speed
   //fitter->setDebugLvl(10);
   //fTrack->Print();
   try {
      fitter->processTrack(fTrack);
   } catch (genfit::Exception& e) {
   }

   // set fit results
   fIsConverged = fTrack->getFitStatus(fTrackRep)->isFitConverged();
   fChi2 = fTrack->getFitStatus(fTrackRep)->getChi2();
   fNDF  = fTrack->getFitStatus(fTrackRep)->getNdf();
   fPval = fTrack->getFitStatus(fTrackRep)->getPVal(); 

   int start_ihit = 0;
   for (int ihit=0; ihit<fNumHits; ihit++) {
      try {
         genfit::TrackPoint* tpExp = fTrack->getPointWithMeasurementAndFitterInfo(start_ihit, fTrackRep);
         if (tpExp == NULL) {
            fprintf(stdout,"Track has no TrackPoint with fitterInfo. This error would be bug of genfit2 (2015/02/19)\n");
            continue;
         }
         genfit::KalmanFittedStateOnPlane kfsopExp(*(static_cast<genfit::KalmanFitterInfo*>(tpExp->getFitterInfo(fTrackRep))->getBackwardUpdate()));

         TVector3 linePoint = fWirePos1[ihit];
         TVector3 lineDirection = fWirePos2[ihit] - fWirePos1[ihit];
         TVector3 poca, poca_onwire;
         double length = fTrackRep->extrapolateToLine(kfsopExp, linePoint, lineDirection, poca, poca_onwire);
         //poca.Print();
         //poca_onwire.Print();
         //printf("length %f\n", length);

         TVector3 dist = poca - poca_onwire;
         fDistFits[ihit] = dist.Mag();
         fPosFits[ihit] = fTrackRep->getPos(kfsopExp);
         fMomFits[ihit] = fTrackRep->getMom(kfsopExp);
      } catch(genfit::Exception& e) {
         fprintf(stderr,"extrapolate failed at ihit %d. go to next hit\n", ihit);
      }
   }
}
void Fitter::PrintResult()
{
   printf("converged %d chi2 %f NDF %f chi2/ndf %f pval %f\n", fIsConverged, fChi2, fNDF, fChi2/fNDF, fPval);
}

bool   Fitter::IsConverged() { return fIsConverged; }
double Fitter::GetChi2()     { return fChi2; }
double Fitter::GetNDF()      { return fNDF; }
double Fitter::GetRedChi2()  { return fChi2/fNDF; }
double Fitter::GetPval()     { return fPval; }
TVector3& Fitter::GetPosFit(int ihit) { return fPosFits[ihit]; }
TVector3& Fitter::GetMomFit(int ihit) { return fMomFits[ihit]; }
double Fitter::GetXFit(int ihit) { return GetPosFit(ihit).X(); }
double Fitter::GetYFit(int ihit) { return GetPosFit(ihit).Y(); }
double Fitter::GetRFit(int ihit) { return sqrt2(GetXFit(ihit), GetYFit(ihit)); }
double Fitter::GetZFit(int ihit) { return GetPosFit(ihit).Z(); }
double Fitter::GetPxFit(int ihit) { return GetMomFit(ihit).X(); }
double Fitter::GetPyFit(int ihit) { return GetMomFit(ihit).Y(); }
double Fitter::GetPtFit(int ihit) { return sqrt2(GetPxFit(ihit), GetPyFit(ihit)); }
double Fitter::GetPzFit(int ihit) { return GetMomFit(ihit).Z(); }
double Fitter::GetPaFit(int ihit) { return GetMomFit(ihit).Mag(); }
double Fitter::GetDistFit(int ihit) { return fDistFits[ihit]; }
