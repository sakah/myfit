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

      double GetA();
      double GetB();
      TH2F* GetH2D_AB();

   private:
      char fName[32];
      int fAnum;
      double fAstep;
      double fAmin;
      double fAmax;
      double fBstep;
      int fBnum;
      double fBmin;
      double fBmax;
      TH2F* fH2D_AB;
      double fA;
      double fB;
};
#endif
