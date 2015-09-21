#include "TRandom.h"
#include "TMath.h"
#include "CdcHit.h"

CdcHit::CdcHit(const char* name) { strcpy(fName, name); Clear(); SetRsmear(0.02/*200um*/); }
void CdcHit::Clear() { fNumHits = 0; }
void CdcHit::PrintHit()
{
   printf("%s\n", fName);
   printf("%d\n", fNumHits);
   for (int ihit=0; ihit<fNumHits; ihit++) {
      printf("iturn %2d ilayer %2d icell %3d Pt %7.3f Pz %7.3f Pa %7.3f\n", fIturn[ihit], fIlayer[ihit], fIcell[ihit], GetPt(ihit), GetPz(ihit), GetPa(ihit));
   }
}
void CdcHit::PrintHit(CdcHit& other)
{
   printf("%s\n", fName);
   printf("%d\n", fNumHits);
   for (int ihit=0; ihit<fNumHits; ihit++) {
      printf("iturn %2d ilayer %2d icell %3d | Pt ( %7.3f %7.3f ) Pz ( %7.3f  %7.3f ) Pa ( %7.3f %7.3f ) zpos ( %7.3f %7.3f ) dist ( %7.3f %7.3f )\n", 
            fIturn[ihit], fIlayer[ihit], fIcell[ihit], 
            GetPt(ihit), other.GetPt(ihit), 
            GetPz(ihit), other.GetPz(ihit), 
            GetPa(ihit), other.GetPa(ihit),
            GetZ(ihit) , other.GetZ(ihit),
            GetDist(ihit), other.GetDist(ihit));
   }
}
void CdcHit::AddHit(int ilayer, int icell, int iturn, double dist, double t, double x, double y, double z, double px, double py, double pz)
{
   int i = fNumHits;
   fT[i]      = t; // tof
   fX[i]      = x;
   fY[i]      = y;
   fZ[i]      = z;
   fPx[i]     = px;
   fPy[i]     = py;
   fPz[i]     = pz;
   fIlayer[i] = ilayer;
   fIcell[i]  = icell;
   fIturn[i]  = iturn;
   fDist[i]   = dist;
   fNumHits++;
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
   fDist[i]   = src.fDist[ihit];
   fNumHits++;
}
void CdcHit::MakeNoise(WireConfig& wireConfig, double noise_occupancy)
{
   for (int ilayer=0; ilayer<20; ilayer++) {
      int numCells = wireConfig.GetCellSize(ilayer);
      for (int icell=0; icell<numCells; icell++) {
         double p = gRandom->Uniform(1.0);
         if (p<noise_occupancy) {
            double dist = gRandom->Uniform(1.6);
            AddHit(ilayer, icell, -1, dist, 0, 0, 0, 0, 0, 0, 0);
         }
      }
   }
}
void CdcHit::Merge(CdcHit& cdc1, CdcHit& cdc2)
{
   fNumHits = 0;
   for (int ihit=0; ihit<cdc1.GetNumHits(); ihit++) AddHit(cdc1, ihit);
   for (int ihit=0; ihit<cdc2.GetNumHits(); ihit++) AddHit(cdc2, ihit);
}
void CdcHit::CopyByClusters(WireConfig& wireConfig, CdcHit& src)
{
   fNumHits = 0;

   int nhits[20];
   int hitIdx[20][500];
   int icells[20][500];
   bool single[20][500];
   for (int ilayer=0; ilayer<20; ilayer++) {
      nhits[ilayer] = 0;
      for (int icell=0; icell<500; icell++) {
         single[ilayer][icell] = false;
      }
   }
   for (int ihit=0; ihit<src.GetNumHits(); ihit++) {
      int ilayer = src.fIlayer[ihit];
      int icell = src.fIcell[ihit];
      int n = nhits[ilayer];
      icells[ilayer][n] = icell;
      hitIdx[ilayer][n] = ihit;
      nhits[ilayer]++;
   }
   for (int ilayer=0; ilayer<20; ilayer++) {
      int numCells = wireConfig.GetCellSize(ilayer);
      for (int ihit=0; ihit<nhits[ilayer]; ihit++) {
         int icell = icells[ilayer][ihit];
         bool leftHit = false;
         bool rightHit = false;
         int icellL = icell - 1;
         int icellR = icell + 1;
         if (icellL<0) icellL = numCells-1;
         if (icellR>=numCells) icellR = 0;
         // check that left/right cell is empty or not
         // If empty, skip it
         for (int jhit=0; jhit<nhits[ilayer]; jhit++) {
            int jcell = icells[ilayer][jhit];
            if (jcell == icellL)  leftHit = true;
            if (jcell == icellR)  rightHit = true;
            //printf("ilayer %d icell %d jcell %d (icellL %d icellR %d)\n", ilayer, icell, jcell, icellL, icellR);
         }
         //printf("ilayer %d icell %d leftHit %d rightHit %d\n", ilayer, icell, leftHit, rightHit);
         if (!leftHit && !rightHit) {
            single[ilayer][ihit]=true;
         } else {
            single[ilayer][ihit]=false;
         }
      }
      for (int ihit=0; ihit<nhits[ilayer]; ihit++) {
         //printf("CopyByClusters: ilayer %d icell %d single %d\n", ilayer, icells[ilayer][ihit], single[ilayer][ihit]);
         if (!single[ilayer][ihit]) {
            AddHit(src, hitIdx[ilayer][ihit]);
         }
      }
   }
}
void CdcHit::CopyByFirstArrivedHit(CdcHit& src, double trig_time)
{
   fNumHits = 0;

   int nhits[20][500];
   int hitIdx[20][500][10];
   double timeFromTrig[20][500][10];
   for (int ilayer=0; ilayer<20; ilayer++) {
      for (int icell=0; icell<500; icell++) {
         nhits[ilayer][icell] = 0;
      }
   }
   for (int ihit=0; ihit<src.GetNumHits(); ihit++) {
      int ilayer = src.fIlayer[ihit];
      int icell = src.fIcell[ihit];
      int n = nhits[ilayer][icell];
      double my_time = src.GetT(ihit) + src.GetDriftTime(ihit) - trig_time;
      hitIdx[ilayer][icell][n] = ihit;
      timeFromTrig[ilayer][icell][n] = my_time;
      nhits[ilayer][icell]++;
   }
   for (int ilayer=0; ilayer<20; ilayer++) {
      for (int icell=0; icell<500; icell++) {
         int n = nhits[ilayer][icell];
         if (n==0) continue;
         int min_ihit = 0;
         double min_time=1e10;
         for (int ihit=0; ihit<n; ihit++) {
            double my_time = timeFromTrig[ilayer][icell][ihit];
            if (my_time < min_time) {
               min_time = my_time;
               min_ihit = ihit;
            }
         }
         int idx = hitIdx[ilayer][icell][min_ihit];
         AddHit(src, idx);
      }
   }
}
void CdcHit::CopyByLayer(CdcHit& src, int odd_or_even)
{
   fNumHits = 0;
   for (int ihit=0; ihit<src.GetNumHits(); ihit++) {
      int ilayer = src.fIlayer[ihit];
      if (odd_or_even==CDC_ODD && ilayer%2==0) continue;
      if (odd_or_even==CDC_EVEN && ilayer%2==1) continue;
      AddHit(src, ihit);
   }
}
void CdcHit::CopyByHough(CdcHit& src, double rho, double* uhits, double* vhits, double threshold, bool debug)
{
   /*
    * Assume that (uhits, vhits) are rotated so that y=ax+b -> y = b
    */
   fNumHits = 0;
   for (int ihit=0; ihit<src.GetNumHits(); ihit++) {
      int ilayer = src.fIlayer[ihit];
      int icell = src.fIcell[ihit];
      int iturn = src.fIturn[ihit];
      double res =vhits[ihit] - rho;
      if (debug) printf("iturn %d ilayer %d icell %d u %f v %f rho %f res %f ", iturn, ilayer, icell, uhits[ihit], vhits[ihit], rho, res);
      if (TMath::Abs(res)<threshold) {
         if (debug) printf("--> included\n");
         AddHit(src, ihit);
      } else {
         if (debug) printf("--> excluded\n");
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
   for (int ihit=0; ihit<fNumHits; ihit++) {
      fDist[ihit] += fRsmear[ihit]; // could be negative 
   }
}
int CdcHit::GetMaxLayer()
{ 
   int max_ilayer = -1;
   for (int ihit=0; ihit<fNumHits; ihit++) {
      if (max_ilayer < fIlayer[ihit]) {
         max_ilayer = fIlayer[ihit];
      }
   }
   return max_ilayer;
}
int CdcHit::GetNumTurns() { return fIturn[fNumHits-1]+1; }
int CdcHit::GetNumHits()  { return fNumHits; }
int CdcHit::GetNumHitsByTurn(int iturn_min, int iturn_max)
{
   int num=0;
   for (int ihit=0; ihit<fNumHits; ihit++) {
      if (GetIturn(ihit)>=iturn_min && GetIturn(ihit)<=iturn_max) num++;
   }
   return num;
}
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
double CdcHit::GetDriftTime(int ihit) { return GetDist(ihit)/2e-3; /*cm/ns*/ }
void CdcHit::GetUV(WireConfig& wireConfig, double* uhits, double* vhits)
{
   for (int ihit=0; ihit<fNumHits; ihit++) {
      double wx, wy;
      wireConfig.GetWirePos(fIlayer[ihit], LAYER_TYPE_SENSE, fIcell[ihit], WIRE_TYPE_SENSE, 0, "up", &wx, &wy);
      double r2 = pow2(wx, wy);
      uhits[ihit] = 2.0*wx/r2;
      vhits[ihit] = 2.0*wy/r2;
      //printf("GetUV: ihit %d wx %f wy %f u %f v %f\n", ihit, wx, wy, uhits[ihit], vhits[ihit]);
   }
}
void CdcHit::GetXYend(WireConfig& wireConfig, double* xends, double* yends)
{
   for (int ihit=0; ihit<fNumHits; ihit++) {
      double wx, wy;
      wireConfig.GetWirePos(fIlayer[ihit], LAYER_TYPE_SENSE, fIcell[ihit], WIRE_TYPE_SENSE, 0, "up", &wx, &wy);
      xends[ihit] = wx;
      yends[ihit] = wy;
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
void CdcHit::DrawDriftCircles(WireConfig& wireConfig, const char* z_origin, int fill_style, int fill_color)
{
   for (int ihit=0; ihit<fNumHits; ihit++) {
      double wx, wy;
      if (strcmp(z_origin,"hitz")==0) {
         wireConfig.GetWirePos(fIlayer[ihit], LAYER_TYPE_SENSE, fIcell[ihit], WIRE_TYPE_SENSE, fZ[ihit], "center", &wx, &wy);
      } else if (strcmp(z_origin, "endplate")==0) {
         wireConfig.GetWirePos(fIlayer[ihit], LAYER_TYPE_SENSE, fIcell[ihit], WIRE_TYPE_SENSE, 0, "up", &wx, &wy);
      } else {
         fprintf(stderr,"ERROR: unknown z_origin (%s) ->  hitz | endplate\n", z_origin);
         return;
      }
      double r = GetDist(ihit);
      int col = GetColorByTurn(fIturn[ihit]);
      draw_circle(wx, wy, r, col, fill_style, fill_color);
   }
}
void CdcHit::DrawAny(double* u, double* v, int style)
{
   for (int ihit=0; ihit<fNumHits; ihit++) {
      int col = GetColorByTurn(fIturn[ihit]);
      draw_marker(u[ihit], v[ihit], col, style);
   }
}
