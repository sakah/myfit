#ifndef CIRC_H
#define CIRC_H

#include "TMinuit.h"

class Circle
{
   public:

      Circle(const char* name);
      void SetFitIniPar();
      void FitCircle(int nhits, double* xhits, double* yhits);
      void PrintCircle();

      double GetX0Ini();
      double GetY0Ini();
      double GetRIni();

      double GetX0Fit();
      double GetY0Fit();
      double GetRFit();
      double GetChi2();
      double GetRedChi2();

   private:

      char fName[32];
      TMinuit* fMinuit;
      int fNumHits;
      double fChi2;

      double fXSig;
      double fYSig;
      double fX0Fit;
      double fY0Fit;
      double fRFit;
      double fX0Ini;
      double fY0Ini;
      double fRIni;
      double fX0Step;
      double fY0Step;
      double fRStep;

};
#endif
