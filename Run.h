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
      int  ProcessEvent(int iev, int checking_num_turns=-1, double threshold=0.005, bool show_event_canvas=true, bool debug=false);
      void ProcessEvents(int checking_num_turns, double threshold=0.005, int start_iev=0, bool stop_every_event=true, bool show_event_canvas=true, bool show_run_canvas=false, bool debug=false);

   private:
      void Open();
      void ClearEvent();
      void ClearRun();
      void ShowEventCanvas();
      void ShowRunCanvas();
      void BookHist();
      void FillHist();

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
      Hough  fHough1;
      Hough  fHough2;
      CdcHit fCdcHO;
      CdcHit fCdcHO1;
      CdcHit fCdcHO2;
      Circle fCirc1;
      Circle fCirc2;

      CdcHit fCdcFit;
      Fitter fFitter;

      bool fEvtCanOpened;
      MyCanvas fEvtCan1;
      MyCanvas fEvtCan2;

      TH1F* fNumAll1;
      TH1F* fNumSig1;
      TH1F* fNumNoi1;
      TH1F* fNumRem1;
      TH1F* fNumAll2;
      TH1F* fNumSig2;
      TH1F* fNumNoi2;
      TH1F* fNumRem2;
      TH1F* fNumAll3;
      TH1F* fNumSig3;
      TH1F* fNumNoi3;
      TH1F* fNumRem3;

      TH1F* fPtResid1;
      TH1F* fPtResid2;
      TH1F* fPtResol1;
      TH1F* fPtResol2;

      bool fRunCanOpened;
      MyCanvas fRunCan1;
      MyCanvas fRunCan2;
};

#endif
