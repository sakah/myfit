#include "TMath.h"
#include "CdcHit.h"
#include "Circle.h"

static int circ_nhits;
static double circ_xhits[MAX_CDC_HIT];
static double circ_yhits[MAX_CDC_HIT];
static double circ_xsig;
static double circ_ysig;

static void func_circ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *x, Int_t iflag)
{
   // To suppress warning messages.
   (void)npar;
   (void)gin;
   (void)iflag;

   double x0 = x[0];
   double y0 = x[1];
   double R  = x[2];
   double chi2 = 0;
   for (int ihit=0; ihit<circ_nhits; ihit++) {
      double x1 = circ_xhits[ihit] - x0;
      double y1 = circ_yhits[ihit] - y0;
      double theta = TMath::ATan2(y1, x1);
      double xexp = R * TMath::Cos(theta);
      double yexp = R * TMath::Sin(theta);
      double dx = (xexp-x1)/circ_xsig;
      double dy = (yexp-y1)/circ_ysig;
      chi2 += dx*dx + dy*dy;
   }
   f = chi2;
}

Circle::Circle(const char*name)
{
   strcpy(fName, name);
   fMinuit = new TMinuit(3);
   fMinuit->SetFCN(func_circ);

   SetFitIniPar();
}
void Circle::SetFitIniPar()
{
   fX0Ini = 20;
   fY0Ini = -5;
   fRIni = 40;
   fX0Step = 1;
   fY0Step = 1;
   fRStep = 1;
   fXSig = 1.0;
   fYSig = 1.0;
}
void Circle::FitCircle(int nhits, double* xhits, double* yhits)
{
   fNumHits = nhits;

   // copy to static values
   circ_nhits = nhits;
   for (int ihit=0; ihit<nhits; ihit++) {
      circ_xhits[ihit] = xhits[ihit];
      circ_yhits[ihit] = yhits[ihit];
   }
   circ_xsig = fXSig;
   circ_ysig = fYSig;

   Int_t ierflag;
   Double_t arglist[10];
   TString Tag[3];
   Double_t var[3];
   Double_t verr[3];
   Double_t bnd1, bnd2;
   Int_t ivarbl;

   // suppress output
   arglist[0] = -1;
   fMinuit->mnexcm("SET PRINT", arglist, 1, ierflag);

   // suppress warning message
   fMinuit->mnexcm("SET NOWarnings", arglist, 0, ierflag);

   // set initial values with limits
   fMinuit->mnparm(0, "x0", fX0Ini, fX0Step, 0, 0, ierflag); // cm
   fMinuit->mnparm(1, "y0", fY0Ini, fY0Step, 0, 0, ierflag); // cm
   fMinuit->mnparm(2 ,"R",  fRIni,  fRStep,  20, 70, ierflag); // cm

   // use chi2
   arglist[0] = 1;
   fMinuit->mnexcm("SET ERR", arglist, 1, ierflag);

   // do minimize
   arglist[0] = 1000; // do at least 1000 function calls
   arglist[1] = 0.1;  // tolerance = 0.1
   fMinuit->mnexcm("MIGRAD", arglist, 2, ierflag);

   // copy fit results
   for (int i=0; i<3; i++) {
      fMinuit->mnpout(i, Tag[i], var[i], verr[i], bnd1, bnd2, ivarbl);
      //printf("i %d %f +/- %f\n", i, var[i], verr[i]);
   }

   // chi2
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   fMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   fChi2 = amin;

   fX0Fit = var[0]; //cm
   fY0Fit = var[1]; //cm
   fRFit  = var[2]; // cm
}

void Circle::PrintCircle()
{
   printf("%s\n", fName);
   printf("X0 %7.3f Y0 %7.3f R %7.3f Pt %7.3f (MeV/c) chi2/ndf %7.3f/%d (%7.3f)\n", GetX0Fit(), GetY0Fit(), GetRFit(), GetRFit()*3.0*1.0, fChi2, fNumHits-3, GetRedChi2());
}

double Circle::GetX0Ini() { return fX0Ini; }
double Circle::GetY0Ini() { return fY0Ini; }
double Circle::GetRIni() { return fRIni; }

double Circle::GetX0Fit() { return fX0Fit; }
double Circle::GetY0Fit() { return fY0Fit; }
double Circle::GetRFit() { return fRFit; }
double Circle::GetChi2() { return fChi2; }
double Circle::GetRedChi2() { return fChi2/(fNumHits-3); }
