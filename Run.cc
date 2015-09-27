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
   fCdcFA("CDC Hits FirstArrived"),
   fCdcCL("CDC Hits making clusters"),
   fCdcCL1("CDC Hits making (odd-layer)"),
   fCdcCL2("CDC Hits making (even-layer)"),
   fHough1("Hough (odd layers)"),
   fHough2("Hough (even layers)"),
   fCdcHO("CDC after Hough"),
   fCdcHO1("CDC Hits after Hough (odd layers)"),
   fCdcHO2("CDC Hits after Hough (even layers)"),
   fCirc11("Circle fit 1st (odd layers)"),
   fCirc12("Circle fit 1st (even layers)"),
   fCirc21("Circle fit 2nd (odd layers)"),
   fCirc22("Circle fit 2nd (even layers)"),
   fCdcCF("CDC Hits after 1st cirlce fit"),
   fCdcCF1("CDC Hits after 1st cirlce fit (odd layers)"),
   fCdcCF2("CDC Hits after 1st cirlce fit (even layers)"),
   fFitter(),
   fEvtCanOpened(false),
   fEvtCan1(),
   fEvtCan2(),
   fShowEventCanvas(true)
{
   strcpy(fRunName, name);
   Open();
}


int Run::ProcessEvent(int iev, int checking_num_turns, double thre_hough, double thre_circ)
{
   bool debug=false;

   ClearEvent();

   fEventNumber = iev;
   fHoughThreshold = thre_hough;
   fCircleThreshold = thre_circ;

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
   fCdcFA.CopyByFirstArrivedHit(fCdcSigNoise, fScinti.GetT(0));
   fCdcCL.CopyByClusters(fWireConfig, fCdcFA);
   if (debug) {
      //fCdcSig.PrintHit();
      //fCdcNoise.PrintHit();
      //fCdcSigNoise.PrintHit();
      //fCdcFA.PrintHit();
      fCdcCL.PrintHit();
   }

   fCdcCL1.CopyByLayer(fCdcCL, 1);
   fCdcCL2.CopyByLayer(fCdcCL, 0);

   fCdcCL1.GetUV(fWireConfig, u1, v1);
   fCdcCL2.GetUV(fWireConfig, u2, v2);

   fHough1.FindLine(fCdcCL1.GetNumHits(), u1, v1);
   fHough2.FindLine(fCdcCL2.GetNumHits(), u2, v2);
   rotate_by(0, 0, -fHough1.GetT()+TMath::Pi()/2.0, fCdcCL1.GetNumHits(), u1, v1, u1rot, v1rot);
   rotate_by(0, 0, -fHough2.GetT()+TMath::Pi()/2.0, fCdcCL2.GetNumHits(), u2, v2, u2rot, v2rot);
   if (debug) {
      fHough1.PrintHough();
      fHough2.PrintHough();
   }

   fCdcHO1.CopyByHough(fCdcCL1, fHough1.GetR(), u1rot, v1rot, thre_hough, debug);
   fCdcHO2.CopyByHough(fCdcCL2, fHough2.GetR(), u2rot, v2rot, thre_hough, debug);
   fCdcHO.Merge(fCdcHO1, fCdcHO2);

   fCdcHO1.GetXYend(fWireConfig, x1end, y1end);
   fCdcHO2.GetXYend(fWireConfig, x2end, y2end);

   fCirc11.FitCircle(fCdcHO1.GetNumHits(), x1end, y1end);
   fCirc12.FitCircle(fCdcHO2.GetNumHits(), x2end, y2end);
   if (debug) {
      fCirc11.PrintCircle();
      fCirc12.PrintCircle();
   }
   fCdcCF1.CopyByCircle(fCdcHO1, x1end, y1end, fCirc11.GetX0Fit(), fCirc11.GetY0Fit(), fCirc11.GetRFit(), thre_circ, debug);
   fCdcCF2.CopyByCircle(fCdcHO2, x2end, y2end, fCirc12.GetX0Fit(), fCirc12.GetY0Fit(), fCirc12.GetRFit(), thre_circ, debug);
   fCdcCF.Merge(fCdcCF1, fCdcCF2);

   fCdcCF1.GetXYend(fWireConfig, x1end, y1end);
   fCdcCF2.GetXYend(fWireConfig, x2end, y2end);
   fCirc21.FitCircle(fCdcCF1.GetNumHits(), x1end, y1end);
   fCirc22.FitCircle(fCdcCF2.GetNumHits(), x2end, y2end);
   if (debug) {
      fCirc21.PrintCircle();
      fCirc22.PrintCircle();
   }

   if (fShowEventCanvas) {
      DrawEventCanvas();
   }

   return 0;
}

void Run::ShowEvents(int start_iev, int checking_num_turns, double thre_hough, double thre_circ)
{
   fShowEventCanvas = true;

   int i=0;
   for (int iev=start_iev; ;iev++) {
      int ret = ProcessEvent(iev, checking_num_turns, thre_hough, thre_circ);
      if (ret==-1) continue;
      if (ret==-2) break;
      if (fShowEventCanvas) {
         printf("Type q to quit: ");
         if (i==0) getchar();
         char c = getchar();
         printf("c -> '%c'\n", c);
         if (c=='q') break;
      }
      i++;
   }
}

void Run::ProcessEvents(int start_iev, int checking_num_turns, double thre_hough, double thre_circ)
{
   fShowEventCanvas=false;
   bool debug=false;
   for (int iev=start_iev; ;iev++) {
      int ret = ProcessEvent(iev, checking_num_turns, thre_hough, thre_circ);
      if (ret==-1) continue;
      if (ret==-2) break;
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

void Run::ClearEvent()
{
   fCheren.Clear();
   fScinti.Clear();
   fCdcNoise.Clear();
   fCdcSig.Clear();
   fCdcSigNoise.Clear();
   fCdcFA.Clear();
   fCdcCL.Clear();
   fCdcCL1.Clear();
   fCdcCL2.Clear();
   fCdcHO.Clear();
   fCdcHO1.Clear();
   fCdcHO2.Clear();
   fCdcCF.Clear();
   fCdcCF1.Clear();
   fCdcCF2.Clear();
}

void Run::DrawEventCanvas()
{
   if (!fEvtCanOpened) {
      fEvtCan1.Setup(Form("c1-%s",fRunName),"c1",   0, 0, 600, 600);
      fEvtCan2.Setup(Form("c2-%s",fRunName),"c2", 600, 0, 1000, 1000);
      fEvtCanOpened=true;
   }
   fEvtCan1.SetTitle(Form("iev %d (%s)",fEventNumber, fRunName));
   fEvtCan1.Divide(2,3);
   fEvtCan1.cd(1); draw_frame("uv1;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcCL1.DrawAny(u1, v1, 5); draw_line_TR(fHough1.GetT(), fHough1.GetR(), -0.05, 0.05, kRed, 1);
   fEvtCan1.cd(2); draw_frame("uv2;u;v", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcCL2.DrawAny(u2, v2, 5); draw_line_TR(fHough2.GetT(), fHough2.GetR(), -0.05, 0.05, kRed, 1);
   fEvtCan1.cd(3); draw_frame("uv1rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcCL1.DrawAny(u1rot, v1rot, 5); draw_line_AB2(0, fHough1.GetR(), -0.05, 0.05, kRed, fHoughThreshold);
   fEvtCan1.cd(4); draw_frame("uv2rot;urot;vrot", 100, -0.05, 0.05, 100, -0.05, 0.05); fCdcCL2.DrawAny(u2rot, v2rot, 5); draw_line_AB2(0, fHough2.GetR(), -0.05, 0.05, kRed, fHoughThreshold);
   fEvtCan1.cd(5); fHough1.GetH2D_TR()->Draw("colz"); draw_marker(fHough1.GetT(), fHough1.GetR(), kRed, 24);
   fEvtCan1.cd(6); fHough2.GetH2D_TR()->Draw("colz"); draw_marker(fHough2.GetT(), fHough2.GetR(), kRed, 24);

   fEvtCan2.SetTitle(Form("iev %d (%s)",fEventNumber, fRunName));
   fEvtCan2.Divide(4,2);
   int n=1;
   const char* z_origin = "endplate";
   int fill_style = 0;
   int fill_color = 0;
   const char* opt_txt = "layer cell cell_dist";
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c1"); fCdcFA.DrawDriftCircles(1, fWireConfig, z_origin, fill_style, fill_color, opt_txt);
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c2"); fCdcCL.DrawDriftCircles(1, fWireConfig, z_origin, fill_style, fill_color, opt_txt);
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c3"); fCdcHO.DrawDriftCircles(1, fWireConfig, z_origin, fill_style, fill_color, opt_txt); draw_circle(fCirc11.GetX0Fit(), fCirc11.GetY0Fit(), fCirc11.GetRFit(), kBlue, 0, 0);
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c4"); fCdcCF.DrawDriftCircles(1, fWireConfig, z_origin, fill_style, fill_color, opt_txt); draw_circle(fCirc21.GetX0Fit(), fCirc21.GetY0Fit(), fCirc21.GetRFit(), kBlue, 0, 0);
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c5"); fCdcFA.DrawDriftCircles(0, fWireConfig, z_origin, fill_style, fill_color, opt_txt);
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c6"); fCdcCL.DrawDriftCircles(0, fWireConfig, z_origin, fill_style, fill_color, opt_txt);
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c7"); fCdcHO.DrawDriftCircles(0, fWireConfig, z_origin, fill_style, fill_color, opt_txt); draw_circle(fCirc12.GetX0Fit(), fCirc12.GetY0Fit(), fCirc12.GetRFit(), kBlue, 0, 0);
   fEvtCan2.cd(n++); fWireConfig.DrawEndPlate("c8"); fCdcCF.DrawDriftCircles(0, fWireConfig, z_origin, fill_style, fill_color, opt_txt); draw_circle(fCirc22.GetX0Fit(), fCirc22.GetY0Fit(), fCirc22.GetRFit(), kBlue, 0, 0);

   fEvtCan1.Update();
   fEvtCan2.Update();
   fEvtCan1.Print("a1.pdf");
   fEvtCan2.Print("a2.pdf");
}
