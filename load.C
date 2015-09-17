{
   gROOT->ProcessLine(".L Util.cc+");
   gROOT->ProcessLine(".L XTCurve.cc+");
   gROOT->ProcessLine(".L WireConfig.cc+");
   gROOT->ProcessLine(".L CounterHit.cc+");
   gROOT->ProcessLine(".L CdcHit.cc+");
   gROOT->ProcessLine(".L Hough.cc+");

   char* wire_config = "B1T_square_1.5m_ver_2014_03_28.txt";
   WireConfig wireconf;
   wireconf.Init(wire_config);

   char* root = "root/hoge1-0.root";
   TFile* f = new TFile(root);
   TTree* t = (TTree*)f->Get("t");

   CounterHit cheren;
   CounterHit scinti;
   CdcHit cdc;

   scinti.SetBranchAddressAll(t, "trig_scinti_nhits", "trig_scinti_time", "trig_scinti_posx", "trig_scinti_posy", "trig_scinti_posz", "trig_scinti_momx", "trig_scinti_momy", "trig_scinti_momz");
   cheren.SetBranchAddressAll(t, "trig_cheren_nhits", "trig_cheren_time", "trig_cheren_posx", "trig_cheren_posy", "trig_cheren_posz", "trig_cheren_momx", "trig_cheren_momy", "trig_cheren_momz");
   cdc.SetBranchAddressAll(t, "nwirehit", "time", "minhit_x", "minhit_y", "minhit_z", "minhit_px", "minhit_py", "minhit_pz", "ilayer", "icell", "iturn");

   if (cheren.GetNumHits()==0 || scinti.GetNumHits()==0) return;

   CdcHit cdc1;
   CdcHit cdc2;
   cdc1.CopyByLayer(cdc, CDC_ODD);
   cdc2.CopyByLayer(cdc, CDC_EVEN);
   double u1[MAX_WIRE_HIT];
   double v1[MAX_WIRE_HIT];
   double u2[MAX_WIRE_HIT];
   double v2[MAX_WIRE_HIT];
   cdc1.GetUV(wireconfig, u1, v1);
   cdc2.GetUV(wireconfig, u2, v2);

   Hough hough1;
   Hough hough2;
   hough1.FindLine(cdc1.GetNumHits(), u1, v1);
   hough2.FindLine(cdc2.GetNumHits(), u2, v2);

   CdcHit cdc1hough;
   CdcHit cdc2hough;
   cdc1hough.CopyByHough(cdc1, u1, v1);
   cdc2hough.CopyByHough(cdc2, u1, v1);

}
