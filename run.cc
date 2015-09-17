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
CdcHit cdc;
CdcHit cdc1;
CdcHit cdc2;
Hough hough1("odd ");
Hough hough2("even");
double threshold = 0.01;
CdcHit cdc1hough;
CdcHit cdc2hough;

TCanvas* c1 = NULL;
void run(int iev)
{
   char* wire_config = "B1T_square_1.5m_ver_2014_03_28.txt";
   WireConfig wireConfig;
   wireConfig.Init(wire_config);

   char* root = "root/hoge1-0.root";
   TFile* f = new TFile(root);
   t = (TTree*)f->Get("t");

   initial.SetBranchAddress(t, "ini_x_cm", "ini_y_cm", "ini_z_cm", "ini_px_GeV", "ini_py_GeV", "ini_pz_GeV");
   scinti.SetBranchAddressAll(t, "trig_scinti_nhits", "trig_scinti_time", "trig_scinti_posx", "trig_scinti_posy", "trig_scinti_posz", "trig_scinti_momx", "trig_scinti_momy", "trig_scinti_momz");
   cheren.SetBranchAddressAll(t, "trig_cherenkov_nhits", "trig_cherenkov_time", "trig_cherenkov_posx", "trig_cherenkov_posy", "trig_cherenkov_posz", "trig_cherenkov_momx", "trig_cherenkov_momy", "trig_cherenkov_momz");
   cdc.SetBranchAddressAll(t, "nwirehit", "time", "minhit_x", "minhit_y", "minhit_z", "minhit_px", "minhit_py", "minhit_pz", "ilayer", "icell", "iturn", "dist");

   t->GetEntry(iev);

   if (cheren.GetNumHits()==0 || scinti.GetNumHits()==0) return;
   printf("iev %d\n", iev);
   initial.PrintHit();
   scinti.PrintHit("==scinti==");
   cheren.PrintHit("==cherenkov==");

   cdc1.CopyByLayer(cdc, 1);
   cdc2.CopyByLayer(cdc, 0);
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
