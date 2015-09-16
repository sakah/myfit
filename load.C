{
   gROOT->ProcessLine(".L XTCurve.cc+");
   gROOT->ProcessLine(".L WireConfig.cc+");
   gROOT->ProcessLine(".L Event.cc+");

   char* wire_config = "B1T_square_1.5m_ver_2014_03_28.txt";
   char* root = "root/hoge1-0.root";
   //Event evt(wire_config, root);
   //evt.GetEntry(iev);
   //evt.DrawCanvas("c1","MCHits");
   //evt.DrawEndplate();
   //evt.DrawMCHitsAt("MC", 0);

   Event evt1(wire_config, root);
   Event evt2(wire_config, root);
   evt1.GetEntry(iev);
   evt2.GetEntryWithRemovingPileup(evt1);

   evt1.PrintEntry();
   evt2.PrintEntry();
}
