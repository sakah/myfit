#ifndef HOUTH_H
#define HOUTH_H

#include "TH2F.h"

class Hough
{
   public:
      Hough(const char* name);
      ~Hough();
      void FindLine(int nhits, double* uhits, double* vhits);
      void PrintHough();

      double GetT();
      double GetR();
      TH2F* GetH2D_TR();

   private:
      char fName[32];
      int fTnum;
      double fTstep;
      double fTmin;
      double fTmax;
      int fRnum;
      double fRstep;
      double fRmin;
      double fRmax;
      TH2F* fH2D_TR;
      double fT;
      double fR;
};
#endif
