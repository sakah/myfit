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

   SetMarkerColor("default", kGray);
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
   fTree->SetBranchAddress("dist",        fWire_MCDist);
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
   
   for (int ihit=0; ihit<fWire_Nhits; ihit++) {
      double dtime1 = GetDriftTime(ihit) + fWire_Time[ihit] - GetTrigTime();
      SetDriftTimeWithTOF(ihit, dtime1);
      SetDist(ihit, GetMCDist(ihit));
      fWire_FirstArrived[ihit] = 0;
   }
};
void Event::CheckPileup()
{
   int num_hits[20][500];
   double times[20][500][10];
   int idx[20][500][10];
   for (int ilayer=0; ilayer<20; ilayer++) {
      for (int icell=0; icell<500; icell++) {
         num_hits[ilayer][icell] = 0;
      }
   }
   for (int ihit=0; ihit<fWire_Nhits; ihit++) {
      int ilayer = fWire_Ilayer[ihit];
      int icell = fWire_Icell[ihit];
      int iturn = fWire_Iturn[ihit];
      double dtime = GetDriftTimeWithTOF(ihit);
      int n = num_hits[ilayer][icell];
      times[ilayer][icell][n] = dtime;
      idx[ilayer][icell][n] = ihit;
      num_hits[ilayer][icell]++;
   }
   for (int ilayer=0; ilayer<20; ilayer++) {
      for (int icell=0; icell<500; icell++) {
         int nhits = num_hits[ilayer][icell];
         //if (ilayer==2 && icell==192) printf("HOGE =--> nhits %d\n", nhits);
         if (nhits==0) continue;
         double min_time=1e10;
         int min_idx=idx[ilayer][icell][0];
         for (int ihit=0; ihit<nhits; ihit++) {
            double this_time = times[ilayer][icell][ihit];
            if (this_time < min_time) {
               min_time = this_time;
               min_idx = idx[ilayer][icell][ihit];
            }
         }
         fWire_FirstArrived[min_idx] = 1;
      }
   }
}
void Event::CopyEventInfo(Event& oe)
{
      fTree = oe.fTree;
      fIev = oe.fIev;

      fMC_Nhits = oe.fMC_Nhits;
      for (int ihit=0; ihit<fMC_Nhits; ihit++) {
         fMC_Time[ihit]   = oe.fMC_Time[ihit];
         fMC_Xhits[ihit]  = oe.fMC_Xhits[ihit];
         fMC_Yhits[ihit]  = oe.fMC_Yhits[ihit];
         fMC_Zhits[ihit]  = oe.fMC_Zhits[ihit];
         fMC_Pxhits[ihit] = oe.fMC_Pxhits[ihit];
         fMC_Pyhits[ihit] = oe.fMC_Pyhits[ihit];
         fMC_Pzhits[ihit] = oe.fMC_Pzhits[ihit];
      }

      fScinti_Nhits = oe.fScinti_Nhits;
      for (int ihit=0; ihit<fScinti_Nhits; ihit++) {
         fScinti_Time[ihit]   = oe.fScinti_Time[ihit];
         fScinti_Xhits[ihit]  = oe.fScinti_Xhits[ihit];
         fScinti_Yhits[ihit]  = oe.fScinti_Yhits[ihit];
         fScinti_Zhits[ihit]  = oe.fScinti_Zhits[ihit];
         fScinti_Pxhits[ihit] = oe.fScinti_Pxhits[ihit];
         fScinti_Pyhits[ihit] = oe.fScinti_Pyhits[ihit];
         fScinti_Pzhits[ihit] = oe.fScinti_Pzhits[ihit];
      }

      fCheren_Nhits = oe.fCheren_Nhits;
      for (int ihit=0; ihit<fCheren_Nhits; ihit++) {
         fCheren_Time[ihit]   = fCheren_Time[ihit];
         fCheren_Xhits[ihit]  = fCheren_Xhits[ihit];
         fCheren_Yhits[ihit]  = fCheren_Yhits[ihit];
         fCheren_Zhits[ihit]  = fCheren_Zhits[ihit];
         fCheren_Pxhits[ihit] = fCheren_Pxhits[ihit];
         fCheren_Pyhits[ihit] = fCheren_Pyhits[ihit];
         fCheren_Pzhits[ihit] = fCheren_Pzhits[ihit];
      }

      mcol_default = oe.mcol_default;
      mcol_1st_turn = oe.mcol_1st_turn;
      mcol_2nd_turn = oe.mcol_2nd_turn;
      mcol_3rd_turn = oe.mcol_3rd_turn;
      mcol_noise = oe.mcol_noise;
}
void Event::AddWireHit(int ihit, Event& oe)
{
      int nhit = fWire_Nhits;

      fWire_Ilayer[nhit]            = oe.fWire_Ilayer[ihit];
      fWire_Icell[nhit]             = oe.fWire_Icell[ihit];
      fWire_Iturn[nhit]             = oe.fWire_Iturn[ihit];
      fWire_MCDist[nhit]            = oe.fWire_MCDist[ihit];
      fWire_Time[nhit]              = oe.fWire_Time[ihit];
      fWire_Xhits[nhit]             = oe.fWire_Xhits[ihit];
      fWire_Yhits[nhit]             = oe.fWire_Yhits[ihit];
      fWire_Zhits[nhit]             = oe.fWire_Zhits[ihit];
      fWire_Pxhits[nhit]            = oe.fWire_Pxhits[ihit];
      fWire_Pyhits[nhit]            = oe.fWire_Pyhits[ihit];
      fWire_Pzhits[nhit]            = oe.fWire_Pzhits[ihit];
      fWire_DriftTimeWithTOF[nhit]  = oe.fWire_DriftTimeWithTOF[ihit];
      fWire_FirstArrived[nhit]      = oe.fWire_FirstArrived[ihit];
      fWire_Dist[nhit]              = oe.fWire_Dist[ihit];

      fWire_Nhits++;
};
void Event::GetEntryWithRemovingPileup(Event& oe)
{
   CopyEventInfo(oe);
   oe.CheckPileup();

   fWire_Nhits = 0;
   for (int ihit=0; ihit<oe.fWire_Nhits; ihit++) {
      int first_arrived = oe.fWire_FirstArrived[ihit];
      if (first_arrived==1) {
         AddWireHit(ihit, oe);
      }
   }
};

void Event::PrintWireHit(int ihit)
{
   printf("ihit %3d FA %d iturn %2d ilayer %2d icell %3d mcdist %6.2f dist %6.2f tof %6.2f tof-trig %6.2f dtime %6.2f dtime+tof-trig %6.2f x %6.2f y %6.2f z %6.2f px %6.2f py %6.2f pz %6.2f\n", 
         ihit, 
         fWire_FirstArrived[ihit],
         fWire_Iturn[ihit], 
         fWire_Ilayer[ihit], 
         fWire_Icell[ihit], 
         fWire_MCDist[ihit], 
         fWire_Dist[ihit], 
         fWire_Time[ihit], 
         fWire_Time[ihit]-GetTrigTime(), 
         GetDriftTime(ihit),
         fWire_DriftTimeWithTOF[ihit], 
         fWire_Xhits[ihit], 
         fWire_Yhits[ihit], 
         fWire_Zhits[ihit], 
         fWire_Pxhits[ihit], 
         fWire_Pyhits[ihit], 
         fWire_Pzhits[ihit]);
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
   printf("nturn %d nhits %d\n", GetNumTurns(), fWire_Nhits);
   for (int ihit=0; ihit<fWire_Nhits; ihit++) {
      PrintWireHit(ihit);
   }
};

int Event::GetNumTurns()
{
   int nhits = fWire_Nhits;
   if (nhits==0) return -1;
   return fWire_Iturn[nhits-1] + 1;
};
double Event::GetMCDist(int ihit)
{
   return fWire_MCDist[ihit];
}
double Event::GetDist(int ihit)
{
   return fWire_Dist[ihit];
}
void Event::SetDist(int ihit, double dist)
{
   fWire_Dist[ihit] = dist;
}


// Drawing
void Event::SetMarkerColor(char* category, int col)
{
   if (strcmp(category,"default")==0) mcol_default=col;
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
void Event::DrawHits(char* canv_name, const char* zorigin, double dz)
{
   if (fWire_Nhits==0) return;
   double xmin,ymin,xmax,ymax;
   GetRange(xmin,ymin,xmax,ymax);
   DrawCanvas(canv_name,"Hits", xmin, ymin, xmax, ymax);
   DrawEndplate();
   DrawHitsAt(zorigin, dz);
}

double Event::GetTrigTime()
{
   double trig_time = 1e10;
   if (fScinti_Nhits==0 || fCheren_Nhits==0) return trig_time;
   return fScinti_Time[0];
}
double Event::GetDriftTime(int ihit)
{
   return fXTCurve.GetTime(fWire_MCDist[ihit]);
}
double Event::GetDriftTimeWithTOF(int ihit)
{
   return fWire_DriftTimeWithTOF[ihit];
}
void Event::SetDriftTimeWithTOF(int ihit, double dtime)
{
   fWire_DriftTimeWithTOF[ihit] = dtime;
}

// private
void Event::GetWirePos(int cid, int icell, double zpos_from_center, const char* zorigin, double& xwire, double& ywire)
{
   fWireConfig.GetWirePos(cid, LAYER_TYPE_SENSE, icell, WIRE_TYPE_SENSE, zpos_from_center, zorigin, &xwire, &ywire);
}

void Event::GetRange(double& xmin, double& ymin, double& xmax, double& ymax)
{
   xmin = 1e10;
   ymin = 1e10;
   xmax = -1e10;
   ymax = -1e10;
   for (int ihit=0; ihit<fWire_Nhits; ihit++) {
      double wx, wy;
      GetWirePos(fWire_Ilayer[ihit], fWire_Icell[ihit], 0.0, "up", wx, wy);
      if (xmin>wx) xmin = wx;
      if (xmax<wx) xmax = wx;
      if (ymin>wy) ymin = wy;
      if (ymax<wy) ymax = wy;
   }
}
void Event::DrawHitsAt(const char* zorigin, double dz)
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
      int mcol = mcol_default;

      int iturn = fWire_Iturn[ihit];
      if (iturn==-1) mcol = mcol_noise;
      else if (iturn==0) mcol = mcol_1st_turn;
      else if (iturn==1) mcol = mcol_2nd_turn;
      else if (iturn==2) mcol = mcol_3rd_turn;

      e->SetLineColor(mcol);
      e->Draw();
   }
};
