#ifndef CDCHIT_H
#define CDCHIT_H

#define MAX_CDC_HIT 1000

#define CDC_ODD  (1)
#define CDC_EVEN (0)
#define CDC_ALL  (-1)

#include "Util.h"
#include "TTree.h"
#include "WireConfig.h"

class CdcHit
{
   public:

      CdcHit();
      void Clear();
      void PrintHit(char* prefix);
      void AddHit(int ilayer, int icell, int iturn, double dist); // used for noise
      void AddHit(CdcHit& src, int ihit);
      void MakeNoise(WireConfig& wireConfig, double noise_occupancy, int seed);
      void Merge(CdcHit& cdc1, CdcHit& cdc2);
      void CopyByClusters(WireConfig& wireConfig, CdcHit& src);
      void CopyByFirstArrivedHit(CdcHit& src, double trig_time);
      void CopyByLayer(CdcHit& src, int odd_or_even);
      void CopyByHough(CdcHit& src, double a, double b, double* uhits, double* vhits, double threshold);

      void SetBranchAddressNum(TTree* t, const char* name);
      void SetBranchAddressTime(TTree* t, const char* name);
      void SetBranchAddressX(TTree* t, const char* name);
      void SetBranchAddressY(TTree* t, const char* name);
      void SetBranchAddressZ(TTree* t, const char* name);
      void SetBranchAddressPx(TTree* t, const char* name);
      void SetBranchAddressPy(TTree* t, const char* name);
      void SetBranchAddressPz(TTree* t, const char* name);
      void SetBranchAddressIlayer(TTree* t, const char* name);
      void SetBranchAddressIcell(TTree* t, const char* name);
      void SetBranchAddressIturn(TTree* t, const char* name);
      void SetBranchAddressDist(TTree* t, const char* name);
      void SetBranchAddressAll(TTree* t, const char* num, const char* time, const char* x, const char* y, const char* z, const char* px, const char* py, const char* pz, 
            const char* ilayer, const char* icell, const char* iturn, const char* dist);
      void SetRsmear(double sigma);

      int GetNumTurns();
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
      int GetIlayer(int ihit);
      int GetIcell(int ihit);
      int GetIturn(int ihit);
      double GetDist(int ihit);
      double GetDistSmeared(int ihit);
      double GetDriftTime(int ihit);
      void GetUV(WireConfig& wireConfig, double* uhits, double* vhits);
      void GetXYend(WireConfig& wireConfig, double* xends, double* yends);

      int GetColorByTurn(int iturn);
      void DrawAny(double* u, double* v, int style);
      void DrawXYAt(WireConfig& wireConfig, const char* z_origin);

   private:

      int fNumHits;
      double fT[MAX_CDC_HIT];
      double fX[MAX_CDC_HIT];
      double fY[MAX_CDC_HIT];
      double fZ[MAX_CDC_HIT];
      double fPx[MAX_CDC_HIT];
      double fPy[MAX_CDC_HIT];
      double fPz[MAX_CDC_HIT];
      int fIlayer[MAX_CDC_HIT];
      int fIcell[MAX_CDC_HIT];
      int fIturn[MAX_CDC_HIT];
      double fDist[MAX_CDC_HIT];

      double fRsmear[MAX_CDC_HIT];
};

#endif
