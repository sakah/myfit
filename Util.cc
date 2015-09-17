#include "Util.h"

#include "TMath.h"
#include "TMarker.h"
#include "TEllipse.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TF1.h"

double pow2(double a, double b) { return a*a + b*b; }
double sqrt2(double a, double b) { return TMath::Sqrt(a*a+b*b); }
double sqrt3(double a, double b, double c) { return TMath::Sqrt(a*a+b*b+c*c); };
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
void draw_line(double a, double b, double xmin, double xmax, int col)
{
   TF1* f1 = new TF1("line", "[0]*x+[1]", xmin, xmax);
   f1->SetLineColor(col);
   f1->SetParameters(a, b);
   f1->Draw("same");
}
