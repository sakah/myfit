#ifndef HOUTH_H
#define HOUTH_H

#include "TH2F.h"

class Hough
{
   public:
      Hough(char* name);
      ~Hough();
      void FindLine(int nhits, double* uhits, double* vhits);
      void PrintHough();

   private:
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
