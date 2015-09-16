#include "Event.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TEllipse.h"

Event::Event(char* wire_config, char* root)
{
   ReadWireConfig(wire_config);
   ReadTree(root);
   SetupBranch();

   SetMarkerColor("1st_turn",kRed);
   SetMarkerColor("2nd_turn",kBlue);
   SetMarkerColor("3rd_turn",kGreen);
   SetMarkerColor("noise",kCyan);
};
void Event::ReadWireConfig(char* wire_config)
{
   fWireConfig.Init(wire_config);
};
void Event::ReadTree(char* root)
{
   TFile* f = new TFile(root);
   fTree = (TTree*)f->Get("t");
   if (fTree==NULL) {
      fprintf(stderr,"ERROR: No tree found\n");
   }
};
void Event::SetupBranch()
{
   fTree->SetBranchAddress("iev", &fIev);

   fTree->SetBranchAddress("trig_cherenkov_nhits", &fCheren_Nhits);
   fTree->SetBranchAddress("trig_cherenkov_time",   fCheren_Time);

   fTree->SetBranchAddress("trig_scinti_nhits", &fScinti_Nhits);
   fTree->SetBranchAddress("trig_scinti_time",   fScinti_Time);

   fTree->SetBranchAddress("nwirehit",   &fWire_Nhits);
   fTree->SetBranchAddress("ilayer",      fWire_Ilayer);
   fTree->SetBranchAddress("icell",       fWire_Icell);
   fTree->SetBranchAddress("iturn",       fWire_Iturn);
   fTree->SetBranchAddress("dist",        fWire_Dist);
   fTree->SetBranchAddress("time",        fWire_Time);
   fTree->SetBranchAddress("minhit_x",    fWire_Xhits);
   fTree->SetBranchAddress("minhit_y",    fWire_Yhits);
   fTree->SetBranchAddress("minhit_z",    fWire_Zhits);
   fTree->SetBranchAddress("minhit_px",   fWire_Pxhits);
   fTree->SetBranchAddress("minhit_py",   fWire_Pyhits);
   fTree->SetBranchAddress("minhit_pz",   fWire_Pzhits);
};
void Event::GetEntry(int iev)
{
   fTree->GetEntry(iev);
};
void Event::PrintEntry()
{
   printf("iev %d\n", fIev);

   printf("--scinti--\n");
   printf("nhits %d\n", fScinti_Nhits);
   for (int ihit=0; ihit<fScinti_Nhits; ihit++) {
      printf("ihit %3d time %6.2f x %6.2f y %6.2f z %6.2f px %6.2f py %6.2f pz %6.2f\n", 
            ihit,
            fScinti_Time[ihit],
            fScinti_Xhits[ihit],
            fScinti_Yhits[ihit],
            fScinti_Zhits[ihit],
            fScinti_Pxhits[ihit],
            fScinti_Pyhits[ihit],
            fScinti_Pzhits[ihit]);
   }

   printf("--cherenkov--\n");
   printf("nhits %d\n", fCheren_Nhits);
   for (int ihit=0; ihit<fCheren_Nhits; ihit++) {
      printf("ihit %3d time %6.2f x %6.2f y %6.2f z %6.2f px %6.2f py %6.2f pz %6.2f\n", 
            ihit,
            fCheren_Time[ihit],
            fCheren_Xhits[ihit],
            fCheren_Yhits[ihit],
            fCheren_Zhits[ihit],
            fCheren_Pxhits[ihit],
            fCheren_Pyhits[ihit],
            fCheren_Pzhits[ihit]);
   }

   printf("--wire--\n");
   printf("nhits %d\n", fWire_Nhits);
   for (int ihit=0; ihit<fWire_Nhits; ihit++) {
      printf("ihit %3d iturn %2d ilayer %2d icell %3d dist %6.2f time %6.2f x %6.2f y %6.2f z %6.2f px %6.2f py %6.2f pz %6.2f\n", 
            ihit, 
            fWire_Iturn[ihit], 
            fWire_Ilayer[ihit], 
            fWire_Icell[ihit], 
            fWire_Dist[ihit], 
            fWire_Time[ihit], 
            fWire_Xhits[ihit], 
            fWire_Yhits[ihit], 
            fWire_Zhits[ihit], 
            fWire_Pxhits[ihit], 
            fWire_Pyhits[ihit], 
            fWire_Pzhits[ihit]);
   }
};

int Event::GetNumTurns()
{
   int nhits = fWire_Nhits;
   if (nhits==0) return -1;
   return fWire_Iturn[nhits-1] + 1;
};
double Event::GetDist(int ihit)
{
   return fWire_Dist[ihit];
}

void Event::SetMarkerColor(char* category, int col)
{
   if (strcmp(category,"1st_turn")==0) mcol_1st_turn=col;
   if (strcmp(category,"2nd_turn")==0) mcol_2nd_turn=col;
   if (strcmp(category,"3rd_turn")==0) mcol_3rd_turn=col;
   if (strcmp(category,"noise")==0) mcol_noise=col;
}
void Event::DrawCanvas(char* canv_name, char* canv_title, double xmin, double ymin, double xmax, double ymax)
{
   double xwin = xmax-xmin;
   double ywin = ymax-ymin;
   TCanvas* c1 = new TCanvas(canv_name, canv_title, 800, 800*ywin/xwin);
   c1->DrawFrame(xmin, ymin, xmax, ymax);
}
void Event::DrawEndplate()
{
   for (int cid=0; cid<20; cid++) {
      if (cid%2==1) {
         double r = fWireConfig.GetLayerRadius(cid, LAYER_TYPE_SENSE, 0);
         TEllipse *e = new TEllipse(0,0,r);
         e->SetFillStyle(0);
         e->SetLineColor(kGray);
         e->Draw();
      }
   }
}
void Event::DrawMCHitsAt(const char* zorigin, double dz)
{
   for (int ihit=0; ihit<fWire_Nhits; ihit++) {
      double wx, wy;
      if (strcmp(zorigin,"MC")==0) {
         GetWirePos(fWire_Ilayer[ihit], fWire_Icell[ihit], fWire_Zhits[ihit], "center", wx, wy);
      } else {
         GetWirePos(fWire_Ilayer[ihit], fWire_Icell[ihit], dz, zorigin, wx, wy);
      }
      double wr = GetDist(ihit);

      //printf("ihit %d wx %f wy %f wr %f\n", ihit, wx, wy, wr);
      TEllipse* e = new TEllipse(wx, wy, wr);
      e->SetFillStyle(0);
      int mcol = kRed;

      int iturn = fWire_Iturn[ihit];
      if (iturn==-1) mcol = mcol_noise;
      else if (iturn==0) mcol = mcol_1st_turn;
      else if (iturn==1) mcol = mcol_2nd_turn;
      else if (iturn==2) mcol = mcol_3rd_turn;

      e->SetLineColor(mcol);
      e->Draw();
   }
};
void Event::DrawMCHits(int iev)
{
   GetEntry(iev);
   DrawCanvas("c1","MCHits");
   DrawEndplate();
   DrawMCHitsAt("MC", 0);
}

void Event::GetWirePos(int cid, int icell, double zpos_from_center, const char* zorigin, double& xwire, double& ywire)
{
   fWireConfig.GetWirePos(cid, LAYER_TYPE_SENSE, icell, WIRE_TYPE_SENSE, zpos_from_center, zorigin, &xwire, &ywire);
}

