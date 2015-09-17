#include "TRandom.h"
#include "CdcHit.h"

CdcHit::CdcHit() { fNumHits = 0; SetRsmear(0.02/*200um*/); }
void CdcHit::PrintHit(char* prefix)
{
   printf("%s\n", prefix);
   for (int ihit=0; ihit<fNumHits; ihit++) {
      printf("iturn %2d ilayer %2d icell %3d\n", fIturn[ihit], fIlayer[ihit], fIcell[ihit]);
   }
}
void CdcHit::AddHit(CdcHit& src, int ihit)
{
   int i = fNumHits;
   fT[i]      = src.fT[ihit];
   fX[i]      = src.fX[ihit];
   fY[i]      = src.fY[ihit];
   fZ[i]      = src.fZ[ihit];
   fPx[i]     = src.fPx[ihit];
   fPy[i]     = src.fPy[ihit];
   fPz[i]     = src.fPz[ihit];
   fIlayer[i] = src.fIlayer[ihit];
   fIcell[i]  = src.fIcell[ihit];
   fIturn[i]  = src.fIturn[ihit];
   fDist[i]  = src.fDist[ihit];
   fNumHits++;
}
void CdcHit::CopyByLayer(CdcHit& src, int odd_or_even)
{
   fNumHits = 0;
   for (int ihit=0; ihit<src.GetNumHits(); ihit++) {
      if (odd_or_even==CDC_ODD && src.fIlayer[ihit]%2==0) continue;
      if (odd_or_even==CDC_EVEN && src.fIlayer[ihit]%2==1) continue;
      AddHit(src, ihit);
   }
}
void CdcHit::CopyByHough(CdcHit& src, double a, double b, double* uhits, double* vhits, double threshold)
{
   fNumHits = 0;
   for (int ihit=0; ihit<src.GetNumHits(); ihit++) {
      double v = a * uhits[ihit] + b;
      double res = v - vhits[ihit];
      if (TMath::Abs(res)<threshold) {
         AddHit(src, ihit);
      }
   }
}
void CdcHit::SetBranchAddressNum(TTree* t, const char* name)  { t->SetBranchAddress(name, &fNumHits); }
void CdcHit::SetBranchAddressTime(TTree* t, const char* name) { t->SetBranchAddress(name, fT); }
void CdcHit::SetBranchAddressX(TTree* t, const char* name)    { t->SetBranchAddress(name, fX); }
void CdcHit::SetBranchAddressY(TTree* t, const char* name)    { t->SetBranchAddress(name, fY); }
void CdcHit::SetBranchAddressZ(TTree* t, const char* name)    { t->SetBranchAddress(name, fZ); }
void CdcHit::SetBranchAddressPx(TTree* t, const char* name)   { t->SetBranchAddress(name, fPx); }
void CdcHit::SetBranchAddressPy(TTree* t, const char* name)   { t->SetBranchAddress(name, fPy); }
void CdcHit::SetBranchAddressPz(TTree* t, const char* name)   { t->SetBranchAddress(name, fPz); }
void CdcHit::SetBranchAddressIlayer(TTree* t, const char* name){ t->SetBranchAddress(name, fIlayer); }
void CdcHit::SetBranchAddressIcell(TTree* t, const char* name) { t->SetBranchAddress(name, fIcell); }
void CdcHit::SetBranchAddressIturn(TTree* t, const char* name) { t->SetBranchAddress(name, fIturn); }
void CdcHit::SetBranchAddressDist(TTree* t, const char* name)  { t->SetBranchAddress(name, fDist); }
void CdcHit::SetBranchAddressAll(TTree* t, const char* num, const char* time, const char* x, const char* y, const char* z, const char* px, const char* py, const char* pz, 
      const char* ilayer, const char* icell, const char* iturn, const char* dist)
{
   SetBranchAddressNum(t, num);
   SetBranchAddressTime(t, time);
   SetBranchAddressX(t, x);
   SetBranchAddressY(t, y);
   SetBranchAddressZ(t, z);
   SetBranchAddressPx(t, px);
   SetBranchAddressPy(t, py);
   SetBranchAddressPz(t, pz);
   SetBranchAddressIlayer(t, ilayer);
   SetBranchAddressIcell(t, icell);
   SetBranchAddressIturn(t, iturn);
   SetBranchAddressDist(t, dist);
}
void CdcHit::SetRsmear(double sigma)
{
   for (int ihit=0; ihit<MAX_CDC_HIT; ihit++) {
      fRsmear[ihit] = gRandom->Gaus(0, sigma);
   }
}
int    CdcHit::GetNumHits() { return fNumHits; }
double CdcHit::GetT(int ihit) { return fT[ihit]; }
double CdcHit::GetX(int ihit) { return fX[ihit]; }
double CdcHit::GetY(int ihit) { return fY[ihit]; }
double CdcHit::GetR(int ihit) { return sqrt2(fX[ihit], fY[ihit]); }
double CdcHit::GetZ(int ihit) { return fZ[ihit]; }
double CdcHit::GetPx(int ihit) { return fPx[ihit]*1e3; }
double CdcHit::GetPy(int ihit) { return fPy[ihit]*1e3; }
double CdcHit::GetPz(int ihit) { return fPz[ihit]*1e3; }
double CdcHit::GetPt(int ihit) { return sqrt2(fPx[ihit], fPy[ihit])*1e3; }
double CdcHit::GetPa(int ihit) { return sqrt3(fPx[ihit], fPy[ihit], fPz[ihit])*1e3; }
int CdcHit::GetIlayer(int ihit) { return fIlayer[ihit]; }
int CdcHit::GetIcell(int ihit) { return fIcell[ihit]; }
int CdcHit::GetIturn(int ihit) { return fIturn[ihit]; }
double CdcHit::GetDist(int ihit) { return fDist[ihit]; }
double CdcHit::GetDistSmeared(int ihit) { return fDist[ihit] + fRsmear[ihit]; }
void CdcHit::GetUV(WireConfig& wireConfig, double* uhits, double* vhits)
{
   for (int ihit=0; ihit<fNumHits; ihit++) {
      double wx, wy;
      wireConfig.GetWirePos(fIlayer[ihit], LAYER_TYPE_SENSE, fIcell[ihit], WIRE_TYPE_SENSE, 0, "up", &wx, &wy);
      double r2 = pow2(wx, wy);
      uhits[ihit] = 2.0*wx/r2;
      vhits[ihit] = 2.0*wy/r2;
   }
}
int CdcHit::GetColorByTurn(int iturn)
{
   int col = kCyan; // noise
   if (iturn==0) col = kRed;
   if (iturn==1) col = kBlue;
   if (iturn==2) col = kGreen;
   if (iturn==3) col = kMagenta;
   if (iturn>=4) col = kGray;
   return col;
}
void CdcHit::DrawXYAt(WireConfig& wireConfig, const char* z_origin)
{
   for (int ihit=0; ihit<fNumHits; ihit++) {
      double wx, wy;
      if (strcmp(z_origin,"MC")==0) {
         wireConfig.GetWirePos(fIlayer[ihit], LAYER_TYPE_SENSE, fIcell[ihit], WIRE_TYPE_SENSE, fZ[ihit], "center", &wx, &wy);
      } else {
         wireConfig.GetWirePos(fIlayer[ihit], LAYER_TYPE_SENSE, fIcell[ihit], WIRE_TYPE_SENSE, 0, z_origin, &wx, &wy);
      }
      double r = GetDist(ihit);
      int col = GetColorByTurn(fIturn[ihit]);
      draw_ellipse(wx, wy, r, col);
   }
}
void CdcHit::DrawAny(double* u, double* v, int style)
{
   for (int ihit=0; ihit<fNumHits; ihit++) {
      int col = GetColorByTurn(fIturn[ihit]);
      draw_marker(u[ihit], v[ihit], col, style);
   }
}
