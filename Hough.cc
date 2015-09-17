#include "Hough.h"

Hough::Hough(double threshold)
{
   fGraph_UV = NULL;
   fGraph_UV_Inside = NULL;
   fH2ab = NULL;
   fFoundA = 1e10;
   fFoundB = 1e10;

   fNum_Hits = 0;
   fNum_Signal= 0;
   fNum_Signal_Inside= 0;
   fNum_Signal_Inside= 0;
   fNum_Inside= 0;
   fNum_Inside_Signal= 0;
   fNum_Inside_Noise= 0;

   fChi2 = 1e10;
   fGraph = NULL;
   fHdiff = NULL;

   fDiffThreshold = threshold;
};
~Hough::Hough()
{
   if (fH2_Diff!=NULL) delete fH2D_Diff;
   if (fH2D_AB!=NULL) delete fH2D_AB;
   if (fGraph_UV!=NULL) delete fGraph_UV;
   if (fGraph_UV_Inside!=NULL) delete fGraph_UV_Inside;
};
void Hough::SetName(char* name)
{
   strcpy(fName, name);
};
void Hough::AddHitWithConformal(double x, double y)
{
   int ihit = fNum_Hits;
   fXhits[ihit] = x;
   fYhits[ihit] = y;
   double r2 = x*x+y*y;
   fUhits[ihit] = 2.0*fXhits[ihit]/r2;
   fVhits[ihit] = 2.0*fYhits[ihit]/r2;
   fNum_Hits++;
};
void Hough::FindLine()
{
   double astep = 0.1;
   double amin = -8;
   double amax = 8;
   double bstep = 0.001;
   double bmin = -0.5;
   double bmax = 0.5;
   int anum = static_cast<int>((amax-amin)/astep);
   int bnum = static_cast<int>((bmax-bmin)/bstep);
   //printf("anum %d %f %f bnum %d %f %f\n", anum, amin, amax, bnum, bmin, bmax);
   if (fH2D_AB==NULL) {
      fH2D_AB = new TH2F("h2ab",Form("%s A-B Space;a;b",name),anum, amin, amax, bnum, bmin, bmax);
      fH2D_AB->SetStats(0);
   }
   fH2_AB->Reset();

   fGraph_UV = new TGraph(fNum_Hits, fUhits, fVhits);
   fGraph_UV->SetTitle(Form("%s U-V Space;u;v",name));

   for (int i=0; i<fNum_Hits; i++) {
      for (int ia=0; ia<anum; ia++) {

         double a = ia*astep + amin;
         double b = -fUhits[i]*a + fVhits[i];

         //printf("i %d a %lf b %lf\n", i, a, b);
         fH2D_AB->Fill(a, b, 1);
      }
   }
   int ia_min;
   int ib_min;
   int tmp;
   fH2D_AB->GetMaximumBin(ia_min, ib_min, tmp);
   fFoundA = fH2D_AB->GetXaxis()->GetBinCenter(ia_min);
   fFoundB = fH2D_AB->GetYaxis()->GetBinCenter(ib_min);
};
void Hough::CalcDiff()
{
   if (fH1D_Diff==NULL) {
      fH1D_Diff = new TH1F("hdiff",Form("%s Residual; Residual;",fName), 100, -0.03, 0.03);
      gStyle->SetOptStat(1111111);
      fH1D_Diff->SetStats(1);
   }
   fH1D_Diff->Reset();

   fNum_Signal_Inside=0;
   fNum_Signal_Outside=0;

   fNum_Inside=0;
   fNum_Inside_Signal=0;
   fNum_Inside_Noise=0;

   double uhits_inside[1000];
   double vhits_inside[1000];

   for (int ihit=0; ihit<fNum_Hits; ihit++) {
      if (fIturns[ihit]!=-1) fNum_Signal++;

      double v = found_a * uhits[ihit] + found_b;
      diff[ihit] = v - vhits[ihit];
      hdiff->Fill(diff[ihit]);
      //printf("ihit %d vcalc %f vhits %f diff %f\n", ihit, v, hits.vhits[ihit], diff);
      if (TMath::Abs(diff[ihit]) < diff_threshold) {
         uhits_inside[num_inside] = uhits[ihit];
         vhits_inside[num_inside] = vhits[ihit];
         num_inside++;
         circ.add_hit(ilayers[ihit], icells[ihit], iturns[ihit], w_xs[ihit], w_ys[ihit]);
         if (iturns[ihit]!=-1) {
            num_signal_inside++;
            num_inside_signal++;
         } else {
            num_inside_noise++;
         }
      } else {
         if (iturns[ihit]!=-1) num_signal_outside++;
      }
   }
   //printf("DEBUG: num_inside %d (sig %d noise %d)\n", num_inside, num_inside_signal, num_inside_noise);
   gr_uv_inside = new TGraph(num_inside, uhits_inside, vhits_inside);
   gr_uv_inside->SetMarkerColor(kBlue);
   gr_uv_inside->SetTitle(Form("%s U-V Space(Inside);u;v",name));

};
void Hough::PrintResult(int iev)
{
   printf("Hough:: iev %d found_a %f found_b %f ", iev, found_a, found_b);
   printf("signal: inside %5.2f (%d/%d) outside %5.2f (%d/%d) ", 
         (double)fNum_Signal_Inside/fNum_Signal, fNum_Signal_Inside, fNum_Signal,
         (double)fNum_Signal_Outside/fNum_Signal, fNum_Signal_Outside, fNum_Signal);
   printf("inside: signal %5.2f (%d/%d) noise %5.2f (%d/%d)\n", 
         (double)fNum_Inside_Signal/fNum_Inside, fNum_Inside_Signal, fNum_Inside,
         (double)fNum_Inside_Noise/fNum_Inside, fNum_Inside_Signal, fNum_Inside);
};
TF1* Hough::GetLine()
{
   TF1* f1 = new TF1("f1", "[0]+[1]*x", -1e-1, 1e-1);
   f1->SetParameters(fFoundB, fFoundA);
   return f1;
};

void Hough::DrawHistAB()
{
   hH2ab->Draw("colz");
   TMarker* m1 = new TMarker(fFoundA, fFoundB, 33);
   m1->SetMarkerColor(kRed);
   m1->SetMarkerSize(3.0);
   m1->Draw("same");
};
void Hough::DrawHistUV()
{
   TH2F* hframe = new TH2F("hframe","",10,-0.1, 0.1, 10, -0.1, 0.1);
   hframe->SetStats(0);
   hframe->Draw();
   hframe->SetTitle(fGraph_UV->GetTitle());
   GetLine()->Draw("same");
   fGraph_UV->Draw("p same");
   fGraph_UV_Inside->Draw("p same");
};
void Hough::DrawHistDiff()
{
   fHdiff->Draw();
   gPad->Modified();
   gPad->Update();
   double ymax = gPad->GetFrame()->GetY2();
   double x1L = -fDiffThreshold, y1L = 0.0;
   double x2L = +fDiffThreshold, y2L = 0.0;
   double x1R = -fDiffThreshold, y1R = ymax;
   double x2R = +fDiffThreshold, y2R = ymax;
   TLine* l1 = new TLine(x1L, y1L, x1R, y1R); l1->SetLineColor(kRed); l1->Draw("same");
   TLine* l2 = new TLine(x2L, y2L, x2R, y2R); l2->SetLineColor(kRed); l2->Draw("same");
};

