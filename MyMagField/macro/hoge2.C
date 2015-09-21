{
   TTree t;
   t.ReadFile("jj2","x/D:y:z:rad:bx:by:bz");
   t.SetMarkerStyle(2);
   t.Draw("sqrt(bx*bx+by*by+bz*bz):z","Entry$<100");
   TCanvas c2;
   t.Draw("sqrt(x*x+y*y):z","Entry$<100");
   t.Draw("sqrt(x*x+y*y):z","Entry$<200");
   c1.cd();
   t.Draw("sqrt(bx*bx+by*by+bz*bz):z","Entry$<200");
   TCanvas c3;
   t.Draw("bx:z","Entry$<200");
   TCanvas c4;
   t.Draw("by:z","Entry$<200");
   TCanvas c5;
   t.Draw("bz:z","Entry$<200");
   TCanvas c6;
   t.Draw("rad:z","Entry$<200");
   TCanvas c7;
   t.Draw("x:y","Entry$<200");
}
