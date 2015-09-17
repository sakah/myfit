#ifndef COUNTERHIT_H
#define COUNTERHIT_H

#define MAX_COUNTER_HIT 100

#include "Util.h"
#include "TTree.h"

class CounterHit
{
   public:

      CounterHit();
      void Clear();
      void PrintHit(char* prefix);
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
      double GetT(int ihit); // ns
      double GetX(int ihit); // cm
      double GetY(int ihit); // cm
      double GetR(int ihit); // cm
      double GetZ(int ihit); // cm
      double GetPx(int ihit); // MeV
      double GetPy(int ihit); // MeV
      double GetPz(int ihit); // MeV
      double GetPt(int ihit); // MeV
      double GetPa(int ihit); // MeV

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
