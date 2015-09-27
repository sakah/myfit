#ifndef RUN_H
#define RUN_H

#include "TSystem.h"
#include "TStyle.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TPaveText.h"
#include "TMath.h"

#include "Util.h"
#include "MyCanvas.h"
#include "WireConfig.h"
#include "InitialHit.h"
#include "CounterHit.h"
#include "CdcHit.h"
#include "Hough.h"
#include "Circle.h"
#include "Fitter.h"

class Run
{
   public:
      Run(const char* name);
      int  ProcessEvent(int iev, int checking_num_turns=-1, double thre_hough=0.005, double thre_circ=0.1);
      void ShowEvents(int start_iev, int checking_num_turns, double thre_hough=0.005, double thre_circ=0.1);
      void ProcessEvents(int start_iev, int checking_num_turns, double thre_hough=0.005, double thre_circ=0.1);

   private:
      void Open();
      void ClearEvent();
      void DrawEventCanvas();

      char fRunName[32];
      int fEventNumber;
      TTree* fTree;
      WireConfig fWireConfig;
      InitialHit fInitial;
      CounterHit fCheren;
      CounterHit fScinti;
      double fNoiseOccupancy;
      CdcHit fCdcNoise;
      CdcHit fCdcSig;
      CdcHit fCdcSigNoise;
      CdcHit fCdcFA;
      CdcHit fCdcCL;
      CdcHit fCdcCL1;
      CdcHit fCdcCL2;
      double fHoughThreshold;
      double fCircleThreshold;
      Hough  fHough1;
      Hough  fHough2;
      CdcHit fCdcHO;
      CdcHit fCdcHO1;
      CdcHit fCdcHO2;
      Circle fCirc11;
      Circle fCirc12;
      CdcHit fCdcCF;
      CdcHit fCdcCF1;
      CdcHit fCdcCF2;
      Circle fCirc21;
      Circle fCirc22;

      Fitter fFitter;

      bool fEvtCanOpened;
      MyCanvas fEvtCan1;
      MyCanvas fEvtCan2;

      bool fShowEventCanvas;
};

#endif
