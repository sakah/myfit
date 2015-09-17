#include "Hough.h"

Hough::Hough(const char* name)
{
   fAstep = 0.1;
   fAmin = -8;
   fAmax = 8;
   fBstep = 0.001;
   fBmin = -0.5;
   fBmax = 0.5;
   fAnum = static_cast<int>((fAmax-fAmin)/fAstep);
   fBnum = static_cast<int>((fBmax-fBmin)/fBstep);
   fH2D_AB = new TH2F("h2ab",Form("%s A-B Space;a;b",name),fAnum, fAmin, fAmax, fBnum, fBmin, fBmax);
   fH2D_AB->SetStats(0);
}
Hough::~Hough()
{
   delete fH2D_AB;
}
void Hough::FindLine(int nhits, double* uhits, double* vhits)
{
   for (int ihit=0; ihit<nhits; ihit++) {
      for (int ia=0; ia<fAnum; ia++) {
         double a = ia*fAstep + fAmin;
         double b = -uhits[ihit]*a + vhits[ihit];
         fH2D_AB->Fill(a, b, 1);
      }
   }
   int ia_min;
   int ib_min;
   int tmp;
   fH2D_AB->GetMaximumBin(ia_min, ib_min, tmp);
   fA = fH2D_AB->GetXaxis()->GetBinCenter(ia_min);
   fB = fH2D_AB->GetYaxis()->GetBinCenter(ib_min);
}
void Hough::PrintHough()
{
   printf("fA %7.3f fB %7.3f\n", fA, fB);
}
double Hough::GetA() { return fA; }
double Hough::GetB() { return fB; }
