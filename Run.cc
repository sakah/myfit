#include "Run.h"

static double u1[MAX_CDC_HIT];
static double v1[MAX_CDC_HIT];
static double u2[MAX_CDC_HIT];
static double v2[MAX_CDC_HIT];

static double u1rot[MAX_CDC_HIT];
static double v1rot[MAX_CDC_HIT];
static double u2rot[MAX_CDC_HIT];
static double v2rot[MAX_CDC_HIT];

static double x1end[MAX_CDC_HIT];
static double y1end[MAX_CDC_HIT];
static double x2end[MAX_CDC_HIT];
static double y2end[MAX_CDC_HIT];

Run::Run(const char* name):
   fTree(NULL),
   fWireConfig(),
   fInitial(),
   fCheren("Cherenkov"),
   fScinti("Scinti"),
   fNoiseOccupancy(0.10),
   fCdcNoise("CDC Noise"),
   fCdcSig("CDC Signal"),
   fCdcSigNoise("CDC Signal with Noise"),
   fCdcSigNoise1("CDC Signal with Noise (odd layers)"),
   fCdcSigNoise2("CDC Signal with Noise (even layers)"),
   fCdcFA1("CDC FirstArrived Hits (odd layers)"),
   fCdcFA2("CDC FirstArrived Hits (even layers)"),
   fCdcClus1("CDC Clusters (odd layers)"),
   fCdcClus2("CDC Clusters (even layers)"),
   fHough1("Hough (odd layers)"),
   fHough2("Hough (even layers)"),
   fCdcHough1("CDC after Hough (odd layers)"),
   fCdcHough2("CDC after Hough (even layers)"),
   fCirc1("Circle (odd layers)"),
   fCirc2("Circle (even layers)"),
   fCdcFit("CDC Fit"),
   fFitter(),
   fEvtCanOpened(false),
   fEvtCan1(),
   fEvtCan2(),
   fNumAll1(NULL),
   fNumSig1(NULL),
   fNumNoi1(NULL),
   fNumRem1(NULL),
   fNumAll2(NULL),
   fNumSig2(NULL),
   fNumNoi2(NULL),
   fNumRem2(NULL),
   fNumAll3(NULL),
   fNumSig3(NULL),
   fNumNoi3(NULL),
   fNumRem3(NULL),
   fPtResid1(NULL),
   fPtResid2(NULL),
   fPtResol1(NULL),
   fPtResol2(NULL),
   fRunCanOpened(false),
   fRunCan1()
{
   strcpy(fRunName, name);
   Open();
   BookHist();
}


int Run::ProcessEvent(int iev, int checking_num_turns, double threshold, bool show_event_canvas, bool debug)
{
   ClearEvent();

   fEventNumber = iev;
   fHoughThreshold = threshold;

   gRandom->SetSeed(1); // Use same seed => same rsmear and noise pattern

   fTree->GetEntry(iev);
   printf("iev %4d nhits %3d nturns %2d nscinti %d nchren %d\n", iev, fCdcSig.GetNumHits(), fCdcSig.GetNumTurns(), fScinti.GetNumHits(), fCheren.GetNumHits());
   if (iev>=fTree->GetEntries()) return -2;
   if (fCheren.GetNumHits()==0 || fScinti.GetNumHits()==0 || fCdcSig.GetNumHits()==0) return - 1;
   if (checking_num_turns !=-1 && fCdcSig.GetNumTurns() != checking_num_turns) return -1;
   if (fCdcSig.GetMaxLayer()<8) return -1;

   if (debug) {
      fInitial.PrintHit();
      fScinti.PrintHit();
      fCheren.PrintHit();
   }

   fCdcSig.SetRsmear(0.02);
   fCdcNoise.MakeNoise(fWireConfig, fNoiseOccupancy);
   fCdcSigNoise.Merge(fCdcSig, fCdcNoise);
   fCdcSigNoise1.CopyByLayer(fCdcSigNoise, 1);
   fCdcSigNoise2.CopyByLayer(fCdcSigNoise, 0);
   if (debug) {
      fCdcSig.PrintHit();
      fCdcNoise.PrintHit();
      fCdcSigNoise.PrintHit();
      fCdcSigNoise1.PrintHit();
      fCdcSigNoise2.PrintHit();
   }

   fCdcFA1.CopyByFirstArrivedHit(fCdcSigNoise1, fScinti.GetT(0));
   fCdcFA2.CopyByFirstArrivedHit(fCdcSigNoise2, fScinti.GetT(0));
   fCdcClus1.CopyByClusters(fWireConfig, fCdcFA1);
   fCdcClus2.CopyByClusters(fWireConfig, fCdcFA2);
   if (debug) {
      fCdcSigNoise.PrintHit();
      fCdcFA1.PrintHit();
      fCdcFA2.PrintHit();
      fCdcClus1.PrintHit();
      fCdcClus2.PrintHit();
   }

   fCdcClus1.GetUV(fWireConfig, u1, v1);
   fCdcClus2.GetUV(fWireConfig, u2, v2);

   fHough1.FindLine(fCdcClus1.GetNumHits(), u1, v1);
   fHough2.FindLine(fCdcClus2.GetNumHits(), u2, v2);
   rotate_by(0, 0, -fHough1.GetT()+TMath::Pi()/2.0, fCdcClus1.GetNumHits(), u1, v1, u1rot, v1rot);
   rotate_by(0, 0, -fHough2.GetT()+TMath::Pi()/2.0, fCdcClus2.GetNumHits(), u2, v2, u2rot, v2rot);
   if (debug) {
      fHough1.PrintHough();
      fHough2.PrintHough();
   }

   fCdcHough1.CopyByHough(fCdcClus1, fHough1.GetR(), u1rot, v1rot, threshold, debug);
   fCdcHough2.CopyByHough(fCdcClus2, fHough2.GetR(), u2rot, v2rot, threshold, debug);

   fCdcHough1.GetXYend(fWireConfig, x1end, y1end);
   fCdcHough2.GetXYend(fWireConfig, x2end, y2end);

   fCirc1.FitCircle(fCdcHough1.GetNumHits(), x1end, y1end);
   fCirc2.FitCircle(fCdcHough2.GetNumHits(), x2end, y2end);
   if (debug) {
      fCirc1.PrintCircle();
      fCirc2.PrintCircle();
   }

   if (show_event_canvas) {
      ShowEventCanvas();
   }

   FillHist();

   return 0;
}

void Run::ProcessEvents(int checking_num_turns, double threshold, int start_iev, bool stop_every_event, bool show_event_canvas, bool show_run_canvas, bool debug)
{
   ClearRun();

   int i=0;
   for (int iev=start_iev; ;iev++) {
      int ret = ProcessEvent(iev, checking_num_turns, threshold, show_event_canvas, debug);
      if (ret==-1) continue;
      if (ret==-2) break;
      if (stop_every_event) {
         printf("Type q to quit: ");
         if (i==0) getchar();
         char c = getchar();
         printf("c -> '%c'\n", c);
         if (c=='q') break;
      }
      i++;
   }

   if (show_run_canvas) {
      ShowRunCanvas();
   }
}

void Run::Open()
{
   char* wire_config = "B1T_square_1.5m_ver_2014_03_28.txt";
   fWireConfig.Init(wire_config);

   char* root = "root/hoge1-0.root";
   TFile* f = new TFile(root);
   fTree = (TTree*)f->Get("t");

   fInitial.SetBranchAddress(fTree, "ini_x_cm", "ini_y_cm", "ini_z_cm", "ini_px_GeV", "ini_py_GeV", "ini_pz_GeV");
   fScinti.SetBranchAddressAll(fTree, "trig_scinti_nhits", "trig_scinti_time", "trig_scinti_posx", "trig_scinti_posy", "trig_scinti_posz", "trig_scinti_momx", "trig_scinti_momy", "trig_scinti_momz");
   fCheren.SetBranchAddressAll(fTree, "trig_cherenkov_nhits", "trig_cherenkov_time", "trig_cherenkov_posx", "trig_cherenkov_posy", "trig_cherenkov_posz", "trig_cherenkov_momx", "trig_cherenkov_momy", "trig_cherenkov_momz");
   fCdcSig.SetBranchAddressAll(fTree, "nwirehit", "time", "minhit_x", "minhit_y", "minhit_z", "minhit_px", "minhit_py", "minhit_pz", "ilayer", "icell", "iturn", "dist");
}

void Run::BookHist()
{
   fNumAll1 = new TH1F("NumAll1", "All Raw;#/Hits;Entries", 50, 400, 600);
   fNumSig1 = new TH1F("NumSig1", "Signal Raw;#/Signal;Entries", 50, 0, 100);
   fNumNoi1 = new TH1F("NumNoi1", "Noise Raw;#/Noise;Entries", 50, 400, 500);
   fNumRem1 = new TH1F("NumNoi1", "Signal Removed Raw;#/Signal Removed;Entries", 20, 0, 20);
   fNumAll2 = new TH1F("NumAll2", "All After Clustering;#/Hits;Entries", 50, 0, 200);
   fNumSig2 = new TH1F("NumSig2", "Signal After Clustering;#/Signal;Entries", 50, 0, 100);
   fNumNoi2 = new TH1F("NumNoi2", "Noise After Clustering;#/Noise;Entries", 50, 0, 200);
   fNumRem2 = new TH1F("NumRem2", "Signal Removed After Clustering;#/Signal Removed;Entries", 20, 0, 20);
   fNumAll3 = new TH1F("NumAll3", "All After Hough trans.;#/Hits;Entries", 50, 0, 200);
   fNumSig3 = new TH1F("NumSig3", "Signal After Hough trans.;#/Signal;Entries", 50, 0, 100);
   fNumNoi3 = new TH1F("NumNoi3", "Noise After Hough trans.;#/Noise;Entries", 50, 0, 50);
   fNumRem3 = new TH1F("NumRem3", "Signal Removed After Hough trans.;#/Signal Removed;Entries", 20, 0, 20);

   fPtResid1 = new TH1F("PtResid1","pt Residual (odd layers);pt_fit-pt_hit (MeV/c); Entries", 100, -50,50);
   fPtResid2 = new TH1F("PtResid2","pt Residual (even layers);pt_fit-pt_hit (MeV/c); Entries", 100, -50,50);
   fPtResol1 = new TH1F("PtResol1","pt Resolution (odd layers);(pt_fit-pt_hit)/pt_hit; Entries", 100, -1,1);
   fPtResol2 = new TH1F("PtResol2","pt Resolution (even layers);(pt_fit-pt_hit)/pt_hit; Entries", 100, -1,1);
}

void Run::ClearEvent()
{
   fCheren.Clear();
   fScinti.Clear();
   fCdcNoise.Clear();
   fCdcSig.Clear();
   fCdcSigNoise.Clear();
   fCdcSigNoise1.Clear();
   fCdcSigNoise2.Clear();
   fCdcFA1.Clear();
   fCdcFA2.Clear();
   fCdcClus1.Clear();
   fCdcClus2.Clear();
   fCdcHough1.Clear();
   fCdcHough2.Clear();
}

void Run::ClearRun()
{
   fNumAll1->Reset();
   fNumSig1->Reset();
   fNumNoi1->Reset();
   fNumRem1->Reset();

   fNumAll2->Reset();
   fNumSig2->Reset();
   fNumNoi2->Reset();
   fNumRem2->Reset();

   fNumAll3->Reset();
   fNumSig3->Reset();
   fNumNoi3->Reset();
   fNumRem3->Reset();
}

void Run::ShowEventCanvas()
{
   if (!fEvtCanOpened) {
      fEvtCan1.Setup(Form("c1-%s",fRunName),"c1",   0, 0, 600, 600);
      fEvtCan2.Setup(Form("c2-%s",fRunName),"c2", 600, 0, 600, 600);
      fEvtCanOpened=true;
   }
   fEvtCan1.SetTitle(Form("iev %d (%s)",fEventNumber, fRunName));
   fEvtCan1.Divide(2,3);
   fEvtCan1.cd(1); draw_frame("uv1;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcClus1.DrawAny(u1, v1, 5); draw_line_TR(fHough1.GetT(), fHough1.GetR(), -0.05, 0.05, kRed, 1);
   fEvtCan1.cd(2); draw_frame("uv2;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcClus2.DrawAny(u2, v2, 5); draw_line_TR(fHough2.GetT(), fHough2.GetR(), -0.05, 0.05, kRed, 1);
   fEvtCan1.cd(3); draw_frame("uv1rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcClus1.DrawAny(u1rot, v1rot, 5); draw_line_AB2(0, fHough1.GetR(), -0.05, 0.05, kRed, fHoughThreshold);
   fEvtCan1.cd(4); draw_frame("uv2rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcClus2.DrawAny(u2rot, v2rot, 5); draw_line_AB2(0, fHough2.GetR(), -0.05, 0.05, kRed, fHoughThreshold);
   fEvtCan1.cd(5); fHough1.GetH2D_TR()->Draw("colz"); draw_marker(fHough1.GetT(), fHough1.GetR(), kRed, 24);
   fEvtCan1.cd(6); fHough2.GetH2D_TR()->Draw("colz"); draw_marker(fHough2.GetT(), fHough2.GetR(), kRed, 24);

   fEvtCan2.SetTitle(Form("iev %d (%s)",fEventNumber, fRunName));
   fEvtCan2.Divide(4,2);
   fEvtCan2.cd(1); fWireConfig.DrawEndPlate("c1"); fCdcSigNoise1.DrawDriftCircles(fWireConfig, "endplate", 0, 0);
   fEvtCan2.cd(2); fWireConfig.DrawEndPlate("c2"); fCdcFA1.DrawDriftCircles(fWireConfig, "endplate", 0, 0);
   fEvtCan2.cd(3); fWireConfig.DrawEndPlate("c3"); fCdcClus1.DrawDriftCircles(fWireConfig, "endplate", 0, 0);
   fEvtCan2.cd(4); fWireConfig.DrawEndPlate("c4"); fCdcHough1.DrawDriftCircles(fWireConfig, "endplate", 0, 0); draw_circle(fCirc1.GetX0Fit(), fCirc1.GetY0Fit(), fCirc1.GetRFit(), kBlue, 0, 0);
   fEvtCan2.cd(5); fWireConfig.DrawEndPlate("c5"); fCdcSigNoise2.DrawDriftCircles(fWireConfig, "endplate", 0, 0);
   fEvtCan2.cd(6); fWireConfig.DrawEndPlate("c6"); fCdcFA2.DrawDriftCircles(fWireConfig, "endplate", 0, 0);
   fEvtCan2.cd(7); fWireConfig.DrawEndPlate("c7"); fCdcClus2.DrawDriftCircles(fWireConfig, "endplate", 0, 0);
   fEvtCan2.cd(8); fWireConfig.DrawEndPlate("c8"); fCdcHough2.DrawDriftCircles(fWireConfig, "endplate", 0, 0); draw_circle(fCirc2.GetX0Fit(), fCirc2.GetY0Fit(), fCirc2.GetRFit(), kBlue, 0, 0);

   fEvtCan1.Update();
   fEvtCan2.Update();
   fEvtCan1.Print("a1.pdf");
   fEvtCan2.Print("a2.pdf");
}

void Run::FillHist()
{
   int NA1 = fCdcFA1.GetNumHits()   + fCdcFA2.GetNumHits();
   int NS1 = fCdcFA1.GetNumSignal() + fCdcFA2.GetNumSignal();
   int NN1 = fCdcFA1.GetNumNoise()  + fCdcFA2.GetNumNoise();
   int NA2 = fCdcClus1.GetNumHits()   + fCdcClus2.GetNumHits();
   int NS2 = fCdcClus1.GetNumSignal() + fCdcClus2.GetNumSignal();
   int NN2 = fCdcClus1.GetNumNoise()  + fCdcClus2.GetNumNoise();
   int NA3 = fCdcHough1.GetNumHits()   + fCdcHough2.GetNumHits();
   int NS3 = fCdcHough1.GetNumSignal() + fCdcHough2.GetNumSignal();
   int NN3 = fCdcHough1.GetNumNoise()  + fCdcHough2.GetNumNoise();
   printf("iev %4d NA1 %3d NS1 %3d NN1 %3d\n", fEventNumber, NA1, NS1, NN1);
   printf("iev %4d NA2 %3d NS2 %3d NN2 %3d\n", fEventNumber, NA2, NS2, NN2);
   printf("iev %4d NA3 %3d NS3 %3d NN3 %3d\n", fEventNumber, NA3, NS3, NN3);

   fNumAll1->Fill(NA1);
   fNumSig1->Fill(NS1);
   fNumNoi1->Fill(NN1);
   fNumRem1->Fill(NS1-NS1); // always 0

   fNumAll2->Fill(NA2);
   fNumSig2->Fill(NS2);
   fNumNoi2->Fill(NN2);
   fNumRem2->Fill(NS1-NS2);

   fNumAll3->Fill(NA3);
   fNumSig3->Fill(NS3);
   fNumNoi3->Fill(NN3);
   fNumRem3->Fill(NS1-NS3);

   double pt_mc = fCdcSig.GetPt(0); // MeV/c
   double pt_fit1 = fCirc1.GetRFit()*3.0*1.0; // MeV/c
   double pt_fit2 = fCirc2.GetRFit()*3.0*1.0; // MeV/c
   fPtResid1->Fill(pt_fit1-pt_mc);
   fPtResid2->Fill(pt_fit2-pt_mc);
   fPtResol1->Fill((pt_fit1-pt_mc)/pt_mc);
   fPtResol2->Fill((pt_fit2-pt_mc)/pt_mc);
}

void Run::ShowRunCanvas()
{
   if (!fRunCanOpened) {
      fRunCan1.Setup(Form("c3-%s", fRunName),"c3",   0, 0, 600, 600);
      fRunCan2.Setup(Form("c4-%s", fRunName),"c4", 600, 0, 600, 600);
      fRunCanOpened=true;
   }
   fRunCan1.SetTitle(fRunName);
   fRunCan1.Divide(4,3);
   fRunCan1.cd(1); fNumAll1->Draw();
   fRunCan1.cd(2); fNumSig1->Draw();
   fRunCan1.cd(3); fNumNoi1->Draw();
   fRunCan1.cd(4); fNumRem1->Draw();
   fRunCan1.cd(5); fNumAll2->Draw();
   fRunCan1.cd(6); fNumSig2->Draw();
   fRunCan1.cd(7); fNumNoi2->Draw();
   fRunCan1.cd(8); fNumRem2->Draw();
   fRunCan1.cd(9); fNumAll3->Draw();
   fRunCan1.cd(10);fNumSig3->Draw();
   fRunCan1.cd(11);fNumNoi3->Draw();
   fRunCan1.cd(12);fNumRem3->Draw();

   gStyle->SetOptFit(1);
   fRunCan2.SetTitle(fRunName);
   fRunCan2.Divide(2,2);
   fRunCan2.cd(1); fPtResid1->Fit("gaus");
   fRunCan2.cd(2); fPtResid2->Fit("gaus");
   fRunCan2.cd(3); fPtResol1->Fit("gaus");
   fRunCan2.cd(4); fPtResol2->Fit("gaus");

   fRunCan1.Print("b1.pdf");
   fRunCan2.Print("b2.pdf");
}

