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

double u1[MAX_CDC_HIT];
double v1[MAX_CDC_HIT];
double u2[MAX_CDC_HIT];
double v2[MAX_CDC_HIT];

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
double threshold = 0.01;
CdcHit cdc1hough;
CdcHit cdc2hough;

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
void run(int iev)
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

   cdcSig.PrintHit("==CDC-Sig==");
   cdcNoise.PrintHit("==CDC-Noise==");
   cdcSigNoise.PrintHit("==CDC-SigNoise==");
   cdcFA.PrintHit("==CDC (First Arrived Hit)==");
   cdcClus.PrintHit("==CDC (Clusters)==");

   cdc1.CopyByLayer(cdcClus, 1);
   cdc2.CopyByLayer(cdcClus, 0);
   cdc1.PrintHit("==CDC-odd==");
   cdc2.PrintHit("==CDC-even==");
   cdc1.GetUV(wireConfig, u1, v1);
   cdc2.GetUV(wireConfig, u2, v2);

   hough1.FindLine(cdc1.GetNumHits(), u1, v1);
   hough2.FindLine(cdc2.GetNumHits(), u2, v2);
   hough1.PrintHough();
   hough2.PrintHough();

   cdc1hough.CopyByHough(cdc1, hough1.GetA(), hough1.GetB(), u1, v1, threshold);
   cdc2hough.CopyByHough(cdc2, hough2.GetA(), hough2.GetB(), u1, v1, threshold);

   // Draw
   if (c1==NULL) {
      int nx = 2;
      int ny = 3;
      c1 = new TCanvas("c1","", 500*nx, 500*ny);
      c1->Divide(nx,ny);
   }
   c1->cd(1); wireConfig.DrawEndPlate("c1"); cdc1.DrawXYAt(wireConfig, "up");
   c1->cd(2); wireConfig.DrawEndPlate("c2"); cdc2.DrawXYAt(wireConfig, "up");
   c1->cd(3); draw_frame("uv1", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc1.DrawAny(u1, v1, 5);
   c1->cd(4); draw_frame("uv2", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc2.DrawAny(u2, v2, 5);
   c1->cd(5); hough1.GetH2D_AB()->Draw();
   c1->cd(6); hough2.GetH2D_AB()->Draw();
   c1->Print("a.pdf");
}
