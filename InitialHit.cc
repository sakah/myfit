#include "TTree.h"
#include "Util.h"
#include "InitialHit.h"

InitialHit::InitialHit() {}
void InitialHit::SetBranchAddress(TTree*t, const char* x, const char* y, const char*z, const char* px, const char* py, const char* pz)
{
   t->SetBranchAddress(x, &fX);
   t->SetBranchAddress(y, &fY);
   t->SetBranchAddress(z, &fZ);
   t->SetBranchAddress(px, &fPx);
   t->SetBranchAddress(py, &fPy);
   t->SetBranchAddress(pz, &fPz);
}
double InitialHit::GetX() { return fX; }
double InitialHit::GetY() { return fY; }
double InitialHit::GetR() { return sqrt2(fX, fY); }
double InitialHit::GetZ() { return fZ; }
double InitialHit::GetPx() { return fPx*1e3; }
double InitialHit::GetPy() { return fPy*1e3; }
double InitialHit::GetPt() { return sqrt2(fPx, fPy)*1e3; }
double InitialHit::GetPz() { return fPz*1e3; }
double InitialHit::GetPa() { return sqrt3(fPx, fPy, fPz)*1e3; }
void InitialHit::PrintHit()
{
   printf("===Initial===\n");
   printf("Time   0.000 X %7.3f Y %7.3f R %7.3f Z %7.3f Px %7.3f Py %7.3f Pt %7.3f Pz %7.3f Pa %7.3f\n", 
         GetX(), 
         GetY(), 
         GetR(), 
         GetZ(), 
         GetPx(), 
         GetPy(), 
         GetPt(), 
         GetPz(), 
         GetPa());
}
