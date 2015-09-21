{
   TTree t;
   t.ReadFile("jj2","x/D:y:z:rad");
   t.SetMarkerStyle(2);
   t.SetMarkerColor(1);
   TCanvas c1;
   c1.Divide(1,2);
   c1.cd(1); t.Draw("x:y","Entry$<70");
   c1.cd(2); t.Draw("rad/3.14*180:Entry$","Entry$<70");
   t.SetMarkerColor(2);
   c1.cd(1); t.Draw("x:y","Entry$<20", "same");
   c1.cd(2); t.Draw("rad/3.14*180:Entry$","Entry$<20", "same");
}
