#ifndef FITTER_H
#define FITTER_H

// genfit
#include "Exception.h"
#include "ConstField.h"
#include "FieldManager.h"
#include "FieldMap.h"
#include "KalmanFitter.h"
#include "KalmanFitterRefTrack.h"
#include "KalmanFitterInfo.h"
#include "DAF.h"
#include "KalmanFitStatus.h"
#include "StateOnPlane.h"
#include "Track.h"
#include "TrackPoint.h"
#include "MaterialEffects.h"
#include "RKTrackRep.h"
#include "TGeoMaterialInterface.h"
#include "WireMeasurement.h"
#include "EventDisplay.h"

#include "TVector3.h"
#include "TMatrixDSym.h"
#include "TGeoManager.h"

#define MAX_WIRE_HIT 1000

#include "TVector3.h"

class Fitter
{
   public:
      Fitter();
      void SetGeometry(char* geom_root);
      void SetMagField(char* filedmap_txt);
      void SetMaterialEffects();
      void SetTrack(TVector3& pos_cm, TVector3& mom_GeV, TMatrixDSym& cov);
      void ClearEvent();
      void AddHit(TVector3& w1, TVector3& w2, double w_r, double w_r_err);
      void DoFit();
      void PrintResult();
      bool IsConverged();
      double GetChi2();
      double GetNDF();
      double GetRedChi2();
      double GetPval();
      TVector3& GetPosFit(int ihit);
      TVector3& GetMomFit(int ihit);
      double GetXFit(int ihit);
      double GetYFit(int ihit);
      double GetRFit(int ihit);
      double GetZFit(int ihit);
      double GetPxFit(int ihit);
      double GetPyFit(int ihit);
      double GetPtFit(int ihit);
      double GetPzFit(int ihit);
      double GetPaFit(int ihit);
      double GetDistFit(int ihit);

   private:
      genfit::AbsTrackRep* fTrackRep;
      genfit::Track *fTrack;
      int fNumHits;
      TVector3 fWirePos1[MAX_WIRE_HIT];
      TVector3 fWirePos2[MAX_WIRE_HIT];
      double fDistHits[MAX_WIRE_HIT];

      bool fIsConverged;
      double fChi2;
      double fNDF;
      double fPval;

      TVector3 fPosFits[MAX_WIRE_HIT];
      TVector3 fMomFits[MAX_WIRE_HIT];
      double fDistFits[MAX_WIRE_HIT];
};

#endif
