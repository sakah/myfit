#include "Hough.h"
#include "TMath.h"

Hough::Hough(const char* name)
{
   strcpy(fName, name);

   fTstep = 0.0001;
   fTmin = 0.0;
   fTmax = 2.0*TMath::Pi();
   fRstep = 0.0005;
   fRmin =  0.00;
   fRmax =  0.05;
   fTnum = static_cast<int>((fTmax-fTmin)/fTstep);
   fRnum = static_cast<int>((fRmax-fRmin)/fRstep);
   char* hname = Form("%s Rho-Theta Space;Theta (rad); Rho (cm)",name);
   fH2D_TR = new TH2F(hname, hname, fTnum, fTmin, fTmax, fRnum, fRmin, fRmax);
   fH2D_TR->SetStats(0);
}
Hough::~Hough()
{
   delete fH2D_TR;
}
void Hough::FindLine(int nhits, double* uhits, double* vhits)
{
   fH2D_TR->Reset();
   for (int ihit=0; ihit<nhits; ihit++) {
      for (int it=0; it<fTnum; it++) {
         double theta = it*fTstep + fTmin;
         double rho = uhits[ihit]*TMath::Cos(theta) + vhits[ihit]*TMath::Sin(theta);
         //printf("ihit %d u %f v %f theta %f rho %f\n", ihit, uhits[ihit], vhits[ihit], theta, rho);
         fH2D_TR->Fill(theta, rho);
      }
   }
   int it_max;
   int ir_max;
   int tmp;
   fH2D_TR->GetMaximumBin(it_max, ir_max, tmp);
   fT = fH2D_TR->GetXaxis()->GetBinCenter(it_max);
   fR = fH2D_TR->GetYaxis()->GetBinCenter(ir_max);
}
void Hough::PrintHough()
{
   printf("%s fT %7.3f fR %7.3f\n", fName, fT, fR);
}
double Hough::GetT() { return fT; }
double Hough::GetR() { return fR; }
TH2F* Hough::GetH2D_TR() { return fH2D_TR; }
