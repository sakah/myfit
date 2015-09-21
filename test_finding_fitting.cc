#include "TSystem.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TPaveText.h"
#include "TMath.h"

#include "Util.h"
#include "MyCanvas.h"
#include "wireConfig.h"
#include "InitialHit.h"
#include "CounterHit.h"
#include "CdcHit.h"
#include "Hough.h"
#include "Circle.h"
#include "Fitter.h"

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

bool debug=false;
TTree* t;
WireConfig wireConfig;
InitialHit initial;
CounterHit cheren("Cherenkov");
CounterHit scinti("Scinti");
double noise_occupancy = 0.10;
CdcHit cdcNoise("CDC Noise");
CdcHit cdcSig("CDC Signal");
CdcHit cdcSigNoise("CDC Signal with Noise");
CdcHit cdcFA("CDC FirstArrived Hits");
CdcHit cdcClus("CDC Clusters");
CdcHit cdcClus1("CDC Clusters (odd layers)");
CdcHit cdcClus2("CDC Clusters (even layers)");
Hough hough1("Hough (odd layers)");
Hough hough2("Hough (even layers)");
CdcHit cdc1Hough("CDC after Hough (odd layers)");
CdcHit cdc2Hough("CDC after Hough (even layers)");
Circle circ1("Circle (odd layers)");
Circle circ2("Circle (even layers)");

CdcHit cdcFit("CDC Fit");
Fitter fitter;

MyCanvas c1("c1","c1",   0, 0, 600, 600);
MyCanvas c2("c2","c2", 600, 0, 600, 600);

bool opened=false;
void open()
{
   char* wire_config = "B1T_square_1.5m_ver_2014_03_28.txt";
   wireConfig.Init(wire_config);

   char* root = "root/hoge1-0.root";
   TFile* f = new TFile(root);
   t = (TTree*)f->Get("t");

   initial.SetBranchAddress(t, "ini_x_cm", "ini_y_cm", "ini_z_cm", "ini_px_GeV", "ini_py_GeV", "ini_pz_GeV");
   scinti.SetBranchAddressAll(t, "trig_scinti_nhits", "trig_scinti_time", "trig_scinti_posx", "trig_scinti_posy", "trig_scinti_posz", "trig_scinti_momx", "trig_scinti_momy", "trig_scinti_momz");
   cheren.SetBranchAddressAll(t, "trig_cherenkov_nhits", "trig_cherenkov_time", "trig_cherenkov_posx", "trig_cherenkov_posy", "trig_cherenkov_posz", "trig_cherenkov_momx", "trig_cherenkov_momy", "trig_cherenkov_momz");
   cdcSig.SetBranchAddressAll(t, "nwirehit", "time", "minhit_x", "minhit_y", "minhit_z", "minhit_px", "minhit_py", "minhit_pz", "ilayer", "icell", "iturn", "dist");

   opened=true;
}

void clearEvent()
{
   cheren.Clear();
   scinti.Clear();
   cdcNoise.Clear();
   cdcSig.Clear();
   cdcSigNoise.Clear();
   cdcFA.Clear();
   cdcClus.Clear();
   cdcClus1.Clear();
   cdcClus2.Clear();
   cdc1Hough.Clear();
   cdc2Hough.Clear();
}

bool showEventCanvas=true;
int event(int iev, double threshold=0.01, int checking_num_turns=-1)
{
   if (!opened) open();

   gRandom->SetSeed(1); // Use same seed => same rsmear and noise pattern

   clearEvent();

   t->GetEntry(iev);
   printf("iev %d nhits %d nturns %d nscinti %d nchren %d\n", iev, cdcSig.GetNumHits(), cdcSig.GetNumTurns(), scinti.GetNumHits(), cheren.GetNumHits());
   if (iev>=t->GetEntries()) return -2;
   if (cheren.GetNumHits()==0 || scinti.GetNumHits()==0 || cdcSig.GetNumHits()==0) return - 1;
   if (checking_num_turns !=-1 && cdcSig.GetNumTurns() != checking_num_turns) return -1;
   if (cdcSig.GetMaxLayer()<8) return -1;

   if (debug) {
      initial.PrintHit();
      scinti.PrintHit();
      cheren.PrintHit();
   }

   cdcSig.SetRsmear(0.02);
   cdcNoise.MakeNoise(wireConfig, noise_occupancy);
   cdcSigNoise.Merge(cdcSig, cdcNoise);
   if (debug) {
      cdcSig.PrintHit();
      cdcNoise.PrintHit();
      cdcSigNoise.PrintHit();
   }

   cdcFA.CopyByFirstArrivedHit(cdcSigNoise, scinti.GetT(0));
   cdcClus.CopyByClusters(wireConfig, cdcFA);
   if (debug) {
      cdcSigNoise.PrintHit();
      cdcFA.PrintHit();
      cdcClus.PrintHit();
   }

   cdcClus1.CopyByLayer(cdcClus, 1);
   cdcClus2.CopyByLayer(cdcClus, 0);
   if (debug) {
      cdcClus1.PrintHit();
      cdcClus2.PrintHit();
   }
   cdcClus1.GetUV(wireConfig, u1, v1);
   cdcClus2.GetUV(wireConfig, u2, v2);

   hough1.FindLine(cdcClus1.GetNumHits(), u1, v1);
   hough2.FindLine(cdcClus2.GetNumHits(), u2, v2);
   rotate_by(0, 0, -hough1.GetT()+TMath::Pi()/2.0, cdcClus1.GetNumHits(), u1, v1, u1rot, v1rot);
   rotate_by(0, 0, -hough2.GetT()+TMath::Pi()/2.0, cdcClus2.GetNumHits(), u2, v2, u2rot, v2rot);
   if (debug) {
      hough1.PrintHough();
      hough2.PrintHough();
   }

   cdc1Hough.CopyByHough(cdcClus1, hough1.GetR(), u1rot, v1rot, threshold, debug);
   cdc2Hough.CopyByHough(cdcClus2, hough2.GetR(), u2rot, v2rot, threshold, debug);

   cdc1Hough.GetXYend(wireConfig, x1end, y1end);
   cdc2Hough.GetXYend(wireConfig, x2end, y2end);

   circ1.FitCircle(cdc1Hough.GetNumHits(), x1end, y1end);
   circ2.FitCircle(cdc2Hough.GetNumHits(), x2end, y2end);
   if (debug) {
      circ1.PrintCircle();
      circ2.PrintCircle();
   }

   if (showEventCanvas) {
      c1.SetTitle(Form("iev %d",iev));
      c1.Divide(2,3);
      c1.cd(1); draw_frame("uv1;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); cdcClus1.DrawAny(u1, v1, 5); draw_line_TR(hough1.GetT(), hough1.GetR(), -0.05, 0.05, kRed, 1);
      c1.cd(2); draw_frame("uv2;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); cdcClus2.DrawAny(u2, v2, 5); draw_line_TR(hough2.GetT(), hough2.GetR(), -0.05, 0.05, kRed, 1);
      c1.cd(3); draw_frame("uv1rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); cdcClus1.DrawAny(u1rot, v1rot, 5); draw_line_AB2(0, hough1.GetR(), -0.05, 0.05, kRed, threshold);
      c1.cd(4); draw_frame("uv2rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); cdcClus2.DrawAny(u2rot, v2rot, 5); draw_line_AB2(0, hough2.GetR(), -0.05, 0.05, kRed, threshold);
      c1.cd(5); hough1.GetH2D_TR()->Draw("colz"); draw_marker(hough1.GetT(), hough1.GetR(), kRed, 24);
      c1.cd(6); hough2.GetH2D_TR()->Draw("colz"); draw_marker(hough2.GetT(), hough2.GetR(), kRed, 24);

      c2.SetTitle(Form("iev %d",iev));
      c2.Divide(2,2);
      c2.cd(1); wireConfig.DrawEndPlate("c1"); cdcClus1.DrawDriftCircles(wireConfig, "endplate", 0, 0);
      c2.cd(2); wireConfig.DrawEndPlate("c2"); cdcClus2.DrawDriftCircles(wireConfig, "endplate", 0, 0);
      c2.cd(3); wireConfig.DrawEndPlate("c3"); cdc1Hough.DrawDriftCircles(wireConfig, "endplate", 0, 0); draw_circle(circ1.GetX0Fit(), circ1.GetY0Fit(), circ1.GetRFit(), kRed, 0, 0);
      c2.cd(4); wireConfig.DrawEndPlate("c4"); cdc2Hough.DrawDriftCircles(wireConfig, "endplate", 0, 0); draw_circle(circ2.GetX0Fit(), circ2.GetY0Fit(), circ2.GetRFit(), kBlue, 0, 0);

      c1.Update();
      c2.Update();
      c1.Print("a1.pdf");
      c2.Print("a2.pdf");
   }

   return 0;
}

void run(int checking_num_turns, double threshold, int start_iev=0)
{
   int i=0;
   char c;
   for (int iev=start_iev; ;iev++) {
      int ret = event(iev, threshold, checking_num_turns);
      if (ret==-1) continue;
      if (ret==-2) break;
      printf("Type q to quit: ");
      if (i==0) getchar();
      c = getchar();
      printf("c -> '%c'\n", c);
      if (c=='q') break;
      i++;
   }
}

void get_sig_noise_ratio(double threshold)
{
   TCanvas* c1 = new TCavnas();
   c1->Divide(2,2);
   TH1F* h1 = new TH1F("h1","", 100, 0, 10);

   showEventCanvas=false;
   for (int iev=0; ;iev++) {
      event(iev,threshold,-1);
      int NA1 = cdcFA.GetNumHitsByTurn(-1,-1000);
      int NN1 = cdcFA.GetNumHitsByTurn(-1,-1);
      int NS1 = NA1-NN1;
      int NA2_1 = cdcClus1.GetNumHitsByTurn(-1,-1000);
      int NN2_1 = cdcClus1.GetNumHitsByTurn(-1,-1);
      int NS2_1 = NA2_1-NN2_1;
      int NA2_2 = cdcClus2.GetNumHitsByTurn(-1,-1000);
      int NN2_2 = cdcClus2.GetNumHitsByTurn(-1,-1);
      int NS2_2 = NA2_2-NN2_2;
      int NA2 = NA2_1 + NA2_2;
      int NN2 = NN2_1 + NN2_2;
      int NS2 = NS2_1 + NS2_2;
      int NA3_1 = cdcHough1.GetNumHitsByTurn(-1,-1000);
      int NN3_1 = cdcHough1.GetNumHitsByTurn(-1,-1);
      int NS3_1 = NA3_1-NN3_1;
      int NA3_2 = cdcHough2.GetNumHitsByTurn(-1,-1000);
      int NN3_2 = cdcHough2.GetNumHitsByTurn(-1,-1);
      int NS3_2 = NA3_2-NN3_2;
      int NA3 = NA3_1 + NA3_2;
      int NN3 = NN3_1 + NN3_2;
      int NS3 = NS3_1 + NS3_2;

   }
}
