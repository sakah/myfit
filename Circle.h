#ifndef _CIRC_H
#define _CIRC_H

class Circle
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

#endif

