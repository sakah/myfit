#include "Util.h"

#include "TMath.h"
#include "TMarker.h"
#include "TEllipse.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TF1.h"
#include "TLine.h"

double pow2(double a, double b) { return a*a + b*b; }
double sqrt2(double a, double b) { return TMath::Sqrt(a*a+b*b); }
double sqrt3(double a, double b, double c) { return TMath::Sqrt(a*a+b*b+c*c); };
void rotate_by(double x0, double y0, double angle, int num, double* x1, double* y1, double *x2, double* y2)
{
   for (int i=0; i<num; i++) {
      x2[i]=+(x1[i]-x0)*TMath::Cos(angle)-(y1[i]-y0)*TMath::Sin(angle)+x0;
      y2[i]=+(x1[i]-x0)*TMath::Sin(angle)+(y1[i]-y0)*TMath::Cos(angle)+y0;
   }
}
void draw_ellipse(double x, double y, double r, int col)
{
   TEllipse* e1 = new TEllipse(x, y, r);
   e1->SetFillStyle(0);
   e1->SetLineColor(col);
   e1->Draw();
}
void draw_marker(double x, double y, int col, int style)
{
   TMarker* m1 = new TMarker(x, y, style);
   m1->SetMarkerColor(col);
   m1->Draw();
}
void draw_frame(char* title, int nx, double xmin, double xmax, int ny, double ymin, double ymax)
{
   TH2F* h2 = new TH2F(title, title, nx, xmin, xmax, ny, ymin, ymax);
   h2->SetStats(0);
   h2->Draw();
}
void draw_graph(char* title, double xmin, double xmax, double ymin, double ymax, int nhits, double* x, double* y, int col, int style)
{
   draw_frame(title, 100, xmin, xmax, 100, ymin, ymax);
   TGraph *gr = new TGraph(nhits, x, y);
   gr->SetMarkerColor(col);
   gr->SetMarkerStyle(style);
   gr->Draw("p same");
}
void draw_line_AB(double a, double b, double xmin, double xmax, int col, int style)
{
   TF1* f1 = new TF1("line", "[0]*x+[1]", xmin, xmax);
   f1->SetLineColor(col);
   f1->SetLineStyle(style);
   //if (TMath::Abs(a)>100) {
   //   f1->SetNpx(100000);
   //}
   f1->SetParameters(a, b);
   f1->Draw("same");
}
void draw_line_AB2(double a, double b, double xmin, double xmax, int col, double threshold)
{
   draw_line_AB(a, b, xmin, xmax, col, 1);
   draw_line_AB(a, b+threshold, xmin, xmax, col, 2);
   draw_line_AB(a, b-threshold, xmin, xmax, col, 2);
}
void draw_line_TR(double theta, double rho, double xmin, double xmax, int col, int style)
{
   double a = -1.0/TMath::Tan(theta);
   double b = rho/TMath::Sin(theta);
   draw_line_AB(a, b, xmin, xmax, col, style);
}
