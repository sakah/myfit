#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"

#include "Util.h"
#include "XTCurve.h"
#include "WireConfig.h"
#include "CounterHit.h"
#include "CdcHit.h"
#include "Hough.h"

double u1[MAX_CDC_HIT];
double v1[MAX_CDC_HIT];
double u2[MAX_CDC_HIT];
double v2[MAX_CDC_HIT];

TTree* t;
CounterHit cheren;
CounterHit scinti;
CdcHit cdc;
CdcHit cdc1;
CdcHit cdc2;
Hough hough1("odd");
Hough hough2("even");
double threshold = 0.01;
CdcHit cdc1hough;
CdcHit cdc2hough;

void run(int iev)
{
   char* wire_config = "B1T_square_1.5m_ver_2014_03_28.txt";
   WireConfig wireconfig;
   wireconfig.Init(wire_config);

   char* root = "root/hoge1-0.root";
   TFile* f = new TFile(root);
   t = (TTree*)f->Get("t");

   scinti.SetBranchAddressAll(t, "trig_scinti_nhits", "trig_scinti_time", "trig_scinti_posx", "trig_scinti_posy", "trig_scinti_posz", "trig_scinti_momx", "trig_scinti_momy", "trig_scinti_momz");
   cheren.SetBranchAddressAll(t, "trig_cherenkov_nhits", "trig_cherenkov_time", "trig_cherenkov_posx", "trig_cherenkov_posy", "trig_cherenkov_posz", "trig_cherenkov_momx", "trig_cherenkov_momy", "trig_cherenkov_momz");
   cdc.SetBranchAddressAll(t, "nwirehit", "time", "minhit_x", "minhit_y", "minhit_z", "minhit_px", "minhit_py", "minhit_pz", "ilayer", "icell", "iturn");

   t->GetEntry(iev);

   if (cheren.GetNumHits()==0 || scinti.GetNumHits()==0) return;
   printf("iev %d\n", iev);

   cdc1.CopyByLayer(cdc, 1);
   cdc2.CopyByLayer(cdc, 0);
   cdc1.GetUV(wireconfig, u1, v1);
   cdc2.GetUV(wireconfig, u2, v2);

   hough1.FindLine(cdc1.GetNumHits(), u1, v1);
   hough2.FindLine(cdc2.GetNumHits(), u2, v2);

   cdc1hough.CopyByHough(cdc1, hough1.GetA(), hough1.GetB(), u1, v1, threshold);
   cdc2hough.CopyByHough(cdc2, hough2.GetA(), hough2.GetB(), u1, v1, threshold);

}
