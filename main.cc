/*
   layer   1      0     G      +       51.1673      51.4000      147.6046     396         12          190.400        0.2327      66.106       0.0000
   layer   2      1     F      -       52.0358      52.2000      147.8867     396        -12         -190.400        0.1642     -67.004       15.867
   layer   3      1     S      -       52.8333      53.0000      148.1688     396        -12         -190.400        0.1667     -67.899       15.867
   layer   4      2     F      +       53.5705      53.8000      148.4509     408         12          184.800        0.2295      66.778       15.400
   layer   5      2     S      +       54.3671      54.6000      148.7331     408         12          184.800        0.2329      67.640       15.400
   layer   6      3     F      -       55.1770      55.4000      149.0152     420        -12         -179.520        0.2230     -66.553       0.0000
   layer   7      3     S      -       55.9738      56.2000      149.2973     420        -12         -179.520        0.2262     -67.384       0.0000
   layer   8      4     F      +       56.7831      57.0000      149.5794     432         12          174.533        0.2169      66.327       14.544
   layer   9      4     S      +       57.5801      57.8000      149.8616     432         12          174.533        0.2199      67.129       14.544
   layer   10     5     F      -       58.3889      58.6000      150.1437     444        -12         -169.816        0.2111     -66.102       0.0000
   layer   11     5     S      -       59.1860      59.4000      150.4258     444        -12         -169.816        0.2140     -66.876       0.0000
   layer   12     6     F      +       59.9944      60.2000      150.7079     456         12          165.347        0.2056      65.877       0.0000
   layer   13     6     S      +       60.7917      61.0000      150.9900     456         12          165.347        0.2083      66.625       0.0000
   layer   14     7     F      -       61.5996      61.8000      151.2722     468        -12         -161.107        0.2004     -65.652       13.426
   layer   15     7     S      -       62.3970      62.6000      151.5543     468        -12         -161.107        0.2030     -66.376       13.426
   layer   16     8     F      +       63.2046      63.4000      151.8364     480         12          157.080        0.1954      65.428       0.0000
   layer   17     8     S      +       64.0021      64.2000      152.1185     480         12          157.080        0.1979      66.129       0.0000
   layer   18     9     F      -       64.8093      65.0000      152.4007     492        -12         -153.248        0.1907     -65.205       12.771
   layer   19     9     S      -       65.6069      65.8000      152.6828     492        -12         -153.248        0.1931     -65.884       12.771
   layer   20     10    F      +       66.4138      66.6000      152.9649     504         12          149.600        0.1862      64.982       0.0000
   layer   21     10    S      +       67.2115      67.4000      153.2470     504         12          149.600        0.1885      65.640       0.0000
   layer   22     11    F      -       68.0181      68.2000      153.5292     516        -12         -146.121        0.1819     -64.761       12.177
   layer   23     11    S      -       68.8159      69.0000      153.8113     516        -12         -146.121        0.1841     -65.398       12.177
   layer   24     12    F      +       69.6222      69.8000      154.0934     528         12          142.800        0.1778      64.540       0.0000
   layer   25     12    S      +       70.4201      70.6000      154.3755     528         12          142.800        0.1799      65.158       0.0000
   layer   26     13    F      -       71.2261      71.4000      154.6576     540        -12         -139.626        0.1739     -64.319       11.636
   layer   27     13    S      -       72.0241      72.2000      154.9398     540        -12         -139.626        0.1759     -64.920       11.636
   layer   28     14    F      +       72.8298      73.0000      155.2219     552         12          136.591        0.1702      64.100       0.0000
   layer   29     14    S      +       73.6280      73.8000      155.5040     552         12          136.591        0.1720      64.683       0.0000
   layer   30     15    F      -       74.3733      74.6000      155.7861     564        -14         -155.966        0.2267     -74.472       0.0000
   layer   31     15    S      -       75.1709      75.4000      156.0683     564        -14         -155.966        0.2291     -75.132       0.0000
   layer   32     16    F      +       75.9780      76.2000      156.3504     576         14          152.716        0.2220      74.220       0.0000
   layer   33     16    S      +       76.7756      77.0000      156.6325     576         14          152.716        0.2244      74.862       0.0000
   layer   34     17    F      -       77.5825      77.8000      156.9146     588        -14         -149.600        0.2175     -73.969       10.686
   layer   35     17    S      -       78.3802      78.6000      157.1968     588        -14         -149.600        0.2198     -74.593       10.686
   layer   36     18    F      +       79.1868      79.4000      157.4789     600         14          146.608        0.2132      73.719       0.0000
   layer   37     18    S      +       79.9846      80.2000      157.7610     600         14          146.608        0.2154      74.326       0.0000
   layer   38     19    F      -       80.7909      81.0000      158.0431     612        -14         -143.733        0.2091     -73.470       10.267
   layer   39     19    G      -       81.5889      81.8000      158.3252     612        -14         -143.733        0.2111     -74.061       10.267
 */
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>

#include "InputROOT.h"

#include "TFrame.h"
#include "TMinuit.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TF1.h"
#include "TMarker.h"
#include "TLine.h"
#include "TGraphErrors.h"
#include "TEllipse.h"

int g_num_cells[20] =  {
   396/2,
   396/2,
   408/2,
   420/2,
   432/2,
   444/2,
   456/2,
   468/2,
   480/2,
   492/2,
   504/2,
   516/2,
   528/2,
   540/2,
   552/2,
   564/2,
   576/2,
   588/2,
   600/2,
   612/2};

//static double sqrt2(double a, double b)  { return TMath::Sqrt(a*a+b*b); }
static double sqrt2minus(double a, double b) 
{ 
   if (a<b) return 0.0;
   return TMath::Sqrt(a*a-b*b); 
}
static double rad2deg(double rad)
{
   return rad/TMath::Pi()*180.0;
}
double calc_rad(double x0, double y0, double x, double y)
{
   double dx = x-x0;
   double dy = y-y0;
   double rad = TMath::ATan2(dy,dx);  // [-pi, pi]
   if (dy<0) rad += 2.0*TMath::Pi(); // [0, 2pi]
   return rad;
}
int get_region(double rad)
{
   // rad should be from 0 to 2pi
   double pi = TMath::Pi();
   if (rad>=0 && rad<pi/2.0) return 1;
   if (rad>=pi/2.0 && rad<pi) return 2;
   if (rad>=pi && rad<pi*1.5) return 3;
   return 4;
}
void set_marker_style(TMarker* m, int ilayer)
{
   int style;
   if (ilayer%2==1) style = 8; // ●
   if (ilayer%2==0) style = 22; // ▲
   m->SetMarkerStyle(style);
}
void set_marker_color(TMarker* m, int iturn)
{
   int col;
   if (iturn==-1) col = kCyan; //noise
   if (iturn==0) col = kBlack;
   if (iturn==1) col = kRed;
   if (iturn==2) col = kBlue;
   if (iturn>=3) col = kGreen;
   m->SetMarkerColor(col);
}

struct Sort_int_data
{
   int idx;
   int data;
   double buf1;
   double buf2;
   int buf3;
};
int sort_int_data(const void* a, const void* b)
{
   Sort_int_data* d1 = (Sort_int_data*)a;
   Sort_int_data* d2 = (Sort_int_data*)b;
   int v1 = d1->data;
   int v2 = d2->data;
   //printf("sort_int_data: v1 %d v2 %d\n", v1, v2);
   return v1 - v2;
}

struct Sort_int_double_data
{
   int idx;
   int first_key;
   double second_key;
};
int sort_int_double_data(const void* a, const void* b)
{
   Sort_int_double_data* d1 = (Sort_int_double_data*)a;
   Sort_int_double_data* d2 = (Sort_int_double_data*)b;
   if      (d1->first_key < d2->first_key) return -1;
   else if (d1->first_key > d2->first_key) return +1;
   else {
      if      (d1->second_key < d2->second_key) return -1;
      else if (d1->second_key > d2->second_key) return +1;
   }
   return 0;
}

static struct config* g_config;
int g_maxLayerIdx;
int g_nhits;
double g_xhits[1000];
double g_yhits[1000];
double g_zhits[1000];
int    g_hits_ilayer[1000];
int    g_hits_icell[1000];
int    g_hits_iturn[1000];
double g_xsig;
double g_ysig;

double g_xA_circ1;
double g_yA_circ1;
double g_xB_circ1;
double g_yB_circ1;
double g_xA_circ2;
double g_yA_circ2;
double g_xB_circ2;
double g_yB_circ2;

int g_icell_region[20][4]; // define bordering icells in four region
void set_icell_region()
{
   for (int ilayer=0; ilayer<20; ilayer++) {
      int n1 = g_num_cells[ilayer]/4;
      int n2 = g_num_cells[ilayer]/2;
      int n3 = g_num_cells[ilayer]*3/4;
      g_icell_region[ilayer][0] = 0;
      g_icell_region[ilayer][1] = n1;
      g_icell_region[ilayer][2] = n2;
      g_icell_region[ilayer][3] = n3;
   }
}

void func_circ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *x, Int_t iflag)
{
   double x0 = x[0];
   double y0 = x[1];
   double R  = x[2];
   double chi2 = 0;
   for (int ihit=0; ihit<g_nhits; ihit++) {
      double x1 = g_xhits[ihit] - x0;
      double y1 = g_yhits[ihit] - y0;
      double theta = TMath::ATan2(y1, x1);
      double xexp = R * TMath::Cos(theta);
      double yexp = R * TMath::Sin(theta);
      double dx = (xexp-x1)/g_xsig;
      double dy = (yexp-y1)/g_ysig;
      chi2 += dx*dx + dy*dy;
   }
   //printf("chi2 %f\n", chi2);
   f = chi2;
}
bool chk_hitpattern(int* region_hit, int a, int b, int c, int d)
{
   return region_hit[0]==a && region_hit[1]==b && region_hit[2]==c && region_hit[3]==d;
}

int g_wrong_order;
void func_helix(Int_t &npar, Double_t *gin, Double_t &f, Double_t *x, Int_t iflag)
{
   bool debug = false;
   //bool debug = true;

   double x0 = x[0];
   double y0 = x[1];
   double R  = x[2];
   double rad0  = x[3]; // [0, 360deg]
   double L  = x[4];
   double chi2 = 0;

   // radA1,radA2 are changed by x0, y0, so we have to calc everytime.
   double radA1 = calc_rad(x0, y0, g_xA_circ1, g_yA_circ1);
   double radA2 = calc_rad(x0, y0, g_xA_circ2, g_yA_circ2);
   int regA1 = get_region(radA1);
   int regA2 = get_region(radA2);
   // here care have to be taken!!
   // Because we assume electron rotate anticlock wise, take region4's angle as min_rad.
   double min_rad = radA1<radA2?radA1:radA2;
   if      (regA1==4 && regA2==1) min_rad = radA1;
   else if (regA1==1 && regA2==4) min_rad = radA2;

   // Change angle if rad is smaller than min_rad
   double rad_rotate[1000];
   for (int ihit=0; ihit<g_nhits; ihit++) {
      double rad = calc_rad(x0, y0, g_xhits[ihit], g_yhits[ihit]);
      if (rad<min_rad) rad += 2.0*TMath::Pi();
      rad_rotate[ihit] = rad;
   }

   g_wrong_order = 0;
   double drad_prev = rad_rotate[0] - rad0;
   // Calc x,y position using current parameters
   for (int ihit=0; ihit<g_nhits; ihit++) {
      // By choosing correct rad0, there should not be gap along trajectory.
      double drad = rad_rotate[ihit] - rad0;
      double ddrad = drad - drad_prev;
      if (ddrad<0) {
         g_wrong_order = 1;
      }
      drad_prev = drad;
      if (drad>2.0*TMath::Pi()) drad -= 2.0*TMath::Pi();
      double w_z = drad*L;
      int ilayer = g_hits_ilayer[ihit];
      int icell = g_hits_icell[ihit];
      double w_x;
      double w_y;
      config_get_wire_pos(g_config, ilayer, LAYER_TYPE_SENSE, icell, WIRE_TYPE_SENSE, w_z, "center", &w_x, &w_y);

      double xexp = x0 + R*TMath::Cos(rad0 + w_z/L);
      double yexp = y0 + R*TMath::Sin(rad0 + w_z/L);
      double dx = (xexp-w_x)/g_xsig;
      double dy = (yexp-w_y)/g_ysig;
      chi2 += dx*dx + dy*dy;
      if (debug) printf("ihit %2d ilayer %2d icell %3d w_z %5.1f w_x %5.1f w_y %5.1f xexp %5.1f yexp %5.1f dx %5.1f dy %5.1f rad0 %5.1f (deg) rad %5.1f (deg) chi2 %5.1f\n", 
            ihit,ilayer, icell, w_z, w_x,w_y,xexp,yexp,dx,dy, rad2deg(rad0), rad2deg(rad0+w_z/L), chi2);

      // update hit position for next fit
      g_xhits[ihit] = w_x;
      g_yhits[ihit] = w_y;
      g_zhits[ihit] = w_z;
      if (ihit==0 && ilayer%2==1) {
          g_xA_circ1 = w_x;
          g_yA_circ1 = w_y;
      } else if (ihit==0 && ilayer%2==0) {
          g_xA_circ2 = w_x;
          g_yA_circ2 = w_y;
      }
   }
   //printf("chi2 %f\n", chi2);
   f = chi2;
}

struct Circle
{
   char name[128];
   int nhits;
   double xhits[1000];
   double yhits[1000];
   int hits_ilayer[1000];
   int hits_icell[1000];
   int hits_iturn[1000];
   int hits_region[1000];

   double radius[20];
   int hit_pattern[4];
   int order_region[4];

   int line_color;

   TMinuit* minuit;
   double chi2;
   Circle()
   {
      nhits = 0;

      int n = 0;
      radius[n++] = 51.4000;
      radius[n++] = 53.0000;
      radius[n++] = 54.6000;
      radius[n++] = 56.2000;
      radius[n++] = 57.8000;
      radius[n++] = 59.4000;
      radius[n++] = 61.0000;
      radius[n++] = 62.6000;
      radius[n++] = 64.2000;
      radius[n++] = 65.8000;
      radius[n++] = 67.4000;
      radius[n++] = 69.0000;
      radius[n++] = 70.6000;
      radius[n++] = 72.2000;
      radius[n++] = 73.8000;
      radius[n++] = 75.4000;
      radius[n++] = 77.0000;
      radius[n++] = 78.6000;
      radius[n++] = 80.2000;
      radius[n++] = 81.8000;

      minuit = new TMinuit(3);
      minuit->SetFCN(func_circ);
      g_xsig = 1.0;
      g_ysig = 1.0;
   };
   void print_cells()
   {
      for (int ihit=0; ihit<nhits; ihit++) {
         printf("Circle: %s ilayer %d icell %d iturn %d region %d\n", name, 
               hits_ilayer[ihit],
               hits_icell[ihit],
               hits_iturn[ihit],
               hits_region[ihit]);
      }
   };
   void set_name(char* a_name)
   {
      strcpy(name, a_name);
   };
   void set_line_color(int col)
   {
      line_color = col;
   };
   void remove_hit(int ilayer, int icell)
   {
      int remove_idx = -1;
      for (int ihit=0; ihit<nhits; ihit++) {
         if (hits_ilayer[ihit] == ilayer && hits_icell[ihit] == icell) {
            remove_idx = ihit;
            break;
         }
      }
      //printf("remove_hit: idx %d nhits %d\n", remove_idx, nhits);
      if (remove_idx==-1) return; // not found
      int n=0;
      for (int ihit=0; ihit<nhits; ihit++) {
         if (ihit == remove_idx) continue;
         hits_ilayer[n] = hits_ilayer[ihit];
         hits_icell[n] =  hits_icell[ihit];
         hits_iturn[n] =  hits_iturn[ihit];
         xhits[n] =       xhits[ihit];
         yhits[n] =       yhits[ihit];
         //printf("n %d hits_ilaeyr %d hits_icell %d\n", n, hits_ilayer[n], hits_icell[n]);
         n++;
      }
      nhits--;
   };
   void copy_hits(Circle& other)
   {
      nhits = other.nhits;
      for (int ihit=0; ihit<nhits; ihit++) {
         xhits[ihit] = other.xhits[ihit];
         yhits[ihit] = other.yhits[ihit];
         hits_ilayer[ihit] = other.hits_ilayer[ihit];
         hits_icell[ihit]  = other.hits_icell[ihit];
         hits_iturn[ihit]  = other.hits_iturn[ihit];
      }
   };
   void add_hit(int ilayer, int icell, int iturn, double x, double y)
   {
      hits_ilayer[nhits] = ilayer;
      hits_icell[nhits] = icell;
      hits_iturn[nhits] = iturn;
      xhits[nhits] = x;
      yhits[nhits] = y;
      nhits++;
   };
   void add_hits(Circle& c1, Circle& c2)
   {
      for (int ihit=0; ihit<c1.nhits; ihit++) {
         hits_ilayer[nhits] = c1.hits_ilayer[ihit];
         hits_icell[nhits] = c1.hits_icell[ihit];
         hits_iturn[nhits] = c1.hits_iturn[ihit];
         xhits[nhits] =  c1.xhits[ihit];
         yhits[nhits] = c1.yhits[ihit];
         nhits++;
      }
      for (int ihit=0; ihit<c2.nhits; ihit++) {
         hits_ilayer[nhits] = c2.hits_ilayer[ihit];
         hits_icell[nhits] = c2.hits_icell[ihit];
         hits_iturn[nhits] = c2.hits_iturn[ihit];
         xhits[nhits] =  c2.xhits[ihit];
         yhits[nhits] = c2.yhits[ihit];
         nhits++;
      }
   };

   void sort_cells()
   {
      set_cell_angle();
      sort_cells_by_angle();
   };

   void set_cell_angle()
   {
      // This function set hit_region and order_region for each cells
      // for sorting cells by angle

      double rad90 = TMath::Pi()*0.5;
      double rad180 = TMath::Pi();
      double rad270 = TMath::Pi()*1.5;

      for (int i=0; i<4; i++) {
         hit_pattern[i] = 0;
         order_region[i] = 10;  // using this number sort will be done
      }

      //printf("nhits %d\n", nhits);
      for (int ihit=0; ihit<nhits; ihit++) {
         double rad = calc_rad(x0_fit, y0_fit, xhits[ihit], yhits[ihit]);
         //printf("ihit %d deg %f\n", ihit, rad2deg(rad));
         if      (rad>=0      && rad<rad90)  { hit_pattern[0] = 1; hits_region[ihit] = 0; }
         else if (rad>=rad90  && rad<rad180) { hit_pattern[1] = 1; hits_region[ihit] = 1; }
         else if (rad>=rad180 && rad<rad270) { hit_pattern[2] = 1; hits_region[ihit] = 2; }
         else                                { hit_pattern[3] = 1; hits_region[ihit] = 3; }
      }

      double ang360 = TMath::Pi()*2.0;

      // 4 reg-hits
      if      (hit_pattern[0]==1 && hit_pattern[1]==1 && hit_pattern[2]==1 && hit_pattern[3]==1) { order_region[0] = 1; order_region[1] = 2; order_region[2]= 3; order_region[3] = 4;}
      // 3 reg-hits
      else if (hit_pattern[0]==1 && hit_pattern[1]==1 && hit_pattern[2]==1 && hit_pattern[3]==0) { order_region[0] = 1; order_region[1] = 2; order_region[2]= 3; }
      else if (hit_pattern[0]==1 && hit_pattern[1]==1 && hit_pattern[2]==0 && hit_pattern[3]==1) { order_region[3] = 1; order_region[0] = 2; order_region[3]= 3; } // ! change order
      else if (hit_pattern[0]==1 && hit_pattern[1]==0 && hit_pattern[2]==1 && hit_pattern[3]==1) { order_region[2] = 1; order_region[3] = 2; order_region[0]= 3; } // ! change order
      else if (hit_pattern[0]==0 && hit_pattern[1]==1 && hit_pattern[2]==1 && hit_pattern[3]==1) { order_region[1] = 1; order_region[2] = 2; order_region[3]= 3; }
      // 2 reg-hits
      else if (hit_pattern[0]==1 && hit_pattern[1]==1 && hit_pattern[2]==0 && hit_pattern[3]==0) { order_region[0] = 1; order_region[1] = 2; }
      else if (hit_pattern[0]==1 && hit_pattern[1]==0 && hit_pattern[2]==1 && hit_pattern[3]==0) { order_region[0] = 1; order_region[2] = 2; } // ! must not happen
      else if (hit_pattern[0]==1 && hit_pattern[1]==0 && hit_pattern[2]==0 && hit_pattern[3]==1) { order_region[3] = 1; order_region[0] = 2; } // ! change order
      else if (hit_pattern[0]==0 && hit_pattern[1]==1 && hit_pattern[2]==1 && hit_pattern[3]==0) { order_region[1] = 1; order_region[2] = 2; }
      else if (hit_pattern[0]==0 && hit_pattern[1]==1 && hit_pattern[2]==0 && hit_pattern[3]==1) { order_region[1] = 1; order_region[3] = 2; } // ! must not happen..
      else if (hit_pattern[0]==0 && hit_pattern[1]==0 && hit_pattern[2]==1 && hit_pattern[3]==1) { order_region[2] = 1; order_region[3] = 2; }
      // 1 reg-hits
      else if (hit_pattern[0]==1 && hit_pattern[1]==0 && hit_pattern[2]==0 && hit_pattern[3]==0) { order_region[0] = 1; }
      else if (hit_pattern[0]==0 && hit_pattern[1]==1 && hit_pattern[2]==0 && hit_pattern[3]==0) { order_region[1] = 1; }
      else if (hit_pattern[0]==0 && hit_pattern[1]==0 && hit_pattern[2]==1 && hit_pattern[3]==0) { order_region[2] = 1; }
      else if (hit_pattern[0]==0 && hit_pattern[1]==0 && hit_pattern[2]==0 && hit_pattern[3]==1) { order_region[3] = 1; }

   };

   void sort_cells_by_angle()
   {
      bool debug = false;

      double tmp_xhits[1000];
      double tmp_yhits[1000];
      int    tmp_hits_ilayer[1000];
      int    tmp_hits_icell[1000];
      int    tmp_hits_iturn[1000];
      int    tmp_hits_region[1000];

      int num_data=0;
      // First key is order_region
      // Second key is anlge
      Sort_int_double_data data[1000];

      for (int ihit=0; ihit<nhits; ihit++) {
         tmp_xhits[ihit] = xhits[ihit];
         tmp_yhits[ihit] = yhits[ihit];
         tmp_hits_ilayer[ihit] = hits_ilayer[ihit];
         tmp_hits_icell[ihit]  = hits_icell[ihit];
         tmp_hits_iturn[ihit]  = hits_iturn[ihit];

         int region = hits_region[ihit];
         double rad = calc_rad(x0_fit, y0_fit, xhits[ihit], yhits[ihit]);

         data[ihit].idx = ihit;
         data[ihit].first_key = order_region[region];
         data[ihit].second_key = rad;

         num_data++;
      }

      if (debug) {
         for (int ihit=0; ihit<nhits; ihit++) {
            printf("BEFORE: ihit %d ilayer %d icell %d | first_key %d second_key %f\n", ihit, hits_ilayer[ihit], hits_icell[ihit], data[ihit].first_key, data[ihit].second_key);
         }
      }

      qsort(data, num_data, sizeof(data[0]), sort_int_double_data);

      if (debug) {
         for (int i=0; i<nhits; i++) {
            int ihit = data[i].idx;
            printf("AFTER : ihit %d ilayer %d icell %d | first_key %d second_key %f\n", ihit, hits_ilayer[ihit], hits_icell[ihit], data[i].first_key, data[i].second_key);
         }
      }

      // Overwite cell data
      for (int i=0; i<nhits; i++) {
         int ihit = data[i].idx;

         xhits[i]         = tmp_xhits[ihit];
         yhits[i]         = tmp_yhits[ihit];
         hits_ilayer[i]   = tmp_hits_ilayer[ihit];
         hits_icell[i]    = tmp_hits_icell[ihit];
         hits_iturn[i]    = tmp_hits_iturn[ihit];
         hits_region[i]   = tmp_hits_region[ihit];
      }
   };

   int ihit_now;
   void start_cell_taking()
   {
      ihit_now = 0;
   };
   int take_hits_until_next_layer(int ilayer, double* myxhits, double* myyhits, int* myilayer, int* myicell, int* myiturn)
   {
      //bool debug = true;
      bool debug = false;

      if (debug) printf("take_hits_until_next_layer: ihit_now %d\n", ihit_now);
      int ihit2 = 0;
      for (int ihit=ihit_now; ihit<nhits; ihit++) {
         if (hits_ilayer[ihit]!=ilayer) {
            ihit_now = ihit;
            break;
         }
         if (debug) printf("take_hits_until_next_layer: ihit %d ilayer %d icell %d\n", ihit, hits_ilayer[ihit], hits_icell[ihit]);
         myxhits[ihit2] = xhits[ihit];
         myyhits[ihit2] = yhits[ihit];
         myilayer[ihit2] = hits_ilayer[ihit];
         myicell[ihit2] = hits_icell[ihit];
         myiturn[ihit2] = hits_iturn[ihit];
         ihit2++;
      }
      if (debug) printf("take_hits_until_next_layer: ihit2 %d\n", ihit2);
      return ihit2;
   };
   int take_hits_by_half(int ilayer, double* myxhits, double* myyhits, int* myilayer, int* myicell, int* myiturn)
   {
      //bool debug = true;
      bool debug = false;

      int num_this_layer=0;
      for (int ihit=ihit_now; ihit<nhits; ihit++) {
         if (ilayer!=hits_ilayer[ihit]) {
            break;
         }
         num_this_layer++;
      }
      int ihit_first = ihit_now;
      int ihit_middle = ihit_now + num_this_layer/2;
      int ihit_last = ihit_now + num_this_layer -1;
      int ihit_forward = -1;
      int ihit_backward = -1;

      // Find spacing from ihit_mipple forward and backward
      // forward
      for (int ihit=ihit_middle; ihit<=ihit_last-1; ihit++) {
         if (hits_icell[ihit] != hits_icell[ihit+1]-1) {
            ihit_forward = ihit;
         }
      }
      // backward
      for (int ihit=ihit_middle; ihit>ihit_first; ihit--) {
         if (hits_icell[ihit] != hits_icell[ihit-1]+1) {
            ihit_backward = ihit-1;
         }
      }

      //   backward   forward   ihit_copy        ihit_now
      // -------------------------------------------------
      //    no         no       ihit_middle      ihit_middle+1
      //    no         yes      ihit_forward     ihit_forward+1
      //    yes        no       ihit_backward    ihit_backward+1
      //    yes        yes      ihit_backward    ihit_backward+1

      int ihit_copy;
      if      (ihit_backward==-1 && ihit_forward==-1) ihit_copy = ihit_middle;
      else if (ihit_backward==-1 && ihit_forward!=-1) ihit_copy = ihit_forward;
      else if (ihit_backward!=-1 && ihit_forward==-1) ihit_copy = ihit_backward;
      else if (ihit_backward!=-1 && ihit_forward!=-1) ihit_copy = ihit_backward;

      if (debug) {
         printf("-------\n");
         for (int ihit=ihit_first; ihit<=ihit_last; ihit++) {
            printf("take_hits_by_half: ihit %d ilayer %d icell %d ", ihit, hits_ilayer[ihit], hits_icell[ihit]);
            if (ihit==ihit_middle) printf(" <-- ihit_middle");
            else if (ihit==ihit_forward)  printf(" <-- ihit_forward");
            else if (ihit==ihit_backward) printf(" <-- ihit_backward");

            if (ihit==ihit_copy) printf(" <= ihit_copy\n");
            else printf("\n");
         }
         printf("-------\n");
      }

      int ihit2 = 0;
      for (int ihit=ihit_now; ihit<=ihit_copy; ihit++) {
         if (debug) printf("take_hits_by_half: ihit %d ilayer %d icell %d\n", ihit, hits_ilayer[ihit], hits_icell[ihit]);
         myxhits[ihit2] = xhits[ihit];
         myyhits[ihit2] = yhits[ihit];
         myilayer[ihit2] = hits_ilayer[ihit];
         myicell[ihit2] = hits_icell[ihit];
         myiturn[ihit2] = hits_iturn[ihit];
         ihit2++;
      }

      ihit_now = ihit_copy+1;
      return ihit2;
   };

   double x0_fit;
   double y0_fit;
   double R_fit;
   double x0_ini;
   double y0_ini;
   double R_ini;
   double x0_step;
   double y0_step;
   double R_step;
   double get_rad_fit(int ihit) 
   { 
      double dx = (xhits[ihit] - x0_fit)/R_fit;
      double dy = (yhits[ihit] - y0_fit)/R_fit;
      double rad =  TMath::ATan2(dy,dx);
      //if (rad<0) rad+=2.0*TMath::Pi();
      return rad;
   };
   double get_radA_fit() { return get_rad_fit(0); };
   double get_radB_fit() { return get_rad_fit(nhits-1); };
   double get_degA_fit() { return get_radA_fit()/TMath::Pi()*180.0; };
   double get_degB_fit() { return get_radB_fit()/TMath::Pi()*180.0; };
   double get_pt_fit()
   { 
      // p (GeV) = 0.3 * B (T) * R (m)
      // pm (MeV) * 1e-3 =  0.3 * B (T) * r (cm)*1e-2
      double B = 1.0; // T
      double pt = 3.0*B*R_fit; // MeV/c
      return pt;
   };
   void clear()
   {
      nhits = 0;
   };
   void set_fit_inipar()
   {
      x0_ini = 20;
      y0_ini = -5;
      R_ini = 40;
      //circ1.x0_fit = 20;
      //circ1.y0_fit = -5;
      //circ1.R_fit = 40;

      x0_step = 1;
      y0_step = 1;
      R_step = 1;
   };
   void fit_circ()
   {
      // copy to global values
      g_nhits = nhits;
      for (int ihit=0; ihit<nhits; ihit++) {
         g_xhits[ihit] = xhits[ihit];
         g_yhits[ihit] = yhits[ihit];
      }

      Int_t ierflag;
      Double_t arglist[10];
      TString Tag[3];
      Double_t var[3];
      Double_t verr[3];
      Double_t bnd1, bnd2;
      Int_t ivarbl;

      // suppress output
      arglist[0] = -1;
      minuit->mnexcm("SET PRINT", arglist, 1, ierflag);

      // suppress warning message
      minuit->mnexcm("SET NOWarnings", arglist, 0, ierflag);

      // set initial values with limits
      minuit->mnparm(0, "x0", x0_ini, x0_step, 0, 0, ierflag); // cm
      minuit->mnparm(1, "y0", y0_ini, y0_step, 0, 0, ierflag); // cm
      minuit->mnparm(2 ,"R",  R_ini,  R_step,  20, 70, ierflag); // cm

      // use chi2
      arglist[0] = 1;
      minuit->mnexcm("SET ERR", arglist, 1, ierflag);

      // do minimize
      arglist[0] = 1000; // do at least 1000 function calls
      arglist[1] = 0.1;  // tolerance = 0.1
      minuit->mnexcm("MIGRAD", arglist, 2, ierflag);

      // copy fit results
      for (int i=0; i<3; i++) {
         minuit->mnpout(i, Tag[i], var[i], verr[i], bnd1, bnd2, ivarbl);
         //printf("i %d %f +/- %f\n", i, var[i], verr[i]);
      }

      // chi2
      Double_t amin,edm,errdef;
      Int_t nvpar,nparx,icstat;
      minuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
      chi2 = amin;

      x0_fit = var[0]; //cm
      y0_fit = var[1]; //cm
      R_fit  = var[2]; // cm

      //printf("R_fit %f\n", R_fit);
      //printf("pt_fit %f\n", get_pt_fit());
   };
   void print_fit_result(char* prefix)
   {
      printf("Fit: %s x0 %f y0 %f R %f pt %f (MeV/c) deg1 %f deg2 %f chi2 %f\n", prefix, x0_fit, y0_fit, R_fit, get_pt_fit(), get_degA_fit(), get_degB_fit(), chi2);
   };
   // Draw
   void draw_xy_canvas()
   {
      TH2F*  h2 = new TH2F("fname",Form("%s XY;X(cm);Y(cm)", name), 100, -100, 100, 100, -100, 100);
      h2->SetStats(0);
      h2->Draw();

      draw_radius();
   };
   void draw_xy_hits_fits()
   {
      draw_xy_hits();
      draw_xy_fit();
      draw_xy_hits();
   };
   void draw_radius()
   {
      for (int ilayer=0; ilayer<20; ilayer++) {
         if (ilayer%2==0) continue;
         TEllipse* e = new TEllipse(0,0,radius[ilayer]);
         e->SetFillStyle(0);
         e->SetLineWidth(1);
         e->SetLineStyle(1);
         e->SetLineColor(kGray);
         e->Draw();
      }
   };
   void draw_xy_hits()
   {
      for (int ihit=0; ihit<nhits; ihit++) {
         TMarker* m = new TMarker(xhits[ihit], yhits[ihit], 8);
         //printf("HOGE:: ihit %d hits_iturn %d xhits %f yhits %f\n", ihit, hits_iturn[ihit], xhits[ihit], yhits[ihit]);
         set_marker_color(m, hits_iturn[ihit]);
         set_marker_style(m, hits_ilayer[ihit]);
         m->Draw();
      }
   };
   void draw_xy_fit()
   {
      TMarker* m = new TMarker(x0_fit, y0_fit, 1);
      m->SetMarkerColor(line_color);
      m->Draw();

      TEllipse* e = new TEllipse(x0_fit, y0_fit, R_fit);
      e->SetFillStyle(0);
      e->SetLineWidth(1);
      e->SetLineStyle(1);
      e->SetLineColor(line_color);
      e->Draw();
   };
};

int g_num_raw_hits[20];
int g_raw_hits_icell[20][400];
int g_raw_hits_iturn[20][400];
double g_raw_hits_xpos[20][400];
double g_raw_hits_ypos[20][400];

double g_R_sig[20][400];

void clear_buffer()
{
   for (int ilayer=0; ilayer<20; ilayer++) {
      g_num_raw_hits[ilayer] = 0;
      for (int icell=0; icell<g_num_cells[ilayer]; icell++) {
         g_R_sig[ilayer][icell] = 1e10;
      }
   }
}
void print_raw_hits(int ilayer)
{
   int nhits = g_num_raw_hits[ilayer];
   for (int ihit=0; ihit<nhits; ihit++) {
      printf("RAW:  ihit %d ilayer %d iturn %d icell %d xpos %f ypos %f\n", ihit, ilayer,
            g_raw_hits_iturn[ilayer][ihit], 
            g_raw_hits_icell[ilayer][ihit], 
            g_raw_hits_xpos[ilayer][ihit], 
            g_raw_hits_ypos[ilayer][ihit]);
   }
}
void add_raw_hits(int ilayer, int icell, int iturn, double x, double y)
{
   int n = g_num_raw_hits[ilayer];
   g_raw_hits_icell[ilayer][n] = icell;
   g_raw_hits_iturn[ilayer][n] = iturn;
   g_raw_hits_xpos[ilayer][n] = x;
   g_raw_hits_ypos[ilayer][n] = y;
   g_num_raw_hits[ilayer]++;
}
void remove_raw_hits(int ilayer, int icell)
{
   int num = g_num_raw_hits[ilayer];
   int n=0;
   for (int i=0; i<num; i++) {
      int this_icell = g_raw_hits_icell[ilayer][i];
      if (this_icell == icell) continue;
      g_raw_hits_icell[ilayer][n] = g_raw_hits_icell[ilayer][i];
      g_raw_hits_iturn[ilayer][n] = g_raw_hits_iturn[ilayer][i];
      g_raw_hits_xpos[ilayer][n]  = g_raw_hits_xpos[ilayer][i];
      g_raw_hits_ypos[ilayer][n]  = g_raw_hits_ypos[ilayer][i];
      n++;
   }
   g_num_raw_hits[ilayer]--;
}



struct Helix
{
   char name[128];
   double radius[20];

   int nhits;
   double xhits[1000];
   double yhits[1000];
   double zhits[1000];
   int hits_ilayer[1000];
   int hits_icell[1000];
   int hits_iturn[1000];

   int line_color;

   TMinuit* minuit;
   double chi2;
   double x0_fit;
   double y0_fit;
   double R_fit;
   double rad0_fit;
   double L_fit;

   double x0_ini;
   double y0_ini;
   double R_ini;
   double rad0_ini;
   double L_ini;

   double x0_step;
   double y0_step;
   double R_step;
   double rad0_step;
   double L_step;

   int wrong_order; // flag to check cell angle increment  (should be ascending order)

   double get_pt_fit()
   { 
      // p (GeV) = 0.3 * B (T) * R (m)
      // pm (MeV) * 1e-3 =  0.3 * B (T) * r (cm)*1e-2
      double B = 1.0; // T
      double pt = 3.0*B*R_fit; // MeV/c
      return pt;
   };
   double get_pz_fit()
   { 
      // p (GeV) = 0.3 * B (T) * R (m)
      // pm (MeV) * 1e-3 =  0.3 * B (T) * r (cm)*1e-2
      double B = 1.0; // T
      double pz = 3.0*B*L_fit; // MeV/c
      return pz;
   };
   double get_rad_fit(int ihit)
   {
      double dx = xhits[ihit] - x0_fit;
      double dy = yhits[ihit] - y0_fit;
      return TMath::ATan2(dy,dx);
   };
   double get_z1_fit()
   {
      return zhits[0];
   };
   Helix()
   {
      nhits = 0;

      int n = 0;
      radius[n++] = 51.4000;
      radius[n++] = 53.0000;
      radius[n++] = 54.6000;
      radius[n++] = 56.2000;
      radius[n++] = 57.8000;
      radius[n++] = 59.4000;
      radius[n++] = 61.0000;
      radius[n++] = 62.6000;
      radius[n++] = 64.2000;
      radius[n++] = 65.8000;
      radius[n++] = 67.4000;
      radius[n++] = 69.0000;
      radius[n++] = 70.6000;
      radius[n++] = 72.2000;
      radius[n++] = 73.8000;
      radius[n++] = 75.4000;
      radius[n++] = 77.0000;
      radius[n++] = 78.6000;
      radius[n++] = 80.2000;
      radius[n++] = 81.8000;

      minuit = new TMinuit(5);
      minuit->SetFCN(func_helix);
      g_xsig = 1.0;
      g_ysig = 1.0;
   };
   void set_name(char* a_name)
   {
      strcpy(name, a_name);
   };
   void set_line_color(int col)
   {
      line_color = col;
   };
   void clear()
   {
      nhits = 0;
   };
   void set_xypos_AB(Circle& circ1, Circle& circ2)
   {
      int n1 = circ1.nhits;
      int n2 = circ2.nhits;
      g_xA_circ1 = circ1.xhits[0];
      g_yA_circ1 = circ1.yhits[0];
      g_xB_circ1 = circ1.xhits[n1-1];
      g_yB_circ1 = circ1.yhits[n1-1];
      g_xA_circ2 = circ2.xhits[0];
      g_yA_circ2 = circ2.yhits[0];
      g_xB_circ2 = circ2.xhits[n2-1];
      g_yB_circ2 = circ2.yhits[n2-1];
   };
   void merge_hits(Circle& c1, Circle& c2)
   {
      // Assumption: 
      // (1) c1 is odd_layer and c2 is even_layer.
      // (2) both c1 and c2 are sorted by cell angles

      // Merge Method:
      // Two circles are merged by looking at layer numbers.
      // Collect cells in ilayer=1 from circ_odd until reaching ilayer=3
      // then collect in layer=2 from circ_even until reaching ilayer=4
      // repeat til end..


      //bool debug = true;
      bool debug = false;

      if (debug) {
         c1.print_cells();
         c2.print_cells();
      }

      nhits = 0;
      int n1 = c1.nhits;
      int n2 = c2.nhits;
      if (debug) printf("n1 %d n2 %d\n", n1, n2);

      Circle* circ[2]; // 0: even, 1: odd
      circ[0] = &c2;
      circ[1] = &c1;
      circ[0]->start_cell_taking();
      circ[1]->start_cell_taking();

      // start from ilayer=1 (ilayer=0 might have noise hits)
      // first, outgoing cells
      for (int ilayer=1; ilayer<=g_maxLayerIdx-2; ilayer++) {
         nhits += circ[ilayer%2]->take_hits_until_next_layer(ilayer, &xhits[nhits], &yhits[nhits], &hits_ilayer[nhits], &hits_icell[nhits], &hits_iturn[nhits]);
         if (debug) printf("take_hits: ilayer %d nhits %d\n", ilayer, nhits);
      }
      // second, top-1 cells
      nhits += circ[(g_maxLayerIdx-1)%2]->take_hits_by_half(g_maxLayerIdx-1, &xhits[nhits], &yhits[nhits], &hits_ilayer[nhits], &hits_icell[nhits], &hits_iturn[nhits]);
      if (debug) printf("take_hits: ilayer %d nhits %d (maxLayer - 1)\n", g_maxLayerIdx-1, nhits);
      // finally, top and ingoing cells
      for (int ilayer=g_maxLayerIdx; ilayer>=1; ilayer--) {
         nhits += circ[ilayer%2]->take_hits_until_next_layer(ilayer, &xhits[nhits], &yhits[nhits], &hits_ilayer[nhits], &hits_icell[nhits], &hits_iturn[nhits]);
         if (debug) printf("take_hits: ilayer %d nhits %d\n", ilayer, nhits);
      }

      if (debug) {
         for (int ihit=0; ihit<nhits; ihit++) {
            int ilayer = hits_ilayer[ihit];
            int icell = hits_icell[ihit];
            int iturn = hits_iturn[ihit];
            double x = xhits[ihit];
            double y = yhits[ihit];
            printf("Helix::add_hits: ihit %d ilayer %d icell %d iturn %d x %f y %f\n", ihit, ilayer, icell, iturn, x, y);
         }
      }
   };
   void copy_hits(Helix& other)
   {
      nhits = other.nhits;
      for (int ihit=0; ihit<nhits; ihit++) {
         xhits[ihit] = other.xhits[ihit];
         yhits[ihit] = other.yhits[ihit];
         zhits[ihit] = other.zhits[ihit];
         hits_ilayer[ihit] = other.hits_ilayer[ihit];
         hits_icell[ihit]  = other.hits_icell[ihit];
         hits_iturn[ihit]  = other.hits_iturn[ihit];
      }
   };
   void set_fit_inipar(double x0, double y0, double R, double rad0, double L)
   {
      x0_ini = x0;
      y0_ini = y0;
      R_ini = R;
      rad0_ini = rad0;
      L_ini = L;
      printf("set_fit_inipar:          x0 %7.3f y0 %7.3f R %7.3f rad0 %7.3f (deg) L %7.3f\n",x0,y0,R,rad2deg(rad0),L );

      x0_step = 1;
      y0_step = 1;
      R_step = 1;
      rad0_step = 1;
      L_step = 1;
   };
   void fit_helix(int sign)
   {
      // sing: +1: Pz>0
      //       -1: Pz<0

      double L_min;
      double L_max;
      if (sign>0) {
         L_min = 0;
         L_max = 200;
      } else {
         L_min = -200;
         L_max = 0;
      }
      // copy to global values
      g_nhits = nhits;
      for (int ihit=0; ihit<nhits; ihit++) {
         g_xhits[ihit] = xhits[ihit];
         g_yhits[ihit] = yhits[ihit];
         g_zhits[ihit] = 0.0; // zhits will be set in func_helix using xypos
         g_hits_ilayer[ihit] = hits_ilayer[ihit];
         g_hits_icell[ihit] = hits_icell[ihit];
         g_hits_iturn[ihit] = hits_iturn[ihit];
      }

      Int_t ierflag;
      Double_t arglist[10];
      TString Tag[5];
      Double_t var[5];
      Double_t verr[5];
      Double_t bnd1, bnd2;
      Int_t ivarbl;

      // suppress output
      arglist[0] = -1; 
      minuit->mnexcm("SET PRINT", arglist, 1, ierflag);

      // suppress warning message
      minuit->mnexcm("SET NOWarnings", arglist, 0, ierflag);

      // set initial values with limits
      minuit->mnparm(0, "x0", x0_ini, x0_step, 0, 0, ierflag);
      minuit->mnparm(1, "y0", y0_ini, y0_step, 0, 0, ierflag);
      minuit->mnparm(2 ,"R",  R_ini,  R_step,  20, 70, ierflag);
      minuit->mnparm(3 ,"rad0",  rad0_ini,  rad0_step, 0, 2.0*TMath::Pi(), ierflag);
      minuit->mnparm(4 ,"L",     L_ini,  L_step,  L_min, L_max, ierflag);

      // uset chi2
      arglist[0] = 1;
      minuit->mnexcm("SET ERR", arglist, 1, ierflag);

      // do minimize
      arglist[0] = 1000; // do at least 1000 function calls
      arglist[1] = 0.1;  // tolerance = 0.1
      minuit->mnexcm("MIGRAD", arglist, 2, ierflag);

      // copy fit results
      for (int i=0; i<5; i++) {
         minuit->mnpout(i, Tag[i], var[i], verr[i], bnd1, bnd2, ivarbl);
         //printf("i %d %f +/- %f\n", i, var[i], verr[i]);
      }
      x0_fit = var[0]; //cm
      y0_fit = var[1]; //cm
      R_fit  = var[2]; // cm
      rad0_fit  = var[3]; // rad
      L_fit  = var[4]; // cm

      // chi2
      Double_t amin,edm,errdef;
      Int_t nvpar,nparx,icstat;
      minuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
      chi2 = amin;

      for (int ihit=0; ihit<nhits; ihit++) {
         xhits[ihit] = g_xhits[ihit];
         yhits[ihit] = g_yhits[ihit];
         zhits[ihit] = g_zhits[ihit];
      }
      wrong_order = g_wrong_order;

      //printf("fit_result: x0 %5.1f y0 %5.1f R %5.1f rad %5.1f L %5.1f pt %5.1f pz %5.1f\n", x0_fit, y0_fit, R_fit, rad_fit, L_fit, get_pt_fit(), get_pz_fitt());
   };
   void print_fit_result(char* prefix)
   {
      printf("Fit: %s x0 %7.3f y0 %7.3f R %7.3f rad0 %7.3f (deg) L %7.3f z1 %7.3f (cm) pt %7.3f (MeV/c) pz %7.3f (MeV/c) chi2 %7.3f\n", 
            prefix, x0_fit, y0_fit, R_fit, rad2deg(rad0_fit), L_fit, get_z1_fit(), get_pt_fit(), get_pz_fit(), chi2);
   };

   // Draw
   void draw_xy_canvas()
   {
      TH2F*  h2 = new TH2F("fname-xy",Form("%s XY;X(cm);Y(cm)", name), 100, -100, 100, 100, -100, 100);
      h2->SetStats(0);
      h2->Draw();

      draw_radius();
   };
   void draw_xz_canvas()
   {
      TH2F*  h2 = new TH2F("fname-xz",Form("%s ZX;Z(cm);X(cm)", name), 100, -100, 100, 100, -100, 100);
      h2->SetStats(0);
      h2->Draw();
   };
   void draw_yz_canvas()
   {
      TH2F*  h2 = new TH2F("fname-yz",Form("%s ZY;Z(cm);Y(cm)", name), 100, -100, 100, 100, -100, 100);
      h2->SetStats(0);
      h2->Draw();
   };
   void draw_xy_hits_fits()
   {
      draw_xy_hits();
      draw_xy_fit();
      draw_xy_hits();
   };
   void draw_xz_hits_fits()
   {
      draw_xz_hits();
      draw_xz_fit();
      draw_xz_hits();
   };
   void draw_yz_hits_fits()
   {
      draw_yz_hits();
      draw_yz_fit();
      draw_yz_hits();
   };
   void draw_radius()
   {
      for (int ilayer=0; ilayer<20; ilayer++) {
         if (ilayer%2==0) continue;
         TEllipse* e = new TEllipse(0,0,radius[ilayer]);
         e->SetFillStyle(0);
         e->SetLineWidth(1);
         e->SetLineStyle(1);
         e->SetLineColor(kGray);
         e->Draw();
      }
   };
   void draw_xy_hits()
   {
      for (int ihit=0; ihit<nhits; ihit++) {
         TMarker* m = new TMarker(xhits[ihit], yhits[ihit], 8);
         set_marker_color(m, hits_iturn[ihit]);
         set_marker_style(m, hits_ilayer[ihit]);
         m->Draw();
      }
   };
   void draw_xz_hits()
   {
      for (int ihit=0; ihit<nhits; ihit++) {
         TMarker* m = new TMarker(zhits[ihit], xhits[ihit], 8);
         set_marker_color(m, hits_iturn[ihit]);
         set_marker_style(m, hits_ilayer[ihit]);
         m->Draw();
      }
   };
   void draw_yz_hits()
   {
      for (int ihit=0; ihit<nhits; ihit++) {
         TMarker* m = new TMarker(zhits[ihit], yhits[ihit], 8);
         set_marker_color(m, hits_iturn[ihit]);
         set_marker_style(m, hits_ilayer[ihit]);
         //printf("ihit %d xhits %f yhits %f zhits %f\n", ihit, xhits[ihit], yhits[ihit], zhits[ihit]);
         m->Draw();
      }
   };
   void draw_xy_fit()
   {
      TMarker* m = new TMarker(x0_fit, y0_fit, 1);
      m->SetMarkerColor(line_color);
      m->Draw();

      TEllipse* e = new TEllipse(x0_fit, y0_fit, R_fit);
      e->SetFillStyle(0);
      e->SetLineWidth(1);
      e->SetLineStyle(1);
      e->SetLineColor(line_color);
      e->Draw();
   };
   void draw_xz_fit()
   {
      // x0 + R*cos(rad0 + z/L)
      TF1* f1 = new TF1("f1", "[0] + [1]*cos([2]+x/[3])", -100, 100);
      f1->SetLineWidth(1);
      f1->SetLineStyle(1);
      f1->SetLineColor(line_color);
      f1->SetParameters(x0_fit, R_fit, rad0_fit, L_fit);
      f1->SetNpx(1000);
      f1->Draw("same");
   };
   void draw_yz_fit()
   {
      // x0 + R*cos(rad0 + z/L)
      TF1* f1 = new TF1("f1", "[0] + [1]*sin([2]+x/[3])", -100, 100);
      f1->SetLineWidth(1);
      f1->SetLineStyle(1);
      f1->SetLineColor(line_color);
      f1->SetParameters(y0_fit, R_fit, rad0_fit, L_fit);
      f1->SetNpx(1000);
      f1->Draw("same");
   };
};

struct TwoCircle
{
   double dr;
   double deg;
   void calc(Circle& c1, Circle& c2)
   {
      double dx = c2.x0_fit - c1.x0_fit;
      double dy = c2.y0_fit - c1.y0_fit;
      dr = TMath::Sqrt(dx*dx+dy*dy);
      double theta = TMath::ATan2(dy, dx);
      deg = theta/TMath::Pi()*180.0;
   };
   void print()
   {
      printf("dr %f deg %f\n", dr, deg);
   };
};


double estimate_z1(double dr)
{
   // Following formula is estimated by 
   // fitting z vs dr
   return (-51.3563+7.74943*dr);
}
double estimate_z2(double z1, double drad, double if_pz)
{
   // pz = MeV/c
   // L = cm
   double B = 1.0; // T
   double L = if_pz/(3.0*B); // cm
   printf("estimate_z2 if_pz %f (MeV/c) L %f cm\n", if_pz, L);
   return z1 + L * drad;
}
double estimate_pz(double z1, double z2, double drad)
{
   // drad is always positive
   // L is either positive or netive
   double L = (z2-z1)/drad; // cm
   double B = 1.0; // T
   double pz = 3.0*B*L; // MeV/c
   return pz;
}


struct Conformal
{
   int num_hits;
   int ilayers[10000];
   int icells[10000];
   int iturns[10000];
   // before
   double xhits[10000];
   double yhits[10000];
   // after
   double uhits[10000];
   double vhits[10000];
   double eu[10000];
   double ev[10000];
   Conformal()
   {
      num_hits = 0;
   };
   void add_hits(Circle& circ)
   {
      int n = num_hits;
      for (int ihit=0; ihit<circ.nhits; ihit++) {
         if (n>=10000) {
            fprintf(stderr,"Conformal: too many hits...\n");
            break;
         }
         ilayers[n] = circ.hits_ilayer[ihit];
         icells[n] = circ.hits_icell[ihit];
         iturns[n] = circ.hits_iturn[ihit];
         xhits[n] = circ.xhits[ihit];
         yhits[n] = circ.yhits[ihit];
         double r2 = xhits[ihit]*xhits[ihit] + yhits[ihit]*yhits[ihit];
         uhits[n] = 2.0*xhits[ihit]/r2;
         vhits[n] = 2.0*yhits[ihit]/r2;
         eu[n] = 1.0;
         ev[n] = 1.0;
         n++;
      }
      num_hits = n;
   };
};
struct Hough
{
   char name[128];

   TGraph* gr_uv;
   TGraph* gr_uv_inside;
   TH2F* h2ab;
   double found_a;
   double found_b;

   int num_hits; // all hits, both signal and noise
   int num_signal;
   int num_signal_inside;
   int num_signal_outside;

   int num_inside;
   int num_inside_signal;
   int num_inside_noise;

   double chi2;
   TGraphErrors* gr;
   TH1F* hdiff;
   double diff_threshold;

   double diff[10000];
   Hough(double threshold)
   {
      gr_uv = NULL;
      gr_uv_inside = NULL;
      h2ab = NULL;
      found_a = 1e10;
      found_b = 1e10;

      num_hits = 0;
      num_signal= 0;
      num_signal_inside= 0;
      num_signal_inside= 0;
      num_inside= 0;
      num_inside_signal= 0;
      num_inside_noise= 0;

      chi2 = 1e10;
      gr = NULL;
      hdiff = NULL;

      diff_threshold = threshold;
   };
   ~Hough()
   {
      if (gr!=NULL) delete gr;
      if (hdiff!=NULL) delete hdiff;
      if (h2ab!=NULL) delete h2ab;
      if (gr_uv!=NULL) delete gr_uv;
      if (gr_uv_inside!=NULL) delete gr_uv_inside;
   };
   void set_name(char* a_name)
   {
      strcpy(name, a_name);
   };
   void fit(int iev, double z1, double z2, int nhits, double* uhits, double* vhits, double* eu, double* ev)
   {
      if (gr!=NULL) delete gr;
      gr = new TGraphErrors(nhits, uhits, vhits, eu, ev);
      gr->Fit("pol1");
      TF1* f = gr->GetFunction("pol1");
      chi2 = f->GetChisquare();
      printf("iev %d z1 %f z2 %f chi2 %f\n", iev, z1, z2, chi2);
   };
   void transform(int nhits, double* uhits, double* vhits)
   {
      num_hits = nhits;

      double astep = 0.1;
      double amin = -8;
      double amax = 8;
      double bstep = 0.001;
      double bmin = -0.5;
      double bmax = 0.5;
      int anum = static_cast<int>((amax-amin)/astep);
      int bnum = static_cast<int>((bmax-bmin)/bstep);
      //printf("anum %d %f %f bnum %d %f %f\n", anum, amin, amax, bnum, bmin, bmax);
      if (h2ab==NULL) {
         h2ab = new TH2F("h2ab",Form("%s A-B Space;a;b",name),anum, amin, amax, bnum, bmin, bmax);
         h2ab->SetStats(0);
      }
      h2ab->Reset();

      gr_uv = new TGraph(num_hits, uhits, vhits);
      gr_uv->SetTitle(Form("%s U-V Space;u;v",name));

      for (int i=0; i<num_hits; i++) {
         for (int ia=0; ia<anum; ia++) {

            double a = ia*astep + amin;
            double b = -uhits[i]*a + vhits[i];

            //printf("i %d a %lf b %lf\n", i, a, b);
            h2ab->Fill(a, b, 1);
         }
      }
      int ia_min;
      int ib_min;
      int tmp;
      h2ab->GetMaximumBin(ia_min, ib_min, tmp);
      found_a = h2ab->GetXaxis()->GetBinCenter(ia_min);
      found_b = h2ab->GetYaxis()->GetBinCenter(ib_min);
   };
   void calc_diff(int num_hits, double* uhits, double* vhits, int* ilayers, int* icells, int* iturns, double* w_xs, double* w_ys, Circle& circ)
   {
      if (hdiff==NULL) {
         hdiff = new TH1F("hdiff",Form("%s Residual; Residual;",name), 100, -0.03, 0.03);
         gStyle->SetOptStat(1111111);
         hdiff->SetStats(1);
      }
      hdiff->Reset();

      num_signal=0;
      num_signal_inside=0;
      num_signal_outside=0;

      num_inside=0;
      num_inside_signal=0;
      num_inside_noise=0;

      double uhits_inside[1000];
      double vhits_inside[1000];

      for (int ihit=0; ihit<num_hits; ihit++) {
         if (iturns[ihit]!=-1) num_signal++;

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
   void print_result(int iev)
   {
      printf("Hough:: iev %d found_a %f found_b %f ", iev, found_a, found_b);
      printf("signal: inside %5.2f (%d/%d) outside %5.2f (%d/%d) ", 
            (double)num_signal_inside/num_signal, num_signal_inside, num_signal,
            (double)num_signal_outside/num_signal, num_signal_outside, num_signal);
      printf("inside: signal %5.2f (%d/%d) noise %5.2f (%d/%d)\n", 
            (double)num_inside_signal/num_inside, num_inside_signal, num_inside,
            (double)num_inside_noise/num_inside, num_inside_signal, num_inside);
   };
   TF1* get_line()
   {
      TF1* f1 = new TF1("f1", "[0]+[1]*x", -1e-1, 1e-1);
      f1->SetParameters(found_b, found_a);
      return f1;
   };

   void draw_hist_ab()
   {
      h2ab->Draw("colz");
      TMarker* m1 = new TMarker(found_a, found_b, 33);
      m1->SetMarkerColor(kRed);
      m1->SetMarkerSize(3.0);
      m1->Draw("same");
   };
   void draw_hist_uv()
   {
      TH2F* hframe = new TH2F("hframe","",10,-0.1, 0.1, 10, -0.1, 0.1);
      hframe->SetStats(0);
      hframe->Draw();
      hframe->SetTitle(gr_uv->GetTitle());
      get_line()->Draw("same");
      gr_uv->Draw("p same");
      gr_uv_inside->Draw("p same");
   };
   void draw_hist_diff()
   {
      hdiff->Draw();
      gPad->Modified();
      gPad->Update();
      double ymax = gPad->GetFrame()->GetY2();
      double x1L = -diff_threshold, y1L = 0.0;
      double x2L = +diff_threshold, y2L = 0.0;
      double x1R = -diff_threshold, y1R = ymax;
      double x2R = +diff_threshold, y2R = ymax;
      TLine* l1 = new TLine(x1L, y1L, x1R, y1R); l1->SetLineColor(kRed); l1->Draw("same");
      TLine* l2 = new TLine(x2L, y2L, x2R, y2R); l2->SetLineColor(kRed); l2->Draw("same");
   };
};

// Stats information will be written in text file.
/*
   struct Stats
   {
   int num_signal_inside;
   int num_signal_outside;
   TH1F* h1_ratio_signal_inside;
   TH1F* h1_ratio_signal_outside;
   Stats()
   {
   num_signal_inside = 0;
   num_signal_outside = 0;
   h1_ratio_signal_inside = new TH1F("h1_ratio_signal_inside","", 100, 0, 1);
   h1_ratio_signal_outside = new TH1F("h1_ratio_signal_outside","", 100, 0, 1);
   };
   void set_num_signal_inside(int num) { num_signal_inside = num; };
   void set_num_signal_outside(int num) { num_signal_outside = num; };
   void fill()
   {
   int num_signal = num_signal_inside + num_signal_outside;
   h1_ratio_signal_inside -> Fill((double)num_signal_inside/num_signal);
   h1_ratio_signal_outside -> Fill((double)num_signal_outside/num_signal);
   };
   void draw_hist_ratio_signal_inside()
   {
   h1_ratio_signal_inside->Draw();
   };
   void draw_hist_ratio_signal_outside()
   {
   h1_ratio_signal_outside->Draw();
   };
   };
 */

struct Config
{
   /* config file */
   char input_root[1280];
   char wire_config[1280];
   char sample_type[16];
   char t2r_type[16];
   double rdrift_err_cm;
   double posSmear_cm;
   double momSmear_percent;
   double noise_occupancy;
   double diff_threshold;
   char turn_type[16];
   /* command line argument */
   char* config_file[1280];
   char output_dir[128];
   int iev1;
   int iev2;
   bool make_pdf;
   bool make_txt;
   void parse_option(int argc, char** argv)
   {
      for (int i=0; i<argc; i++) {
         printf("i %d %s\n", i, argv[i]);
      }
      if (argc!=7) {
         fprintf(stderr,"Usage %s <config.txt> <output_dir> <iev1> <iev2> <make_pdf:yes|no> <make_txt:yes|no>\n", argv[0]);
         exit(1);
      }
      parse_config(argv[1]);
      strcpy(output_dir,argv[2]);
      iev1 = atoi(argv[3]);
      iev2 = atoi(argv[4]);
      if (strcmp(argv[5],"yes")==0) {
         make_pdf = true;
      } else {
         make_pdf = false;
      }
      if (strcmp(argv[6],"yes")==0) {
         make_txt = true;
      } else {
         make_txt = false;
      }

      // make output directory
      mkdir(output_dir, 0755);
      mkdir(Form("%s/pdf/",output_dir), 0755);
   };
   void parse_config(char* config_txt)
   {
      FILE* fp = fopen(config_txt,"r");
      if (fp==NULL) {
         fprintf(stderr,"ERROR: parse_option: cannot open file '%s'\n", config_txt);
         exit(1);
      }
      char line[1280];
      char key[128];
      char value[128];
      while (fgets(line, sizeof(line), fp)) {
         if (line[0]=='#') continue; // skip comment line
         sscanf(line, "%s | %s", key, value);
         //printf("'%s' '%s'\n", key, value);
         set_value_char(key,value,input_root,         "input_root");
         set_value_char(key,value,wire_config,        "wire_config");
         set_value_char(key,value,sample_type,        "sample_type");
         set_value_char(key,value,t2r_type,           "t2r_type");
         set_value_double(key,value,&rdrift_err_cm,   "rdrift_err_cm");
         set_value_double(key,value,&posSmear_cm,     "posSmear_cm");
         set_value_double(key,value,&momSmear_percent,"momSmear_percent");
         set_value_double(key,value,&noise_occupancy, "noise_occupancy");
         set_value_double(key,value,&diff_threshold,  "diff_threshold");
         set_value_char(key,value,turn_type,          "turn_type");
      }
      fclose(fp);

   };
   void set_value_char(char* key, char* value, char* set_value, char* set_key)
   {
      if (strcmp(key,set_key)==0) {
         strcpy(set_value, value);
         printf("%s %s\n", key, set_value);
      }
   };
   void set_value_double(char* key, char* value, double* set_value, char* set_key)
   {
      if (strcmp(key,set_key)==0) {
         *set_value = atof(value);
         printf("%s %f\n", key, *set_value);
      }
   };
   void set_value_int(char* key, char* value, int* set_value, char* set_key)
   {
      if (strcmp(key,set_key)==0) {
         *set_value = atoi(value);
         printf("%s %d\n", key, *set_value);
      }
   };
};
int main(int argc, char** argv)
{
   Config config;
   config.parse_option(argc, argv);

   char* input_root = config.input_root;
   char* wire_config_txt = config.wire_config;
   char* sample_type = config.sample_type;
   char* t2r_type = config.t2r_type;
   double rdrift_err_cm = config.rdrift_err_cm;
   double posSmear_cm = config.posSmear_cm;
   double momSmear_percent = config.momSmear_percent;
   double noise_occupancy = config.noise_occupancy;


   /* Initialize global variables */
   set_icell_region();

   /* Setup inputs */
   InputROOT inROOT(input_root, wire_config_txt, sample_type, t2r_type, rdrift_err_cm, posSmear_cm, momSmear_percent);
   g_config = inROOT.getConfig();
   //int total = inROOT.getEntries();
   //int total = 100;


   double w_x1;
   double w_y1;
   double w_z1;
   double w_x2;
   double w_y2;
   double w_z2;
   double w_x;
   double w_y;
   double w_z;

   // Raw hits
   Circle circ1Raw; // odd-layer
   Circle circ2Raw; // even-layer
   Circle circ3Raw; // odd/even-layer 
   circ1Raw.set_name("Raw odd-layer");
   circ2Raw.set_name("Raw even-layer");
   circ3Raw.set_name("Raw odd/even-layer");
   circ1Raw.set_line_color(kRed);
   circ2Raw.set_line_color(kBlue);

   // After removing single hit cells
   Circle circ1Clus; // odd-layer
   Circle circ2Clus; // even-layer
   Circle circ3Clus; // odd/even-layer 
   circ1Clus.set_name("Cluster odd-layer");
   circ2Clus.set_name("Cluster even-layer");
   circ3Clus.set_name("Cluster odd/even-layer");
   circ1Clus.set_line_color(kRed);
   circ2Clus.set_line_color(kBlue);

   // After filtering by conf_hough transformation
   Circle circ1; // odd-layer
   Circle circ2; // even-layer
   Circle circ3; // odd/even-layer
   circ1.set_name("Hough odd-layer");
   circ2.set_name("Hough even-layer");
   circ3.set_name("Hough odd/even-layer");
   circ1.set_line_color(kRed);
   circ2.set_line_color(kBlue);

   Helix helix[2];
   helix[0].set_name("Helix odd-layer");
   helix[1].set_name("Helix even-layer");
   helix[0].set_line_color(kMagenta); // positive ini_pz
   helix[1].set_line_color(kMagenta); // negative ini_pz

   FILE* fpout=NULL;
   if (config.make_txt) {
      fpout = fopen(Form("%s/output.txt",config.output_dir),"w");
      if (fpout==NULL) {
         fprintf(stderr,"ERROR: cannot open for write '%s/output.txt'\n", config.output_dir);
         exit(1);
      }
   }

   bool single_turn=false;
   if (strcmp(config.turn_type,"single")==0) single_turn=true;

   time_t time1 = time(NULL);

   for (int iev=config.iev1; iev<=config.iev2; iev++) { 
      bool debug = false;
      //bool debug = true;

      fprintf(stderr,"iev %d\n", iev);
      clear_buffer();

      inROOT.getEntry(iev);
      bool directHit = inROOT.InDirectHitAtTriggerCounter();
      if (!directHit) continue;

      int numHits = inROOT.getNumHits();
      if (numHits==0) continue;

      g_maxLayerIdx = inROOT.getMaxLayerIdx();

      circ1Raw.clear();
      circ2Raw.clear();
      circ1Clus.clear();
      circ2Clus.clear();
      circ1.clear();
      circ2.clear();

      //printf("iev %d numHits %d\n", iev, numHits );

      /* Get signal hits */
      double zpos = -1;
      int icell1 = -1;
      int icell2 = -1;
      for (int ihit=0; ihit<numHits; ihit++) {
         int ilayer = inROOT.getIlayer(ihit);
         int icell = inROOT.getIcell(ihit);
         int iturn = inROOT.getIturn(ihit);

         g_R_sig[ilayer][icell] = inROOT.getDriftDistance(iev, ihit);

         if (single_turn && iturn>=1) break;
         if (debug) printf("ihit %d iturn %d ilayer %d icell %d\n", ihit, iturn, ilayer, icell);

         inROOT.getWirePosAtEndPlates(ihit, w_x1, w_y1, w_z1, w_x2, w_y2, w_z2);

         if (ilayer%2==1) circ1Raw.add_hit(ilayer, icell, iturn, w_x1, w_y1);
         if (ilayer%2==0) circ2Raw.add_hit(ilayer, icell, iturn, w_x1, w_y1);

         add_raw_hits(ilayer, icell, iturn, w_x1, w_y1);
      }

      /* Add noise. If R_noise is larger than R_sig, then use R_sig. */
      for (int ilayer=0; ilayer<20; ilayer++) {
         for (int icell=0; icell<g_num_cells[ilayer]; icell++) {
            config_get_wire_pos(g_config, ilayer, LAYER_TYPE_SENSE, icell, WIRE_TYPE_SENSE, 0.0, "up", &w_x1, &w_y1);
            double prob = gRandom->Uniform();
            double R_noise = gRandom->Uniform(0, 1.6);
            double R_sig = g_R_sig[ilayer][icell];
            if (prob<noise_occupancy) {
               if (R_noise < R_sig) {
                  // replace with noise hit
                  if (R_sig < 100) {
                     if (debug) printf("should replace with noise hit, ilayer %d icell %d\n", ilayer, icell);
                     if (ilayer%2==1) circ1Raw.remove_hit(ilayer, icell);
                     if (ilayer%2==0) circ2Raw.remove_hit(ilayer, icell);
                     remove_raw_hits(ilayer, icell);
                  }
                  if (ilayer%2==1) circ1Raw.add_hit(ilayer, icell, -1, w_x1, w_y1);
                  if (ilayer%2==0) circ2Raw.add_hit(ilayer, icell, -1, w_x1, w_y1);

                  add_raw_hits(ilayer, icell, -1, w_x1, w_y1);
               }
            }
         }
      }

      /* Remove single hit cells */
      for (int ilayer=0; ilayer<20; ilayer++) {
         // If left and right cells are not next, middle cell is isolated, so remove this.
         for (int ihit=0; ihit<g_num_raw_hits[ilayer]; ihit++) {
            int ihitL = ihit-1;
            int ihitM = ihit;
            int ihitR = ihit+1;
            if (ihitL<0) ihitL = g_num_raw_hits[ilayer] - 1;
            if (ihitR>=g_num_cells[ilayer]) ihitR  = 0;
            int icellL = g_raw_hits_icell[ilayer][ihitL];
            int icellM = g_raw_hits_icell[ilayer][ihitM];
            int icellR = g_raw_hits_icell[ilayer][ihitR];
            int iturn = g_raw_hits_iturn[ilayer][ihitM];
            double x = g_raw_hits_xpos[ilayer][ihitM];
            double y = g_raw_hits_ypos[ilayer][ihitM];
            if (debug) printf("$$$$$ ilayer %d ihit %d icellM %d iturn %d", ilayer, ihit, icellM, iturn);
            int icellL2 = icellL+1; if (icellL2>=g_num_cells[ilayer]) icellL2 -= g_num_cells[ilayer];
            int icellR2 = icellR-1; if (icellL2<0) icellR = 0;
            if (icellL2 != icellM && icellM != icellR2) {
               if (debug) printf("--> excluded\n");
            } else {
               if (debug) printf("--> included\n");
               if (ilayer%2==1) circ1Clus.add_hit(ilayer, icellM, iturn, x, y);
               if (ilayer%2==0) circ2Clus.add_hit(ilayer, icellM, iturn, x, y);
            }
         }
      }

      /* Conformal/Hough transformation */

      Conformal conf1; // odd-layer
      Conformal conf2; // even-layer
      conf1.add_hits(circ1Clus);
      conf2.add_hits(circ2Clus);

      Hough hough1(config.diff_threshold); // odd-layer
      Hough hough2(config.diff_threshold); // even-layer
      hough1.set_name("Hough odd-layer");
      hough2.set_name("Hough even-layer");

      hough1.transform(conf1.num_hits, conf1.uhits, conf1.vhits);
      hough1.calc_diff(conf1.num_hits, conf1.uhits, conf1.vhits, conf1.ilayers, conf1.icells, conf1.iturns, conf1.xhits, conf1.yhits, circ1);
      hough1.print_result(iev);

      hough2.transform(conf2.num_hits, conf2.uhits, conf2.vhits);
      hough2.calc_diff(conf2.num_hits, conf2.uhits, conf2.vhits, conf2.ilayers, conf2.icells, conf2.iturns, conf2.xhits, conf2.yhits, circ2);
      hough2.print_result(iev);

      circ1.set_fit_inipar();
      circ2.set_fit_inipar();
      circ1.fit_circ();
      circ2.fit_circ();
      circ1.print_fit_result(Form("Circ1: iev %d", iev));
      circ2.print_fit_result(Form("Circ2: iev %d", iev));

      struct TwoCircle tc;
      tc.calc(circ1, circ2);
      tc.print();

      /* Sort cells */
      // Before going to 3d helical fitting, first cells should be sorted in correct way.
      // Order of cell is very important in helical fitting because zpos are calculated assuming
      // cells are aligned sequentially (anti-clock wise in this MC)

      // sort data stored in new circle
//      printf("!!!! Sorting cells !!!!\n");
//      circ1.sort_cells();
//      circ2.sort_cells();


      double B = 1.0; // T
      double x0_ini = circ1.x0_fit;
      double y0_ini = circ1.y0_fit;
      double  R_ini = circ1.R_fit;
      double z1_ini = estimate_z1(tc.dr);
      double rad0_ini;
      double L_ini;
      double pa_ini = 104.0;
      double pt_ini = 3.0*B*R_ini;
      double pz_ini;

      // pz_guess should be tested both positive and negative case
      for (int isign=0; isign<2; isign++) {
         int sign=1;
         if (isign==1) sign = -1;
         pz_ini = sign*sqrt2minus(pa_ini, circ1.get_pt_fit()); // assume positive
         if (pz_ini==0) pz_ini = sign*0.1; // set anyway
         //pz_ini=sign*45.0;
         L_ini = pz_ini/(3.0*B);
         rad0_ini = circ1.get_radA_fit() - z1_ini/L_ini;
         while (rad0_ini<0) {
            rad0_ini += 2.0*TMath::Pi();
         }
         while (rad0_ini>2.0*TMath::Pi()) {
            rad0_ini -= 2.0*TMath::Pi();
         }

         helix[isign].clear();
         helix[isign].set_xypos_AB(circ1, circ2);
         helix[isign].merge_hits(circ1, circ2);
         helix[isign].set_fit_inipar(x0_ini, y0_ini, R_ini, rad0_ini, L_ini);
         helix[isign].fit_helix(sign);
         if (debug) printf("==fit==\n");
      }

      int imin = 0;
      if (helix[1].chi2 < helix[0].chi2) imin = 1;

      TVector3 mcPos;
      TVector3 mcMom;
      inROOT.getPosMom(0, mcPos, mcMom);
      double mc_z1 = mcPos.Z();
      double mc_pt = sqrt2(mcMom.X(), mcMom.Y())*1e3; // GeV -> MeV
      double mc_pz = mcMom.Z()*1e3; // GeV -> MeV

      if (fpout!=NULL) {
         fprintf(fpout,"%5d %2d %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d %7.3f %7.3f %7.3f %7.3f %d %d %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f %7.3f\n",
               iev, 
               g_maxLayerIdx,
               // Circ1,2
               circ1.x0_fit, circ1.y0_fit, circ1.R_fit,
               circ2.x0_fit, circ2.y0_fit, circ2.R_fit,
               // Hough
               hough1.num_signal, hough1.num_signal_inside, hough1.num_signal_outside,
               hough1.num_inside, hough1.num_inside_signal, hough1.num_inside_noise,
               hough2.num_signal, hough2.num_signal_inside, hough2.num_signal_outside, 
               hough2.num_inside, hough2.num_inside_signal, hough2.num_inside_noise,
               // TwoCircle
               tc.dr,
               // MC
               mc_z1, mc_pt, mc_pz,
               // Helix
               imin,
               helix[0].nhits, helix[0].x0_ini, helix[0].y0_ini, helix[0].R_ini, 
               helix[0].rad0_ini, helix[0].L_ini,
               helix[1].rad0_ini, helix[1].L_ini,
               helix[0].chi2, helix[0].x0_fit, helix[0].y0_fit, helix[0].R_fit, helix[0].rad0_fit, helix[0].L_fit, helix[0].get_z1_fit(), helix[0].get_pt_fit(), helix[0].get_pz_fit(),
               helix[1].chi2, helix[1].x0_fit, helix[1].y0_fit, helix[1].R_fit, helix[1].rad0_fit, helix[1].L_fit, helix[1].get_z1_fit(), helix[1].get_pt_fit(), helix[1].get_pz_fit());

         fflush(fpout);
      }

      printf("MC:                                                                                   z1 %7.3f (cm) pt %7.3f (MeV/c) pz %7.3f (MeV/c)\n", mc_z1, mc_pt, mc_pz);
      helix[0].print_fit_result(Form("Helix(pz>0): iev %d", iev));
      helix[1].print_fit_result(Form("Helix(pz<0): iev %d", iev));

      if (config.make_pdf) {
         TCanvas* c1 = new TCanvas("c1","",3000,9000);
         c1->Divide(3,9);
         int j=1;
         c1->cd(j++); circ1Raw.draw_xy_canvas(); circ1Raw.draw_xy_hits_fits();
         c1->cd(j++); circ2Raw.draw_xy_canvas(); circ2Raw.draw_xy_hits_fits();
         c1->cd(j++); circ3Raw.draw_xy_canvas(); circ1Raw.draw_xy_hits_fits(); circ2Raw.draw_xy_hits_fits();
         c1->cd(j++); circ1Clus.draw_xy_canvas(); circ1Clus.draw_xy_hits_fits();
         c1->cd(j++); circ2Clus.draw_xy_canvas(); circ2Clus.draw_xy_hits_fits();
         c1->cd(j++); circ3Clus.draw_xy_canvas(); circ1Clus.draw_xy_hits_fits(); circ2Clus.draw_xy_hits_fits();
         c1->cd(j++); hough1.draw_hist_uv();
         c1->cd(j++); hough2.draw_hist_uv();
         c1->cd(j++); 
         c1->cd(j++); hough1.draw_hist_ab();
         c1->cd(j++); hough2.draw_hist_ab();
         c1->cd(j++); 
         c1->cd(j++); hough1.draw_hist_diff();
         c1->cd(j++); hough2.draw_hist_diff();
         c1->cd(j++); 
         c1->cd(j++); circ1.draw_xy_canvas(); circ1.draw_xy_hits_fits();
         c1->cd(j++); circ2.draw_xy_canvas(); circ2.draw_xy_hits_fits();
         c1->cd(j++); circ3.draw_xy_canvas(); circ1.draw_xy_hits_fits(); circ2.draw_xy_hits_fits();
         c1->cd(j++); helix[0].draw_xy_canvas(); helix[0].draw_xy_hits_fits();
         c1->cd(j++); helix[0].draw_xz_canvas(); helix[0].draw_xz_hits_fits();
         c1->cd(j++); helix[0].draw_yz_canvas(); helix[0].draw_yz_hits_fits();
         c1->cd(j++); helix[1].draw_xy_canvas(); helix[1].draw_xy_hits_fits();
         c1->cd(j++); helix[1].draw_xz_canvas(); helix[1].draw_xz_hits_fits();
         c1->cd(j++); helix[1].draw_yz_canvas(); helix[1].draw_yz_hits_fits();
         c1->cd(j++); helix[0].draw_xy_canvas(); helix[0].draw_xy_hits_fits(); helix[1].draw_xy_hits_fits();
         c1->cd(j++); helix[0].draw_xz_canvas(); helix[0].draw_xz_hits_fits(); helix[1].draw_xz_hits_fits();
         c1->cd(j++); helix[0].draw_yz_canvas(); helix[0].draw_yz_hits_fits(); helix[1].draw_yz_hits_fits();
         c1->Print(Form("%s/pdf/%05d.pdf", config.output_dir, iev));
      }
   }

   fclose(fpout);

   time_t time2 = time(NULL);
   int dn = config.iev2-config.iev1+1;
   int dt = time2-time1;
   printf("Run summary\nNevent %d\nTime %d\nSpeed %f (Hz)\n\n", dn, dt, (double)dn/dt);

   return 0;
}
