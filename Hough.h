#ifndef _HOUTH_H
#define _HOUTH_H

class Hough
{
   public:
      Hough(double threshold);
      ~Hough();
      void SetName(char* name);
      void AddHitWithConformal(double x, double y);
      void FindLine();

   private:
#define MAX_HIT 1000
      int fNum_Hits; // all hits, both signal and noise
      // raw XY hits
      double fXhits[MAX_HIT];
      double fYhits[MAX_HIT];
      // transformed UV hits
      double fUhits[MAX_HIT];
      double fVhits[MAX_HIT];

      char fName[128];

      TGraph* fGraph_UV;
      TGraph* fGraph_UV_Inside;
      TH2F* fH2D_AB;
      double fFoundA;
      double fFoundB;

      int fNum_Signal;
      int fNum_Signal_Inside;
      int fNum_Signal_Outside;

      int fNum_Inside;
      int fNum_Inside_Signal;
      int fNum_Inside_Noise;

      double fChi2;
      TH1F* fH2D_Diff;
      double fDiffThreshold;

      double fDiff[10000];
};
#endif
