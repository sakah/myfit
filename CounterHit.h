#ifndef COUNTERHIT_H
#define COUNTERHIT_H

#define MAX_COUNTER_HIT 100

#include "Util.h"
#include "TTree.h"

class CounterHit
{
   public:

      CounterHit();
      void SetBranchAddressNum(TTree* t, const char* name);
      void SetBranchAddressTime(TTree* t, const char* name);
      void SetBranchAddressX(TTree* t, const char* name);
      void SetBranchAddressY(TTree* t, const char* name);
      void SetBranchAddressZ(TTree* t, const char* name);
      void SetBranchAddressPx(TTree* t, const char* name);
      void SetBranchAddressPy(TTree* t, const char* name);
      void SetBranchAddressPz(TTree* t, const char* name);
      void SetBranchAddressAll(TTree* t, const char* num, const char* time, const char* x, const char* y, const char* z, const char* px, const char* py, const char* pz);

      int GetNumHits();
      double GetT(int ihit);
      double GetX(int ihit);
      double GetY(int ihit);
      double GetR(int ihit);
      double GetZ(int ihit);
      double GetPx(int ihit);
      double GetPy(int ihit);
      double GetPz(int ihit);
      double GetPt(int ihit);
      double GetPa(int ihit);

   private:

      int fNumHits;
      double fT[MAX_COUNTER_HIT];
      double fX[MAX_COUNTER_HIT];
      double fY[MAX_COUNTER_HIT];
      double fZ[MAX_COUNTER_HIT];
      double fPx[MAX_COUNTER_HIT];
      double fPy[MAX_COUNTER_HIT];
      double fPz[MAX_COUNTER_HIT];
};

#endif
