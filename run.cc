#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TPaveText.h"
#include "TMath.h"

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

double u1rot[MAX_CDC_HIT];
double v1rot[MAX_CDC_HIT];
double u2rot[MAX_CDC_HIT];
double v2rot[MAX_CDC_HIT];

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
TPad* pad1 = NULL;
TPad* pad2 = NULL;

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
int event(int iev, double threshold=0.01, int checking_num_turns=-1)
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
   if (iev>=t->GetEntries()) return -2;

   if (cheren.GetNumHits()==0 || scinti.GetNumHits()==0 || cdcSig.GetNumHits()==0) return - 1;
   if (checking_num_turns !=-1 && cdcSig.GetNumTurns() != checking_num_turns) return -1;
   if (cdcSig.GetMaxLayer()<8) return -1;

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
   rotate_by(0, 0, -hough1.GetT()+TMath::Pi()/2.0, cdc1.GetNumHits(), u1, v1, u1rot, v1rot);
   rotate_by(0, 0, -hough2.GetT()+TMath::Pi()/2.0, cdc2.GetNumHits(), u2, v2, u2rot, v2rot);
   hough1.PrintHough();
   hough2.PrintHough();

   cdc1hough.CopyByHough(cdc1, hough1.GetR(), u1rot, v1rot, threshold);
   cdc2hough.CopyByHough(cdc2, hough2.GetR(), u2rot, v2rot, threshold);

   cdc1hough.GetXYend(wireConfig, x1end, y1end);
   cdc2hough.GetXYend(wireConfig, x2end, y2end);

   circ1.FitCircle(cdc1hough.GetNumHits(), x1end, y1end);
   circ2.FitCircle(cdc2hough.GetNumHits(), x2end, y2end);
   circ1.PrintCircle("===circ1===");
   circ2.PrintCircle("===circ2===");

   // Draw
   if (c1==NULL) {
      int nx = 2;
      int ny = 5;
      c1 = new TCanvas("c1","", 500*nx, 500*ny);
      pad1 = new TPad("pad2","pad2", 0.00, 0.95, 1.00, 1.00); // title
      pad2 = new TPad("pad1","pad1", 0.00, 0.00, 1.00, 0.95); // body
      pad1->Draw();
      pad2->Draw();
      pad2->Divide(nx,ny);
   }
   pad1->cd(); TPaveText* pt = new TPaveText(0,0,1,1); pt->SetFillColor(0); pt->SetBorderSize(0); pt->AddText(Form("iev %d", iev)); pt->Draw();
   int n=1;
   pad2->cd(n++); wireConfig.DrawEndPlate("c1"); cdc1.DrawXYAt(wireConfig, "up");
   pad2->cd(n++); wireConfig.DrawEndPlate("c2"); cdc2.DrawXYAt(wireConfig, "up");
   pad2->cd(n++); draw_frame("uv1;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc1.DrawAny(u1, v1, 5); draw_line_TR(hough1.GetT(), hough1.GetR(), -0.05, 0.05, kRed, 1);
   pad2->cd(n++); draw_frame("uv2;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc2.DrawAny(u2, v2, 5); draw_line_TR(hough2.GetT(), hough2.GetR(), -0.05, 0.05, kRed, 1);
   pad2->cd(n++); draw_frame("uv1rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc1.DrawAny(u1rot, v1rot, 5); draw_line_AB2(0, hough1.GetR(), -0.05, 0.05, kRed, threshold);
   pad2->cd(n++); draw_frame("uv2rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); cdc2.DrawAny(u2rot, v2rot, 5); draw_line_AB2(0, hough2.GetR(), -0.05, 0.05, kRed, threshold);
   pad2->cd(n++); hough1.GetH2D_TR()->Draw("colz"); draw_marker(hough1.GetT(), hough1.GetR(), kRed, 24);
   pad2->cd(n++); hough2.GetH2D_TR()->Draw("colz"); draw_marker(hough2.GetT(), hough2.GetR(), kRed, 24);
   pad2->cd(n++); wireConfig.DrawEndPlate("c3"); cdc1hough.DrawXYAt(wireConfig, "up"); draw_ellipse(circ1.GetX0Fit(), circ1.GetY0Fit(), circ1.GetRFit(), kRed);
   pad2->cd(n++); wireConfig.DrawEndPlate("c4"); cdc2hough.DrawXYAt(wireConfig, "up"); draw_ellipse(circ2.GetX0Fit(), circ2.GetY0Fit(), circ2.GetRFit(), kBlue);
   c1->Print("a.pdf");

   return 0;
}
void run(int checking_num_turns, double threshold)
{
   for (int iev=0; ;iev++) {
      int ret = event(iev, threshold, checking_num_turns);
      if (ret==-1) continue;
      if (ret==-2) break;
      printf("Type q to quit");
      char c = getchar();
      if (c=='q') break;
   }
}
