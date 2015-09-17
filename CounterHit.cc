#include "CounterHit.h"

CounterHit::CounterHit() { fNumHits = 0; }
void CounterHit::SetBranchAddressNum(TTree* t, const char* name)  { t->SetBranchAddress(name, &fNumHits); }
void CounterHit::SetBranchAddressTime(TTree* t, const char* name) { t->SetBranchAddress(name, fT); }
void CounterHit::SetBranchAddressX(TTree* t, const char* name)    { t->SetBranchAddress(name, fX); }
void CounterHit::SetBranchAddressY(TTree* t, const char* name)    { t->SetBranchAddress(name, fY); }
void CounterHit::SetBranchAddressZ(TTree* t, const char* name)    { t->SetBranchAddress(name, fZ); }
void CounterHit::SetBranchAddressPx(TTree* t, const char* name)   { t->SetBranchAddress(name, fPx); }
void CounterHit::SetBranchAddressPy(TTree* t, const char* name)   { t->SetBranchAddress(name, fPy); }
void CounterHit::SetBranchAddressPz(TTree* t, const char* name)   { t->SetBranchAddress(name, fPz); }
void CounterHit::SetBranchAddressAll(TTree* t, const char* num, const char* time, const char* x, const char* y, const char* z, const char* px, const char* py, const char* pz)
{
   SetBranchAddressNum(t, num);
   SetBranchAddressTime(t, time);
   SetBranchAddressX(t, x);
   SetBranchAddressY(t, y);
   SetBranchAddressZ(t, z);
   SetBranchAddressPx(t, px);
   SetBranchAddressPy(t, py);
   SetBranchAddressPz(t, pz);
}
int    CounterHit::GetNumHits() { return fNumHits; }
double CounterHit::GetT(int ihit) { return fT[ihit]; }
double CounterHit::GetX(int ihit) { return fX[ihit]; }
double CounterHit::GetY(int ihit) { return fY[ihit]; }
double CounterHit::GetR(int ihit) { return sqrt2(fX[ihit], fY[ihit]); }
double CounterHit::GetZ(int ihit) { return fZ[ihit]; }
double CounterHit::GetPx(int ihit) { return fPx[ihit]; }
double CounterHit::GetPy(int ihit) { return fPy[ihit]; }
double CounterHit::GetPz(int ihit) { return fPz[ihit]; }
double CounterHit::GetPt(int ihit) { return sqrt2(fPx[ihit], fPy[ihit]); }
double CounterHit::GetPa(int ihit) { return sqrt3(fPx[ihit], fPy[ihit], fPz[ihit]); }
