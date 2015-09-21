#include "TRandom.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TVector3.h"
#include "TMatrixDSym.h"
#include "TPaveText.h"

#include "InitialHit.h"
#include "CounterHit.h"
#include "CdcHit.h"
#include "WireConfig.h"
#include "Fitter.h"

TCanvas* c1 = NULL;
TPad* pad1;
TPad* pad2;
TTree* t;
InitialHit initial;
CounterHit cheren;
CounterHit scinti;
CdcHit cdcSig;
CdcHit cdcFit;
WireConfig wireConfig;
Fitter fitter;

double fitZ[1000];

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

   char* geom_root = "geom_nowire_ver_2014_10_09_notilt_t1cm_media_mod.root";
   char* fieldmap_txt = "MyMagField/FieldMap_for_COMET_Phase1/fieldmap_by_IHEP_ver1/IHEP_A9_140905.txt";
   fitter.SetGeometry(geom_root);
   fitter.SetMagField(fieldmap_txt);
   fitter.SetMaterialEffects();

   opened=true;
}
int event(int iev, int checking_num_turns=-1)
{
   if (!opened) open();

   gRandom->SetSeed(1); // Use same seed => same rsmear and noise pattern

   cheren.Clear();
   scinti.Clear();
   cdcSig.Clear();
   cdcFit.Clear();

   t->GetEntry(iev);
   if (iev>=t->GetEntries()) return -2;
   if (cheren.GetNumHits()==0 || scinti.GetNumHits()==0 || cdcSig.GetNumHits()==0) return - 1;
   if (checking_num_turns !=-1 && cdcSig.GetNumTurns() != checking_num_turns) return -1;
   if (cdcSig.GetMaxLayer()<8) return -1;

   cdcSig.SetRsmear(0.02); // 200um

   TVector3 pos1(cdcSig.GetX(0), cdcSig.GetY(0), cdcSig.GetZ(0)); // cm
   TVector3 mom1(cdcSig.GetPx(0)*1e-3, cdcSig.GetPy(0)*1e-3, cdcSig.GetPz(0)*1e-3); // GeV
   TMatrixDSym cov1(6);
   cov1(0,0) = pow(0.2, 2); // x
   cov1(1,1) = pow(0.2, 2); // y
   cov1(2,2) = pow(0.2, 2); // z
   cov1(3,3) = pow(1.0, 2); // px
   cov1(4,4) = pow(1.0, 2); // py
   cov1(5,5) = pow(1.0, 2); // pz

   fitter.ClearEvent();
   fitter.SetTrack(pos1, mom1, cov1);

   int nhits = cdcSig.GetNumHits();
   printf("iev %d nhits %d\n", iev, nhits);

   for (int ihit=0; ihit<nhits; ihit++) {
      TVector3 w1, w2;
      int ilayer = cdcSig.GetIlayer(ihit);
      int icell = cdcSig.GetIcell(ihit);
      int iturn = cdcSig.GetIturn(ihit);
      wireConfig.GetWirePosAtEndplate(ilayer, icell, w1, w2);
      double dist = cdcSig.GetDist(ihit);
      double rerr = 0.02; // 200um
      fitter.AddHit(w1, w2, dist, rerr);
      printf("ihit %2d iturn %d ilayer %2d icell %3d dist %5.2f - w1 (%6.2f %6.2f %6.2f) w2 (%6.2f %6.2f %6.2f)\n", ihit, iturn, ilayer, icell, dist, w1.X(), w1.Y(), w1.Z(), w2.X(), w2.Y(), w2.Z());
   }

   fitter.DoFit();
   fitter.PrintResult();

   for (int ihit=0; ihit<nhits; ihit++) {
      int ilayer = cdcSig.GetIlayer(ihit);
      int icell = cdcSig.GetIcell(ihit);
      int iturn = cdcSig.GetIturn(ihit);
      double dist = fitter.GetDistFit(ihit);
      double x = fitter.GetXFit(ihit);
      double y = fitter.GetYFit(ihit);
      double z = fitter.GetZFit(ihit);
      double px = fitter.GetPxFit(ihit);
      double py = fitter.GetPyFit(ihit);
      double pz = fitter.GetPzFit(ihit);
      cdcFit.AddHit(ilayer, icell, iturn, dist, 0, x, y, z, px, py, pz);
   }

   // Draw
   if (c1==NULL) {
      int nx = 1;
      int ny = 1;
      c1 = new TCanvas("c1","", 500*nx, 500*ny);
      pad1 = new TPad("pad2","pad2", 0.00, 0.95, 1.00, 1.00); // title
      pad2 = new TPad("pad1","pad1", 0.00, 0.00, 1.00, 0.95); // body
      pad1->Draw();
      pad2->Draw();
   }
   pad1->cd(); TPaveText* pt = new TPaveText(0,0,1,1); pt->SetFillColor(0); pt->SetBorderSize(0); pt->AddText(Form("iev %d", iev)); pt->Draw();
   pad2->cd();
   wireConfig.DrawEndPlate("c1"); 
   cdcSig.DrawDriftCircles(wireConfig, "hitz", 0, 0);
   cdcFit.DrawDriftCircles(wireConfig, "hitz", 3001, 2);

   cdcSig.PrintHit("CDC Hit and Fit",cdcFit);
   c1->Print("b.pdf");

   return 0;
}
void run(int checking_num_turns)
{
   for (int iev=0; ;iev++) {
      int ret = event(iev, checking_num_turns);
      if (ret==-1) continue;
      if (ret==-2) break;
      printf("Type q to quit");
      char c = getchar();
      if (c=='q') break;
   }
}
