#ifndef _EVENT_H
#define _EVENT_H

#include "TTree.h"
#include "XTCurve.h"
#include "WireConfig.h"

class Event
{
   public:
      Event(char* wire_config, char* root);
      void ReadWireConfig(char* wire_config);
      void ReadTree(char* root);
      void SetupBranch();
      void GetEntry(int iev);
      void GetEntryWithRemovingPileup(Event& oe); 
      void CheckPileup();

      void PrintEntry();
      void PrintWireHit(int ihit);

      int GetNumTurns();
      double GetMCDist(int ihit);
      double GetDist(int ihit);

      double GetDriftTime(int ihit);
      double GetDriftTimeWithTOF(int ihit);

      // Drawing
      void SetMarkerColor(char* category, int col);
      void DrawCanvas(char* canv_name, char* canv_title, double xmin, double ymin, double xmax, double ymax);
      void DrawEndplate();
      void DrawHits(char* canv_name, const char* zorigin, double dz);


      double GetTrigTime();

      void CopyEventInfo(Event& oe);
      void AddWireHit(int ihit, Event& oe);

   private:
      TTree* fTree;

      int fIev;

#define MAX_MCHIT 10000
      int fMC_Nhits;
      double fMC_Time[MAX_MCHIT];
      double fMC_Xhits[MAX_MCHIT];
      double fMC_Yhits[MAX_MCHIT];
      double fMC_Zhits[MAX_MCHIT];
      double fMC_Pxhits[MAX_MCHIT];
      double fMC_Pyhits[MAX_MCHIT];
      double fMC_Pzhits[MAX_MCHIT];

      int fScinti_Nhits;
      double fScinti_Time[10];
      double fScinti_Xhits[10];
      double fScinti_Yhits[10];
      double fScinti_Zhits[10];
      double fScinti_Pxhits[10];
      double fScinti_Pyhits[10];
      double fScinti_Pzhits[10];

      int fCheren_Nhits;
      double fCheren_Time[10];
      double fCheren_Xhits[10];
      double fCheren_Yhits[10];
      double fCheren_Zhits[10];
      double fCheren_Pxhits[10];
      double fCheren_Pyhits[10];
      double fCheren_Pzhits[10];

#define MAX_HIT 1000
      int fWire_Nhits;
      int fWire_Ilayer[MAX_HIT];
      int fWire_Icell[MAX_HIT];
      int fWire_Iturn[MAX_HIT];
      double fWire_MCDist[MAX_HIT];
      double fWire_Time[MAX_HIT];
      double fWire_Xhits[MAX_HIT];
      double fWire_Yhits[MAX_HIT];
      double fWire_Zhits[MAX_HIT];
      double fWire_Pxhits[MAX_HIT];
      double fWire_Pyhits[MAX_HIT];
      double fWire_Pzhits[MAX_HIT];

      WireConfig fWireConfig;
      void GetWirePos(int cid, int icell, double zpos_from_center, const char* zorigin, double& xwire, double& ywire);

      int mcol_default;
      int mcol_1st_turn;
      int mcol_2nd_turn;
      int mcol_3rd_turn;
      int mcol_noise;

      XTCurve fXTCurve;

      double fWire_DriftTimeWithTOF[MAX_HIT];
      int fWire_FirstArrived[MAX_HIT]; // 0: not first one, 1: first arrived
      double fWire_Dist[MAX_HIT];

      void SetDriftTimeWithTOF(int ihit, double dtime);
      void SetDist(int ihit, double dist);
      void GetRange(double& xmin, double& ymin, double& xmax, double& ymax);
      void DrawHitsAt(const char* zorigin, double dz);
};
#endif

