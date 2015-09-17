#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "Util.h"
#include "XTCurve.h"
#include "wireConfig.h"
#include "InitialHit.h"
#include "CounterHit.h"
#include "CdcHit.h"
#include "Hough.h"
#include "Circle.h"

double u1[MAX_CDC_HIT];
double v1[MAX_CDC_HIT];
double u2[MAX_CDC_HIT];
double v2[MAX_CDC_HIT];

double x1end[MAX_CDC_HIT];
double y1end[MAX_CDC_HIT];
double x2end[MAX_CDC_HIT];
double y2end[MAX_CDC_HIT];

TTree* t;
InitialHit initial;
CounterHit cheren;
CounterHit scinti;
double noise_occupancy = 0.10;
CdcHit cdcNoise;
CdcHit cdcSig;
CdcHit cdcSigNoise;
CdcHit cdcFA;
CdcHit cdcClus;
CdcHit cdc1; // odd-layer
CdcHit cdc2; // even-layer
Hough hough1("odd ");
Hough hough2("even");
CdcHit cdc1hough;
CdcHit cdc2hough;
Circle circ1;
Circle circ2;

WireConfig wireConfig;
TCanvas* c1 = NULL;
bool opened=false;
void open()
{
   char* wire_config = "B1T_square_1.5m_ver_2014_03_28.txt";
   wireConfig.Init(wire_config);

   char* root = "root/hoge1-0.root";
   TFile* f = new TFile(root);
   t = (TTree*)f->Get("t");

   opened=true;
}
void run(int iev, double threshold=0.01)
{
   if (!opened) open();

   cheren.Clear();
   scinti.Clear();
   cdcNoise.Clear();
   cdcSig.Clear();
   cdcSigNoise.Clear();
   cdcFA.Clear();
   cdcClus.Clear();
   cdc1.Clear();
   cdc2.Clear();
   cdc1hough.Clear();
   cdc2hough.Clear();

   initial.SetBranchAddress(t, "ini_x_cm", "ini_y_cm", "ini_z_cm", "ini_px_GeV", "ini_py_GeV", "ini_pz_GeV");
   scinti.SetBranchAddressAll(t, "trig_scinti_nhits", "trig_scinti_time", "trig_scinti_posx", "trig_scinti_posy", "trig_scinti_posz", "trig_scinti_momx", "trig_scinti_momy", "trig_scinti_momz");
   cheren.SetBranchAddressAll(t, "trig_cherenkov_nhits", "trig_cherenkov_time", "trig_cherenkov_posx", "trig_cherenkov_posy", "trig_cherenkov_posz", "trig_cherenkov_momx", "trig_cherenkov_momy", "trig_cherenkov_momz");
   cdcSig.SetBranchAddressAll(t, "nwirehit", "time", "minhit_x", "minhit_y", "minhit_z", "minhit_px", "minhit_py", "minhit_pz", "ilayer", "icell", "iturn", "dist");

   t->GetEntry(iev);

   if (cheren.GetNumHits()==0 || scinti.GetNumHits()==0) return;
   double trig_time = scinti.GetT(0);

   printf("iev %d\n", iev);
   initial.PrintHit();
   scinti.PrintHit("==scinti==");
   cheren.PrintHit("==cherenkov==");

   int seed = 1;
   cdcNoise.MakeNoise(wireConfig, noise_occupancy, seed);
   cdcSigNoise.Merge(cdcSig, cdcNoise);
   cdcFA.CopyByFirstArrivedHit(cdcSigNoise, trig_time);
   cdcClus.CopyByClusters(wireConfig, cdcFA);

   cdcSig.PrintHit("==CDC(Sig)==");
   cdcNoise.PrintHit("==CDC(Noise)==");
   cdcSigNoise.PrintHit("==CDC(SigNoise)==");
   cdcFA.PrintHit("==CDC(First Arrived Hit)==");
   cdcClus.PrintHit("==CDC(Clusters)==");

   cdc1.CopyByLayer(cdcClus, 1);
   cdc2.CopyByLayer(cdcClus, 0);
   cdc1.PrintHit("==CDC(odd-layer)==");
   cdc2.PrintHit("==CDC(even-layer)==");
   cdc1.GetUV(wireConfig, u1, v1);
   cdc2.GetUV(wireConfig, u2, v2);

   hough1.FindLine(cdc1.GetNumHits(), u1, v1);
   hough2.FindLine(cdc2.GetNumHits(), u2, v2);
   hough1.PrintHough();
   hough2.PrintHough();

   cdc1hough.CopyByHough(cdc1, hough1.GetA(), hough1.GetB(), u1, v1, threshold);
   cdc2hough.CopyByHough(cdc2, hough2.GetA(), hough2.GetB(), u2, v2, threshold);

   cdc1hough.GetXYend(wireConfig, x1end, y1end);
   cdc2hough.GetXYend(wireConfig, x2end, y2end);

   circ1.FitCircle(cdc1hough.GetNumHits(), x1end, y1end);
   circ2.FitCircle(cdc2hough.GetNumHits(), x2end, y2end);
   circ1.PrintCircle("===circ1===");
   circ2.PrintCircle("===circ2===");

   // Draw
   if (c1==NULL) {
      int nx = 2;
      int ny = 4;
      c1 = new TCanvas("c1","", 500*nx, 500*ny);
      c1->Divide(nx,ny);
   }
   int n=1;
   c1->cd(n++); wireConfig.DrawEndPlate("c1"); cdc1.DrawXYAt(wireConfig, "up");
   c1->cd(n++); wireConfig.DrawEndPlate("c2"); cdc2.DrawXYAt(wireConfig, "up");
   c1->cd(n++); draw_frame("uv1;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc1.DrawAny(u1, v1, 5); draw_line(hough1.GetA(), hough1.GetB(), -0.05, 0.05, kRed);
   c1->cd(n++); draw_frame("uv2;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc2.DrawAny(u2, v2, 5); draw_line(hough2.GetA(), hough2.GetB(), -0.05, 0.05, kRed);
   c1->cd(n++); hough1.GetH2D_AB()->Draw("colz"); draw_marker(hough1.GetA(), hough1.GetB(), kRed, 29);
   c1->cd(n++); hough2.GetH2D_AB()->Draw("colz"); draw_marker(hough1.GetA(), hough1.GetB(), kRed, 29);
   c1->cd(n++); wireConfig.DrawEndPlate("c3"); cdc1hough.DrawXYAt(wireConfig, "up"); draw_ellipse(circ1.GetX0Fit(), circ1.GetY0Fit(), circ1.GetRFit(), kRed);
   c1->cd(n++); wireConfig.DrawEndPlate("c4"); cdc2hough.DrawXYAt(wireConfig, "up"); draw_ellipse(circ2.GetX0Fit(), circ2.GetY0Fit(), circ2.GetRFit(), kBlue);
   c1->Print("a.pdf");
}
