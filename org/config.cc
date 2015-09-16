#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "config.h"
//#include "wire.h"

#include "TFile.h"
#include "TTree.h"
#include "TPaveText.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TMarker.h"
#include "TMath.h"
#include "TLine.h"
#include "TText.h"
#include "TVector3.h"
#include "TSpline.h"

static TSpline3* get_xtcurve_spline(struct config* config, struct XTcurve* xt_up, struct XTcurve* xt_down, int up_down, int cid, int ibeta, int iatan2);
static double find_xval(int ntry, double Tmax, double Rmax, TSpline3* spl, double y, double x1, double x2);

int config_get_sense_layer_size(struct config* config)
{
   return config->sense_layer_size;
}
int config_get_cell_size(struct config* config, int cid)
{
   int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
   return config->cell_size[wid];
}
void config_init(char* fname, struct config* config)
{
    FILE* fp = fopen(fname,"r");
    if (fp==NULL) {
        fprintf(stderr,"ERROR: failed to open %s\n",fname);
        exit(1);
    }
    char line[1280];
    char type[1280];
    char body[1280];

    int layer_size=0;
    while (fgets(line,sizeof(line),fp)) {
        if (line[0]=='#')
            continue;

        sscanf(line,"%s %s",type,body);
        //printf("type = '%s', body = '%s'\n",type,body);
        if (strcmp(type,"format_type")==0) { 
           strcpy(config->format_type, body);
        } else if (strcmp(type,"layer_size")==0) { // <= include both sense and field layers
           config->sense_layer_size = 0;
           config->layer_size = atoi(body); 
           config->layer_radius_at_endplate = (double*)malloc(sizeof(double)*config->layer_size);
           config->cell_size = (int*)malloc(sizeof(int)*config->layer_size);
           config->cell_width = (double*)malloc(sizeof(double)*config->layer_size);
           config->shift = (double*)malloc(sizeof(double)*config->layer_size);
           config->theta0_at_endplate = (double*)malloc(sizeof(double)*config->layer_size);
           config->length = (double*)malloc(sizeof(double)*config->layer_size);
        } else if (strcmp(type,"layer")==0) { 
           char name[12];
           int wid;                    // Wire Layer ID (start from 1)
           int cid;                    // Cell Layer ID (start from 0)
           char type;                  // G, F, S
           char stsign;                // +, -
           double radius_at_center;    // cm
           double radius_at_endplate;  // cm
           double length;              // Distance between bushes of feedthrough
           int num_wires;              // Number of wires (=2*Cells)
           int num_skip;               // Number of skip holes (=2*Shift)
           double dphi_mrad;           // Difference of angle at endplates = theta_AB
           double stdrop_cm;           // stereo drop
           double stangle_mrad;        // stereo angle
           double theta0_at_endplate;  // first hole's angle at the end plate
           double cell_width;          // cell_width (mrad)
           double shift;               // shift (double, for format_type=prototype)
           int ncol;
           int first_sense_hole_pos;  // 0,1,2... (2014/02/01)
           if (strcmp(config->format_type,"prototype")==0) {
              ncol = sscanf(line,"%s %d %d %c %c %lf %lf %d %lf %lf %d %lf",
                    name, &wid, &cid, &type, &stsign, &radius_at_endplate, &length, &num_wires, &shift, &theta0_at_endplate, &first_sense_hole_pos, &cell_width);
              if (ncol!=12) {
                 fprintf(stderr,"ERROR: format is not correct!\n");
                 exit(1);
              }
           } else if (strcmp(config->format_type,"20140104")==0) {
              ncol = sscanf(line,"%s %d %d %c %c %lf %lf %lf %d %d %lf %lf %lf %lf",
                    name, &wid, &cid, &type, &stsign, &radius_at_center, &radius_at_endplate, &length, &num_wires, &num_skip, &dphi_mrad, &stdrop_cm, &stangle_mrad, &theta0_at_endplate);
              if (ncol!=14) {
                 fprintf(stderr,"ERROR: format is not correct!\n");
                 exit(1);
              }
           } else {
              fprintf(stderr,"ERROR: format_type is not set!\n");
              exit(1);
           }
           if (type=='G'||type=='S') {
              config->sense_layer_size++;
           }

           config->length[layer_size] = length;
           config->layer_radius_at_endplate[layer_size] = radius_at_endplate;
           config->cell_size[layer_size] = num_wires/2;

           if (strcmp(config->format_type,"prototype")==0) {
              config->cell_width[layer_size] = cell_width*1e-3; // mrad -> rad
              config->shift[layer_size] = shift;
              config->theta0_at_endplate[layer_size] = theta0_at_endplate*1e-3 + first_sense_hole_pos * cell_width*1e-3/2.0;
           } else {
              config->cell_width[layer_size] = 2.0*TMath::Pi()/config->cell_size[layer_size]; 
              config->shift[layer_size] = num_skip/2;
              config->theta0_at_endplate[layer_size] = theta0_at_endplate*1e-3;
           }

           printf("type %c wid %d cid %d raidus_at_endplate %lf (cm) length %lf (cm) cell_size %d shift %lf theta0_at_endplate %lf (mrad) stereo_drop %lf (cm) first_sense_hole_pos %d\n", 
                 type,wid,cid,radius_at_endplate,length, config->cell_size[layer_size],config->shift[layer_size],theta0_at_endplate, stdrop_cm, first_sense_hole_pos);

           layer_size++;
        }
        else if (strcmp(type,"inner_wall_radius(cm)")==0) { config->inner_wall_radius = atof(body); }  // 2013/12/04
        else if (strcmp(type,"outer_wall_radius(cm)")==0) { config->outer_wall_radius = atof(body); }  // 2013/12/04
        else {
           fprintf(stderr,"ERROR: unknow type -> '%s'\n", type);
           exit(1);
        }
    }
    if (layer_size!=config->layer_size) {
       fprintf(stderr,"ERROR: layer size is not equal with one you set in layer_size (ilayer=%d, config->layer_size %d)\n", layer_size, config->layer_size);
       exit(1);
    }

    /* 2013/12/04
       config->cdc_rmin = config->layer_radius[0] - config->layer_spacing[0]/2.0;
       if (config->cdc_rmin<0) config->cdc_rmin = 0; 
       */
    //config->cdc_rmin = config->inner_wall_radius;
    //if (config->cdc_rmin<0) config->cdc_rmin = 0; 

    fclose(fp);
    printf("config_init: read %d layers (%d sense layers)\n", config->layer_size, config->sense_layer_size);
    //exit(1);
}
void config_print(FILE* fp, struct config* config)
{
   fprintf(fp, "layer_size        %d\n", config->layer_size);
   fprintf(fp, "inner_wall_radius %lf\n",config->inner_wall_radius);
   fprintf(fp, "outer_wall_radius %lf\n",config->outer_wall_radius);
#if 0
   printf("---------------------\n");
   printf("-- End plate\n");
   printf("---------------------\n");
   double layer_spacing;
   for (int ilayer = 0; ilayer < config->layer_size; ilayer++) {
      fprintf(fp, "layer_id %3d cell_size %4d shift %3d radius(cm) %lf cell_width(cm) %lf spacing(cm) %lf stereo_angle(rad) %lf\n",
            ilayer+1,config->cell_size[ilayer],config->shift[ilayer],config_get_sense_and_field_layer_radius(config, ilayer, 0),
            config_get_cell_width_cm(config, ilayer, 0), config->layer_spacing[i], config->stereo_angle[i]);
   }
   printf("----------------------------\n");
   printf("-- CDC center\n");
   printf("----------------------------\n");
   for (int i = 0; i < config->layer_size; i++) {
      fprintf(fp, "layer_id %3d cell_size %4d shift %3d radius(cm) %lf dlen(cm) %lf 2dlen(cm) %lf staggerd(rad) %lf spacing(cm) %lf stereo_angle(rad) %lf\n",
            i+1,config->cell_size[i],config->shift[i],config->layer_radius_at_center[i],config->cell_dlen_at_center[i],config->cell_dlen_at_center[i]*2.0,config->staggered_offset[i],config->layer_spacing_at_center[i], config->stereo_angle[i]);
   }
#endif
}
void config_print_all(FILE* fp, struct config* config)
{
   double xs, ys;
   double xf, yf;
   double z_from_up = 0.0; // at end plate
   int global_ilayer=0;
   fprintf(fp, "#layer wire global  local wire  x(cm)      y(cm)\n");
   for (int wid = 0; wid < config->layer_size; wid++) {
      for (int icell = 0; icell < config->cell_size[wid]; icell++) {
         config_get_wire_pos(config, wid, icell, WIRE_TYPE_SENSE, z_from_up, "up", &xs, &ys);
         config_get_wire_pos(config, wid, icell, WIRE_TYPE_FIELD, z_from_up, "up", &xf, &yf);
         fprintf(fp, "sense wire %5d %5d %10.5lf %10.5lf\n", wid+1,icell+1,xs,ys);
         fprintf(fp, "field wire %5d %5d %10.5lf %10.5lf\n", wid+1,icell+1,xf,yf);
      }
   }
}
#if 0
int config_get_axial_layer(struct config* config, int* axials)
{
   int i;
   int num=0;
   for (i = 0; i < config->layer_size; i++) {
      if (config->shift[i]==0) {
         axials[num] = i;
         num++;
      }
   }
   return num;
}
#endif
int config_get_wid(struct config* config, int cid, int layer_type)
{
   // Start from Guard layer
   // Note on wid: In Excel, wid start from 1, but in code, start from 0
   int ilayer;
   if (strcmp(config->format_type,"prototype")==0) {
      if (layer_type==LAYER_TYPE_SENSE) {
         ilayer = cid * 2;
      } else {
         ilayer = cid * 2 + 1;
      }
   } else {
      if (layer_type==LAYER_TYPE_SENSE) {
         ilayer = cid * 2;
      } else {
         ilayer = cid * 2 - 1;
      }
   }
   return ilayer;
}

double config_get_layer_radius_at_center(struct config* config, int wid)
{
   double drad = config_get_cell_width_rad(config, wid);
   double theta_AB =  drad*config->shift[wid];
   double Rz0 = config->layer_radius_at_endplate[wid]*TMath::Cos(theta_AB/2.0);
   return Rz0;
}
double config_get_layer_radius_at_center(struct config* config, int cid, int layer_type)
{
   int wid = config_get_wid(config, cid, layer_type);
   return config_get_layer_radius_at_center(config, wid);
}
double config_get_layer_radius(struct config* config, int wid, double z_from_up)
{
   /*
    * field layer of ilayer is just outside of sense layer of ilayer
    *
    *  outer_wall
    *  ========== sense/guard (last)
    *
    *  ---------- field (ilayer+1)
    *  ========== sense (ilayer+1)
    *  ---------- field (ilayer)
    *  ========== sense (ilayer)
    *  ---------- field (ilayer-1)
    *  ========== sense (ilayer-1)
    *
    *  ========== sense/guard (first)
    *  inner_wall
    */
   /* Rz0 = Rze*cos(theta_ab/2.0) 
    *
    * Rz0: radius at z=0
    * Rze: radius at end plate(zratio=0.0 or 1.0)
    * */
   if (wid<=-1) { // layer before first layer
      return config->inner_wall_radius;
   } else if (wid>=config->layer_size) { // layer after last layer
      return config->outer_wall_radius;
   }
   //printf("z_from_up %lf\n", z_from_up);
   //if (z_from_up<0||z_from_up>config->length[wid]+0.01) {
   //   fprintf(stderr,"ERROR:z_from_up(%lf) should be 0 ~ %lf (@wid=%d)\n",  z_from_up, config->length[wid], wid);
   //   exit(1);
   //}
   if (z_from_up<0) {
      z_from_up = 0;
   }
   if (z_from_up>config->length[wid]) {
      z_from_up = config->length[wid];
   }

   double radius_at_center = config_get_layer_radius_at_center(config, wid);
   double theta_from_z0    = config_get_theta_from_z0(config, wid, z_from_up);
   double radius_at_z = radius_at_center/TMath::Cos(theta_from_z0);
   return radius_at_z;
}
double config_get_layer_radius(struct config* config, int cid, int layer_type, double z_from_up)
{
   int wid = config_get_wid(config, cid, layer_type);
   return config_get_layer_radius(config, wid, z_from_up);
}
//void config_get_sense_and_field_layer_radius(struct config* config, int cid, double z_from_up, double* r_sense, double* r_field)
//{
//   *r_sense = config_get_layer_radius(config, cid, LAYER_TYPE_SENSE, z_from_up);
//   *r_field = config_get_layer_radius(config, cid, LAYER_TYPE_FIELD, z_from_up);
//}

double config_get_cell_width_rad(struct config* config, int wid)
{ 
   /*
    *  2pi/ncells: not z-independent
    */
   if (wid==-1) wid=0; // 2013/120/09: inner_wall (layer==-1) consider as first layeer(ilayer=0)
   //return 2.0*TMath::Pi()/config->cell_size[ilayer]; /* sense <-> sense */
   return config->cell_width[wid];  // Modified for prototype chamber (2014/01/21)
}
double config_get_cell_width_rad(struct config* config, int cid, int layer_type)
{
   int wid = config_get_wid(config, cid, layer_type);
   return config_get_cell_width_rad(config, wid);
}

double config_get_theta_from_z0(struct config* config, int wid, double z_from_up)
{
   /* Sign(theta) = Sign(shift) * Sign(f) */
   double Rz0 = config_get_layer_radius_at_center(config, wid);
   double zratio = z_from_up/config->length[wid]; // Range: [0.0, 1.0]
   double f = zratio - 0.5;
   double drad = config_get_cell_width_rad(config, wid);
   double theta_AB =  drad*config->shift[wid];
   double dLe = Rz0*TMath::Tan(theta_AB/2.0);
   double dLz = 2.0*dLe*f;
   return TMath::ATan(dLz/Rz0);
}
double config_get_theta_from_z0(struct config* config, int cid, int layer_type, double z_from_up)
{
   int wid = config_get_wid(config, cid, layer_type);
   return config_get_theta_from_z0(config, wid, z_from_up);
}

double config_get_wire_theta(struct config* config, int wid, int icell, int wire_type, double z_from_up)
{
   // Comments(2014/02/06)
   // For prototype, icell == -1 works
   // For readl, icell += cell_size, so always positive

   // How to determine theta at given z
   // 1. calc theta at center
   // 2. add theta by config_get_theta_from_center
   double drad = config_get_cell_width_rad(config, wid);
   double theta_AB = drad*config->shift[wid];
   double theta0_at_endplate = config->theta0_at_endplate[wid];
   double theta0_at_center = theta0_at_endplate + theta_AB/2.0;
   double theta0 = theta0_at_center + drad*icell + config_get_theta_from_z0(config, wid, z_from_up);
   if (wire_type==WIRE_TYPE_FIELD) {
      theta0 += drad/2.0;
   }
   return theta0;
}
double config_get_wire_theta(struct config* config, int cid, int layer_type, int icell, int wire_type, double z_from_up)
{
   int wid = config_get_wid(config, cid, layer_type);
   return config_get_wire_theta(config, wid, icell, wire_type, z_from_up);
}
//void config_get_sense_and_field_wire_theta(struct config* config, int cid, int icell, double z_from_up, double* theta_sense, double* theta_field)
//{
//   *theta_sense = config_get_wire_theta(config, cid, LAYER_TYPE_SENSE, z_from_up);
//   double drad = config_get_cell_width_rad(config, cid, layer_type);
//   *theta_field = *theta_sense + drad/2.0;
//}

#if 0
double config_get_cell_width_cm(struct config* config, int ilayer, double z_from_up)
{
   // not implimented
   return 0;
}
double config_get_cell_height_cm(struct config* config, int ilayer, double z_from_up)
{
   /*
    *  outer_wall
    *  ========== sense/guard (last)
    *
    *  ---------- field (ilayer)
    *  ========== sense (ilayer)
    *  ---------- field (ilayer-1)
    *
    *  ========== sense/guard (first)
    *  inner_wall
    *
    *  cell_height of sense (ilayer) is R_distance from field(ilayer) to field(ilayer-1)
    */
   double r_sense1, r_field1;
   double r_sense2, r_field2;
   config_get_sense_and_field_layer_radius(config, ilayer-1, z_from_up, &r_sense1, &r_field1);
   config_get_sense_and_field_layer_radius(config, ilayer+0, z_from_up, &r_sense2, &r_field2);
   return r_field2 - r_field1;
}
double config_get_stereo_angle(struct config* config, int ilayer)
{
#if 0 // Following equation is not correct!!! (2014/01/05)
      // Stereo angle is the angle on the x(y)-z plane, not theta
   /*
    * stereo_angle = 2.0*Rze/L*sin(theta_ab/2.0)
    *              = 2.0*Rz0/L*tan(theta_ab/2.0)
    */
   double drad = config_get_cell_width_rad(config, ilayer);
   if (config->shift[ilayer]<0) drad -= -1.0;
   double Rz0 = config->layer_spacing_at_center;
   double L = config->length;
   return TMath::ATan(2.0*Rz0/L*TMath::Tan(drad/2.0));
#endif
   return 0;
}
#endif
void config_get_wire_pos(struct config* config, int wid, int icell, int wire_type, double dz, char* z_origin, double* wx, double* wy)
{
   //
   // --------------------------------------------
   // layer_type:                 s f s f s f ...
   // ilayer:                     0 0 1 1 2 2 ...
   // --------------------------------------------> R
   // wire_type at z=0 (ihole=3,icell=1): f f s f f f  | theta=drad*3/2.0
   // wire_type at z=0 (ihole=2,icell=1): s f f f s f  | theta=drad
   // wire_type at z=0 (ihole=1,icell=0): f f s f f f  | theta=drad/2.0
   // wire_type at z=0 (ihole=0,icell=0): s f f f s f  | theta=0
   //                                 ^
   //                                 |_ staggered (ilayer is odd)
   //                                    stagger is using field wire's hole for sense wire
   // ***
   // icell can be negative.
   // icell=0,-1,-2,....
   // icell=  ncells-1,ncells-2,...
   //
   // *****
   // ilayer can be -1 or layer_size-1 even if there is no wire
   // because this case is used when drawing cell_shape
   //
   /*
   if (ilayer<0) {
      fprintf(stderr,"ERROR: config_get_wire_pos_internal: there is no wire at ilayer=%d, icell=%d, layer_type=%d, wire_type=%d\n", ilayer, icell, layer_type, wire_type);
      //exit(1);
      return;
   }
   */

   // Add protoype format_type check (as cell_shape is broken 2014/01/21)
//   if (strcmp(config->format_type, "prototype")!=0) {
//      if (icell<0) icell += config->cell_size[wid];
//   }
//   printf("hoge A) icell %d\n", icell);
   if (icell<0) icell += config->cell_size[wid];
//   printf("hoge    wid %d cell_size %d\n", wid, config->cell_size[wid]);
//   printf("hoge B) icell %d\n", icell);

   double z_from_up = dz;
   if (strcmp(z_origin,"center")==0) {
      z_from_up += config->length[wid]/2.0;
   } else if (strcmp(z_origin,"up")==0) {
   } else {
      fprintf(stderr,"z_origin should be center or up (%s)\n",z_origin);
      exit(1);
   }
   double Rz  = config_get_layer_radius(config, wid, z_from_up);
   double rad = config_get_wire_theta(config, wid, icell, wire_type, z_from_up);
//   printf("hoge Rz %lf rad %lf\n", Rz, rad);
   
   *wx = Rz*TMath::Cos(rad);
   *wy = Rz*TMath::Sin(rad);
}
void config_get_wire_pos(struct config* config, int cid, int layer_type, int icell, int wire_type, double dz, char* z_origin, double* wx, double* wy)
{
   int wid = config_get_wid(config, cid, layer_type);
   config_get_wire_pos(config, wid, icell, wire_type, dz, z_origin, wx, wy);
}
//void config_get_sense_wire_pos(struct config* config, int wid, int icell, double* wx, double* wy, double z_from_up) { config_get_wire_pos_internal(config,wid,icell,WIRE_TYPE_SENSE,z_from_up,wx,wy); }
//void config_get_field_wire_pos(struct config* config, int wid, int icell, double* wx, double* wy, double z_from_up) { config_get_wire_pos_internal(config,wid,icell,WIRE_TYPE_SENSE,z_from_up,wx,wy); }
//void config_get_sense_wire_pos_in_sense_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up) { config_get_wire_pos_internal(config,cid,icell,LAYER_TYPE_SENSE,WIRE_TYPE_SENSE,z_from_up,wx,wy); }
//void config_get_field_wire_pos_in_sense_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up) { config_get_wire_pos_internal(config,cid,icell,LAYER_TYPE_SENSE,WIRE_TYPE_FIELD,z_from_up,wx,wy); }
//void config_get_sense_wire_pos_in_field_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up) { config_get_wire_pos_internal(config,cid,icell,LAYER_TYPE_FIELD,WIRE_TYPE_SENSE,z_from_up,wx,wy); }
//void config_get_field_wire_pos_in_field_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up) { config_get_wire_pos_internal(config,cid,icell,LAYER_TYPE_FIELD,WIRE_TYPE_FIELD,z_from_up,wx,wy); }

void config_sense_wire_pos_and_vector(struct config* config, int cid, int icell_z0, double* px, double* py, double* pz, double* vx, double *vy, double* vz)
{
   int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
   /*
    * calculate wire position at upstream end cap and wire's direction
    */
   double x1,y1, z1=0; // upstream
   double x2,y2, z2=config->length[wid]; // downstream
   //printf("config_sense_wire_pos_and_vector wid %d cid %d icell_z1 %d zw %lf\n", wid, cid, icell_z0, z2);

   config_get_wire_pos(config, wid, icell_z0, WIRE_TYPE_SENSE, z1, "up", &x1, &y1);
   config_get_wire_pos(config, wid, icell_z0, WIRE_TYPE_SENSE, z2, "up", &x2, &y2);
   *px = x1;
   *py = y1;
   *pz = z1;
   *vx = x2-x1;
   *vy = y2-y1;
   *vz = z2-z1;
   //printf("shift %d *vx %lf *vy %lf *vz %lf deg %lf\n",shift, *vx, *vy, *vz, rad1/3.14159*180.0);
}


#if 0
void config_draw_hit_on_wire(struct config* config, int ilayer, int icell, double z)
{
   double wx,wy;
   config_get_sense_wire_pos_in_sense_layer(config, ilayer, icell, &wx,&wy,z);
   TMarker* m = new TMarker(wx,wy,5); m->SetMarkerStyle(7); m->SetMarkerColor(3); m->Draw("same");
}
#endif
static double setup_xcen=0;
static double setup_ycen=0;
static double setup_xwid=0;
static double setup_ywid=0;
static double setup_text_size=0;
static double setup_sense_marker_size=0;
static double setup_field_marker_size=0;
static int setup_sense_marker_style=20;
static int setup_field_marker_style=20;
static int setup_sense_marker_color=1;
static int setup_field_marker_color=1;
static double setup_line_width=0;
void config_draw_setup(
      int xcen, int xwid,
      int ycen, int ywid,
      double text_size,
      double line_width,
      double s_size, double s_style, double s_color,
      double f_size, double f_style, double f_color)
{
   setup_xcen = xcen; setup_xwid = xwid;
   setup_ycen = ycen; setup_ywid = ywid;
   setup_text_size = text_size;
   setup_line_width = line_width;
   setup_sense_marker_size = s_size;
   setup_sense_marker_style = s_style;
   setup_sense_marker_color = s_color;
   setup_field_marker_size = f_size;
   setup_field_marker_style = f_style;
   setup_field_marker_color = f_color;
}
void config_draw_setup_file(char* fname)
{
   FILE* fp = fopen(fname,"r");
   char line[1280];
   while(fgets(line,sizeof(line),fp)) {
      if (strstr(line,"xcen")) { sscanf(line, "xcen %lf", &setup_xcen); }
      if (strstr(line,"ycen")) { sscanf(line, "ycen %lf", &setup_ycen); }
      if (strstr(line,"xwid")) { sscanf(line, "xwid %lf", &setup_xwid); }
      if (strstr(line,"ywid")) { sscanf(line, "ywid %lf", &setup_ywid); }
      if (strstr(line,"text_size"))   { sscanf(line, "text_size %lf", &setup_text_size); }
      if (strstr(line,"sense_marker")) { sscanf(line, "sense_marker %lf %d %d", &setup_sense_marker_size, &setup_sense_marker_style, &setup_sense_marker_color); }
      if (strstr(line,"field_marker")) { sscanf(line, "field_marker %lf %d %d", &setup_field_marker_size, &setup_field_marker_style, &setup_field_marker_color); }
      if (strstr(line,"line_width"))  { sscanf(line, "line_width %lf", &setup_line_width); }
   }
   fclose(fp);
}
void config_draw_mchit_conformal(struct config* config, int color, int ilayer, int icell, double rhit)
{
   double line_width=1.0;
   double xpos, ypos;
   double z_from_up = 0.0;
   config_get_wire_pos(config, ilayer, LAYER_TYPE_SENSE, icell, WIRE_TYPE_SENSE, z_from_up, "up", &xpos, &ypos);
   double X = 2*xpos/(xpos*xpos+ypos*ypos);
   double Y = 2*ypos/(xpos*xpos+ypos*ypos);
   printf("X %lf Y %lf\n", X, Y);
   TMarker *m = new TMarker(X, Y, 20);
   m->SetMarkerColor(color);
//   m->SetMarkerStyle(setup_sense_marker_style);
   m->SetMarkerSize(0.2);
   //TEllipse *m = new TEllipse(X, Y, 0.0, 0.0);
   //m->SetFillStyle(0); 
   //m->SetLineColor(color); 
   //m->SetLineWidth(line_width); 
   m->Draw("same only");
}
void config_draw_mchit(struct config* config, int color, int ilayer, int icell, double rhit)
{
   double line_width=1.0;
   double xpos, ypos;
   double z_from_up = 0.0;
   config_get_wire_pos(config, ilayer, LAYER_TYPE_SENSE, icell, WIRE_TYPE_SENSE, z_from_up, "up", &xpos, &ypos);
   TEllipse *m = new TEllipse(xpos, ypos, rhit, rhit);
   m->SetFillStyle(0); 
   m->SetLineColor(color); 
   m->SetLineWidth(line_width); 
   m->Draw("same only");
}
void config_draw_mchits(struct config* config, int color, int nhits, int* ilayer, int* icell, double* rhit)
{
   for (int i=0; i<nhits; i++) {
      config_draw_mchit(config, color, ilayer[i], icell[i], rhit[i]);
   }
}
void config_draw_mchits_from_ROOT(struct config* config, int color, char* root_fname, int iev)
{
   int nhits;
   int ilayer[1000];
   int icell[1000];
   double rhit[1000];
   
   TFile* f = new TFile(root_fname);
   TTree* t = (TTree*)f->Get("t");
   t->SetBranchAddress("nwirehit", &nhits);
   t->SetBranchAddress("ilayer", ilayer);
   t->SetBranchAddress("icell", icell);
   t->SetBranchAddress("dist", rhit);
   t->GetEntry(iev);

   printf("iev %d nhits %d\n", iev, nhits);
   for (int i=0; i<nhits; i++) {
      printf("iev %d ilayer %d icell %d rhit %lf\n", iev, ilayer[i], icell[i], rhit[i]);
      config_draw_mchit(config, color, ilayer[i], icell[i], rhit[i]);
   }
}
void config_draw_mchits_conformal(struct config* config, int color, int nhits, int* ilayer, int* icell, double* rhit)
{
   for (int i=0; i<nhits; i++) {
      config_draw_mchit_conformal(config, color, ilayer[i], icell[i], rhit[i]);
   }
}
TCanvas* config_get_canvas(char* canv_name)
{
   double xmin = setup_xcen - setup_xwid/2.0;
   double xmax = setup_xcen + setup_xwid/2.0;
   double ymin = setup_ycen - setup_ywid/2.0;
   double ymax = setup_ycen + setup_ywid/2.0;
   TCanvas* c1 = new TCanvas(canv_name, canv_name, 0, 0, 500, 500*setup_ywid/setup_xwid);
   c1->DrawFrame(xmin,ymin,xmax,ymax);
   //c1->SetGridY();
   c1->SetGrid();

   TPaveText*pt = new TPaveText(0.20,0.80,0.23,0.85, "brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->AddText(canv_name);
   pt->Draw();



   return c1;
}
void config_draw_walls(struct config* config)
{
   double phi1, phi2;
   if (strcmp(config->format_type, "prototype")==0) {
      phi1 = (90.0-16);
      phi2 = (90.0+16);
   } else {
      phi1 = 0;
      phi2 = 360.0;
   }
   //   printf("phi1 %lf phi2 %lf\n", phi1, phi2);
   TEllipse *l1 = new TEllipse(0.,0.,config->inner_wall_radius, config->inner_wall_radius, phi1, phi2); l1->SetFillStyle(0); l1->SetLineColor(kBlue); l1->SetLineWidth(setup_line_width); l1->Draw("same only");
   TEllipse *l2 = new TEllipse(0.,0.,config->outer_wall_radius, config->outer_wall_radius, phi1, phi2); l2->SetFillStyle(0); l2->SetLineColor(kBlue); l2->SetLineWidth(setup_line_width); l2->Draw("same only");
   // Draw right/left side plate for prototype
   if (strcmp(config->format_type, "prototype")==0) {
      double dradL = (90.0+16.0)/180.0*TMath::Pi();
      double dradR = (90.0-16.0)/180.0*TMath::Pi();
      double lx1 = config->inner_wall_radius*TMath::Cos(dradL);
      double ly1 = config->inner_wall_radius*TMath::Sin(dradL);
      double rx1 = config->inner_wall_radius*TMath::Cos(dradR);
      double ry1 = config->inner_wall_radius*TMath::Sin(dradR);
      double lx2 = config->outer_wall_radius*TMath::Cos(dradL);
      double ly2 = config->outer_wall_radius*TMath::Sin(dradL);
      double rx2 = config->outer_wall_radius*TMath::Cos(dradR);
      double ry2 = config->outer_wall_radius*TMath::Sin(dradR);
      TLine* ll = new TLine(lx1, ly1, lx2, ly2); ll->SetLineColor(kBlue); ll->SetLineWidth(setup_line_width); ll->Draw("same");
      TLine* lr = new TLine(rx1, ry1, rx2, ry2); lr->SetLineColor(kBlue); lr->SetLineWidth(setup_line_width); lr->Draw("same");
   }
}
void config_draw_wires(struct config* config, double dz, char* z_origin, bool draw_cell_shape)
{
   // Drawing:
   // Innerwall/Outerwall

   //double xpos[9];
   //double ypos[9];
   //int wire_id[9];
   //double beta1_deg;
   //double beta2_deg;


   for (int cid=0; cid<config->sense_layer_size; cid++) {
      int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);

      int icell_start = 0;
      int icell_last = config->cell_size[wid];
      for (int icell=icell_start; icell< icell_last; icell++) {

         //config_get_cell_shape(config, cid, icell, z_from_up, xpos, ypos, wire_id, &beta1_deg, &beta2_deg);
         struct cell_shape cell_shape;
         config_get_cell_shape(config, cid, icell, dz, z_origin, &cell_shape);
         bool draw_wire = true;
         config_draw_cell_shape(config, cid, icell, &cell_shape, draw_wire, draw_cell_shape);

#if 0
         //printf("cid %d icell %d xpos %lf ypos %lf\n", cid, icell, xpos, ypos);
         TMarker* m_e = new TMarker(xpos[4],ypos[4],2); m_e->SetMarkerStyle(21); m_e->SetMarkerColor(2); m_e->SetMarkerSize(setup_sense_marker_size); m_e->Draw("same");
         if (wid!=config->layer_size-1) {
            TMarker* m_a = new TMarker(xpos[0],ypos[0],2); m_a->SetMarkerStyle(21); m_a->SetMarkerColor(4); m_a->SetMarkerSize(setup_field_marker_size); m_a->Draw("same");
            TMarker* m_b = new TMarker(xpos[1],ypos[1],2); m_b->SetMarkerStyle(21); m_b->SetMarkerColor(4); m_b->SetMarkerSize(setup_field_marker_size); m_b->Draw("same");
            TMarker* m_c = new TMarker(xpos[2],ypos[2],2); m_c->SetMarkerStyle(21); m_c->SetMarkerColor(4); m_c->SetMarkerSize(setup_field_marker_size); m_c->Draw("same");
         }
         TMarker* m_d = new TMarker(xpos[3],ypos[3],2); m_d->SetMarkerStyle(21); m_d->SetMarkerColor(4); m_d->SetMarkerSize(setup_field_marker_size); m_d->Draw("same");
         TMarker* m_f = new TMarker(xpos[5],ypos[5],2); m_f->SetMarkerStyle(21); m_f->SetMarkerColor(4); m_f->SetMarkerSize(setup_field_marker_size); m_f->Draw("same");
         if (wid!=0) {
            TMarker* m_g = new TMarker(xpos[6],ypos[6],2); m_g->SetMarkerStyle(21); m_g->SetMarkerColor(4); m_g->SetMarkerSize(setup_field_marker_size); m_g->Draw("same");
            TMarker* m_h = new TMarker(xpos[7],ypos[7],2); m_h->SetMarkerStyle(21); m_h->SetMarkerColor(4); m_h->SetMarkerSize(setup_field_marker_size); m_h->Draw("same");
            TMarker* m_i = new TMarker(xpos[8],ypos[8],2); m_i->SetMarkerStyle(21); m_i->SetMarkerColor(4); m_i->SetMarkerSize(setup_field_marker_size); m_i->Draw("same");
         }

#endif
         if (setup_text_size>0) {
//            TText* txt = new TText(xpos[4],ypos[4],Form("%d-%d",cid+1,icell+1)); // start from 1
            TText* txt = new TText(cell_shape.ex, cell_shape.ey, Form("%d-%d",cid+1,icell+1)); // start from 1
            txt->SetTextSize(setup_text_size);
            txt->Draw("same");
         }
      }
   }
}

int config_hit_is_outside(struct config* config, double x, double y, double z_from_center)
{
   // TODO: Better to check with volume name by TGeo instead of coordinate (2014/03/24)
   
   // Return 1 if outside
   //        0 if inside
   double rhit = TMath::Sqrt(x*x+y*y);
   // (1) rmin/rmax
   if (rhit < config->inner_wall_radius || rhit > config->outer_wall_radius) {
//      printf("rhit is outside %lf\n", rhit);
      //      fprintf(stderr,"\t rhit (%lf) inner_wall/outer_wall (%lf, %lf)\n", rhit, config->inner_wall_radius, config->outer_wall_radius);
      return 1;
   }
   /* Check that hit position is inside CDC */
   // REMOVE z hit check (2014/03/24)
   // (2) z 
   //if (TMath::Abs(z_from_center) - config->length[0]/2.0>=0) {
   int wid = config->layer_size - 1;
   //printf("zhit %lf wid %d (config->length[wid]/2.0 = %lf)\n", z_from_center, wid,config->length[wid]/2.0);
   if (TMath::Abs(z_from_center) - config->length[wid]/2.0>=0) {
//      printf("zhit is outside %lf wid %d (config->length[wid]/2.0 = %lf)\n", z_from_center, wid,config->length[wid]/2.0);
      return 1;
   }
   
   // Fix code (2014/03/23) - consider tilt angle of end plate
   //double abs_z = TMath::Abs(z_from_center);
   //double abs_z_end_plate = config->length[0]/2.0;
   //printf("abs_z %lf rhit %lf\n", abs_z, rhit);
   //if (TMath::Tan(10.0/180.0*TMath::Pi())*(abs_z-abs_z_end_plate)+config->layer_radius_at_endplate[0] > 0) {
   //   printf("outside of cdc\n");
   //   return 1;
   //}
#if 0
   double p1_x = TMath::Abs(z_from_center);
   double p1_y = rhit;
   double p2_x = config->length[0];
   double p2_y = config->inner_wall_radius;
   double p3_x = config->length[config->layer_size-1]/2.0;
   double p3_y = config->outer_wall_radius;
   int dir = p1_x * (p2_y - p3_y) + p2_x * (p3_y - p1_y) + p3_x * (p1_y - p2_y);
   fprintf(stderr,"config_hit_is_outside: z_from_center %lf dir %d\n", z_from_center, dir);
   // dir =  1 left
   //       -1 right
   //        0 on the line
   if (dir < 0) {
      fprintf(stderr,"\t z is outside (r, z_from_center) = (%lf, %lf)\n", rhit, z_from_center);
      return 1;
   }
#endif
   return 0; // inside of CDC
}
int config_check_hit_in_cell(struct config* config, double x, double y, double z_from_center, int cid, int icell_to_be_checked)
{
   int iret=0; // 0: inside, -1: right side (smaller icell), +1: left side (larger icell)
   //  This function is only for closed cell, so meaningless for guard layers, so return inside anyway
   if (cid==0 || cid==config->sense_layer_size-1) return 0;

   int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
   double z_from_up = z_from_center + config->length[wid]/2.0;
   double sense_layer_radius = config_get_layer_radius(config, cid, LAYER_TYPE_SENSE, z_from_up);
   double hit_r = TMath::Sqrt(x*x + y*y);
   bool upside = hit_r > sense_layer_radius;

   struct cell_shape cell_shape;
   config_get_cell_shape(config, cid, icell_to_be_checked, z_from_center, "center", &cell_shape);

   //printf("       l1   l2\n");
   //printf("    a-----b-----c\n");
   //printf(" l8 |           | l3\n");
   //printf("    d     e     f\n");
   //printf(" l7 |           | l4\n");
   //printf("    g-----h-----i\n");
   //printf("       l6    l5\n");

   int LR;
   if (upside) {
      int A1 = calc_point_is_anti_clock_wise_side(x, y, cell_shape.ax, cell_shape.ay, cell_shape.dx, cell_shape.dy);
      int A2 = calc_point_is_anti_clock_wise_side(x, y, cell_shape.cx, cell_shape.cy, cell_shape.fx, cell_shape.fy);
      //printf("upside: A1 %d A2 %d\n", A1, A2);
      if (A1 == CALC_ANTI_CLOCK_SIDE) LR = CALC_ANTI_CLOCK_SIDE;
      else if (A2 == CALC_CLOCK_SIDE) LR = CALC_CLOCK_SIDE;
      else LR = CALC_MIDDLE;
   } else {
      int A1 = calc_point_is_anti_clock_wise_side(x, y, cell_shape.dx, cell_shape.dy, cell_shape.gx, cell_shape.gy);
      int A2 = calc_point_is_anti_clock_wise_side(x, y, cell_shape.fx, cell_shape.fy, cell_shape.ix, cell_shape.iy);
      //printf("downside: A1 %d A2 %d\n", A1, A2);
      if (A1 == CALC_ANTI_CLOCK_SIDE) LR = CALC_ANTI_CLOCK_SIDE;
      else if (A2 == CALC_CLOCK_SIDE) LR = CALC_CLOCK_SIDE;
      else LR = CALC_MIDDLE;
   }
   //printf("LR = %d (middle %d anti-clock-side %d clock-side %d)\n", LR, CALC_MIDDLE, CALC_ANTI_CLOCK_SIDE, CALC_CLOCK_SIDE);

   return LR;
}
int config_find_sense_wire_pos(struct config* config, double x, double y, double z_from_center, int* cid_found, int* icell_found, double* wx_found, double* wy_found)
{
   /*
    * Return values
    *
    * 0: found
    * -1: out of chamber
    * -2: inside but not belong to cells in both side...
    *
    */

   if (config_hit_is_outside(config, x, y, z_from_center)==1) {
      return -1;
   }
   double rhit = TMath::Sqrt(x*x+y*y);
   double theta_hit = TMath::ATan2(y, x);// Range: [-pi, pi]
   if (theta_hit<0) theta_hit += 2.0*TMath::Pi();
   //fprintf(stderr,"A) config_get_wire_pos: theta_hit %lf (deg) x %lf y %lf z %lf\n", calc_rad2deg(theta_hit), x, y, z);

   *cid_found = config->sense_layer_size-1; // outmost sense layer

   // (1) From r(x,y) and z, calculate ilayer_out
   double min_r=1e10;
   int wid_found = -1;
   for (int cid=0; cid<config->sense_layer_size; cid++) {
      int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
      double z_from_up = z_from_center + config->length[wid]/2.0;
      double radius = config_get_layer_radius(config, wid, z_from_up);
      double diff_r = TMath::Abs(radius-rhit);
      if (diff_r<min_r) {
         min_r = diff_r;
         *cid_found = cid;
         wid_found = wid;
      } else {
         break;
      }
   }
   if (wid_found==-1) {
      fprintf(stderr,"config_find_sense_wire_pos: cannot determine wid(cid). Something wrong...\n");
      exit(1);
   }
   int shift = config->shift[wid_found];
   // This conversion is ok if config->shift is like integer
   //fprintf(stderr,"(2014/10/15): shift %d (original_is_double config->shift %lf)\n",shift,config->shift[wid_found]);

   // (2) Calculate icell_out
   double z_from_up = z_from_center + config->length[wid_found]/2.0;
   double theta = config_get_wire_theta(config, wid_found, 0, WIRE_TYPE_SENSE, z_from_up);
   double drad = config_get_cell_width_rad(config, wid_found);
   double theta_first_cell = theta - drad/2.0; // offset by half cell

   //*icell_found = (theta_hit - theta_first_cell)/drad; // found bug (2014/03/18)
   double abs_icell =  (theta_hit - theta_first_cell)/drad;
   *icell_found = abs_icell;
#if 1 // comment-out (2014/10/14, long debugging) => remove finaly (2014/10/14), this is not reason..
   // really need??? comment-out (2014/08/28) => really need !!!
   if (abs_icell<0) {
      *icell_found = abs_icell -1;
   }
#endif
//   fprintf(stderr, "exit for duebug\n");
//   exit(1);
   if (config->iev==49) {
      fprintf(stderr,"A) cid_found %d shift %d theta_hit %lf drad %lf drad_theta_first_cell %lf abs_icell %lf icell_found %d\n", *cid_found, shift, theta_hit,drad,theta_first_cell, abs_icell, *icell_found);
   }

   // Add (2014/06/12)  original is calculating theta using sense layer, but cell shape is not square (titled)
   // So it is needed to check from cell_shape.
   int iret = config_check_hit_in_cell(config, x, y, z_from_center, *cid_found, *icell_found);
   int icell_tmp = *icell_found;
   if (iret==CALC_ANTI_CLOCK_SIDE) {
      *icell_found += 1;
   } else if (iret==CALC_CLOCK_SIDE) {
      *icell_found -= 1;
   }
   // Don't shift icell for prototype (as there is no cells in that region...)
   if (strcmp(config->format_type, "prototype")!=0) {
      if ((*icell_found) >= config->cell_size[wid_found]) { // icell=10, cell_size=10
         *icell_found -= config->cell_size[wid_found];
      } else if ((*icell_found)<0) {
         //*icell_found += config->cell_size[wid_found] -1; // icell_found=-1 (last_cell) => icell_found = cell_size - 1
         *icell_found += config->cell_size[wid_found];
      }
   }
   if (config->iev==9) {
   fprintf(stderr,"B) cid_found %d shift %d theta_hit %lf drad %lf drad_theta_first_cell %lf abs_icell %lf icell_found %d\n", *cid_found, shift, theta_hit,drad,theta_first_cell, abs_icell, *icell_found);
   }
   /*
      if ((*icell_out)<0 || (*icell_out)>config->cell_size[*ilayer_out]) {
      fprintf(stderr,"ERROR: config_get_wire_pos: something wrong with icell (%d) (ilayer=%d, cell_size %d)!\n", *icell_out, *ilayer_out, config->cell_size[*ilayer_out]);
      fprintf(stderr,"       input -> (x,y,z) %lf %lf %lf r %lf\n", x, y, z, calc_sqrt2(x,y));
      fprintf(stderr,"       theta_sense %lf theta_field %lf\n", theta_sense, theta_field);
      fprintf(stderr,"       theta_hit %lf theta_first_cell %lf drad %lf\n", theta_hit, theta_first_cell, drad);
      exit(1);
      }
      */

   // Check again new cell to check it is really hits in inside
   iret = config_check_hit_in_cell(config, x, y, z_from_center, *cid_found, *icell_found);
   if (iret!=CALC_MIDDLE) {
      // Mostly for guard layer (since open cell)
      if (config->iev==9) {
         fprintf(stderr,"Warning: config_find_sense_wire_pos: hits does not belong to either cells (x,y,z_fromm_center) = %lf %lf %lf\n", x, y, z_from_center);
      }
      return -2;
   }

   // Add (2014/06/04) check that hit position is with Rmax in the found cell !


   //int int_icell = (theta_hit - theta_first_cell)/drad * cellpos_sign;
   //printf("A) int_icell %d abs_icell %lf\n", int_icell, abs_icell);
   //for (int i=int_icell-1; i<int_icell+1; i++) {
   //   if (abs_icell>i && abs_icell<(i+1)) {
   //      printf("i %d\n", i);
   //      abs_icell = i+1;
   //      break;
   //   }
   //}
   //printf("B) int_icell %d abs_icell %lf\n", int_icell, abs_icell);

   //*icell_found =  abs_icell * cellpos_sign;
   //fprintf(stderr,"A) config_get_wire_pos:\n");

   //printf("hoge theta %lf drad %lf theta_hit %lf theta_first_cell %lf (theta_hit - theta_first_cell) %lf abs_icell %e\n", theta, drad, theta_hit, theta_first_cell, theta_hit-theta_first_cell, abs_icell);
   //printf("hoge cid_found %d icell_found %d (cell_size %d)\n", *cid_found, *icell_found, config->cell_size[wid_found]);


   // (3) Get wire position
   config_get_wire_pos(config, wid_found, *icell_found, WIRE_TYPE_SENSE, z_from_up, "up", wx_found, wy_found);
   //fprintf(stderr,"B) config_get_wire_pos:\n");
   //fprintf(stderr,"*ilayer_out %d *icell_out %d wx_out %lf wy_out %lf z %lf\n", *ilayer_out, *icell_out, *wx_out, *wy_out, z);

   return 0;
}
int config_find_sense_wire_pos_and_dist(struct config* config, double x, double y, double z_from_center, int* cid_out, int* icell_out, double* wx_out, double* wy_out, double* dist)
{
   int ret = config_find_sense_wire_pos(config, x, y, z_from_center, cid_out, icell_out, wx_out, wy_out);
   double dx = x - *wx_out;
   double dy = y - *wy_out;
   *dist = sqrt(dx*dx+dy*dy);
   //   printf("config_find_sense_wire_pos_and_dist: x %lf y %lf dist %lf wx_out %lf wy_out %lf\n", x, y, *dist, *wx_out, *wy_out); // HOGE
   return ret;
}
double config_get_wire_cross_point(struct config* config, int cid1, int icell1, int cid2, int icell2, double *cx, double *cy, double *cz)
{
   /*
    *  icell is the number at z=0 (upstream end plate)
    *
    */

   double px1,py1,pz1;
   double px2,py2,pz2;
   double vx1,vy1,vz1;
   double vx2,vy2,vz2;

   config_sense_wire_pos_and_vector(config, cid1, icell1, &px1, &py1, &pz1, &vx1, &vy1, &vz1);
   config_sense_wire_pos_and_vector(config, cid2, icell2, &px2, &py2, &pz2, &vx2, &vy2, &vz2);

   TVector3 x1(px1, py1, pz1);
   TVector3 x2(px2, py2, pz2);
   TVector3 x12 = x2-x1;

   TVector3 vp_1(vx1, vy1, vz1);
   TVector3 vq_1(vx2, vy2, vz2);
   TVector3 vp = vp_1.Unit();
   TVector3 vq = vq_1.Unit();

   double vpq = vp*vq;
   double x12p = x12*vp;
   double x12q = x12*vq;
   double q = (x12q - x12p*vpq)/(vpq*vpq-1);
   double p = x12p + q*vpq;

   TVector3 xp = x1+p*vp;
   TVector3 xq = x2+q*vq;

   *cx = (xp.X() + xq.X())/2.0;
   *cy = (xp.Y() + xq.Y())/2.0;
   *cz = (xp.Z() + xq.Z())/2.0;

   return (xp-xq).Mag(); // distance between xp and xq
}
#if 1
void config_set_cell_shape(
      struct cell_shape* cell_shape,
      double ax,double ay,double bx,double by,double cx,double cy,
      double dx,double dy,double ex,double ey,double fx,double fy,
      double gx,double gy,double hx,double hy,double ix,double iy) 
{
   // f_wire  s_wire  f_wire
   // icell+0 icell+0 icell-1    Prototype                 Real
   //    a       b       c    : ilayer+0 (field layer)   ilayer+1 (field layer)
   //    d       e       f    : ilayer+0 (sense layer)   ilayer+0 (sense layer)
   //    g       h       i    : ilayer-1 (field layer)   ilayer+0 (field layer)
   //
   cell_shape->ax = ax; cell_shape->ay = ay;
   cell_shape->bx = bx; cell_shape->by = by;
   cell_shape->cx = cx; cell_shape->cy = cy;
   cell_shape->dx = dx; cell_shape->dy = dy;
   cell_shape->ex = ex; cell_shape->ey = ey;
   cell_shape->fx = fx; cell_shape->fy = fy;
   cell_shape->gx = gx; cell_shape->gy = gy;
   cell_shape->hx = hx; cell_shape->hy = hy;
   cell_shape->ix = ix; cell_shape->iy = iy;

   cell_shape->beta1 = calc_angle_between_two_lines(fx-ix,fy-iy,hx-ix,hy-iy);
   cell_shape->beta2 = calc_angle_between_two_lines(bx-ax,by-ay,dx-ax,dy-ay);
   //printf("beta1 %lf beta2 %lf\n", cell_shape->beta1/TMath::Pi()*180.0, cell_shape->beta2/TMath::Pi()*180.0);
}
void config_find_closest_sense_or_field_wire_in_field_layer(struct config* config, double x, double y, double dz, char* z_origin, int cid, int icell_start, int wire_type, int* icell_out, double* dist_out)
{
   double min_dist=1e10;
   int min_icell=1000;
   double dist;
   double xw, yw;
   int shift;
   int wid = config_get_wid(config, cid, LAYER_TYPE_FIELD);
   //   printf("hoge cid %d wid %d\n", cid, wid);
   if (wid==-1) { // inner_wall position
      shift = TMath::Abs(config->shift[0]); // use same shift at innermost layer
   } else if (wid==config->layer_size) { // outer_wall position
      shift = TMath::Abs(config->shift[config->layer_size -1]); // use same shift at outermost layer
   } else {
      shift = TMath::Abs(config->shift[wid]);
   }
   //fprintf(stderr,"config_find_closest_sense_or_field_wire_in_field_layer: ilayer_field %d icell_start %d shfit %d\n", ilayer_field, icell_start, shift);
   //fprintf(stderr,"   icell_start - 3:shift %d icell_start + 3*shift %d\n", icell_start-3*shift, icell_start+3*shift);
   for (int icell=icell_start - 3*shift - 6; icell<icell_start + 3*shift + 6; icell++) {
      config_get_wire_pos(config, wid, icell, wire_type, dz, z_origin, &xw, &yw);
      dist = calc_sqrt2(xw-x, yw-y);
      //printf("hoge icell_start %d icell %d -> (xw %lf x %lf ) (yw %lf y %lf) dist %lf\n", icell_start, icell, xw, x, yw, y, dist);
      if (dist < min_dist) {
         min_dist = dist;
         min_icell = icell;
      }
      // Comment-out (2014/01/21)
      //      if (dist>min_dist) {
      //         break;
      //      }
   }
   *icell_out = min_icell;
   *dist_out = min_dist;
   //   printf("hoge wid %d cid %d icell_start %d min_icell %d min_dist %lf (xw, yw) = (%lf, %lf) (x, y) = (%lf, %lf) @z %lf\n", wid, cid, icell_start, min_icell, min_dist, xw, yw, x, y, z);
}
void config_find_closest_three_field_wires_in_field_layer(struct config* config, double x, double y, double dz, char* z_origin, int cid, int icell_start,
      double* x3, double* y3,
      double* x2, double* y2,
      double* x1, double* y1)
{
   //            f       s(x,y)     f   : sense_layer (ilayer_field+1) 
   // theta <--- x3 <---  x2 <---- x1   : field_layer (ilayer_field) <= different stereo angle from one at next sense_layer
   int icell_sense;
   int icell_field;
   double dist_sense;
   double dist_field;
   config_find_closest_sense_or_field_wire_in_field_layer(config, x, y, dz, z_origin, cid, icell_start, WIRE_TYPE_SENSE, &icell_sense, &dist_sense);
   config_find_closest_sense_or_field_wire_in_field_layer(config, x, y, dz, z_origin, cid, icell_start, WIRE_TYPE_FIELD, &icell_field, &dist_field);
   //if (icell_sense==1000 || icell_field==1000) {
   //   *x1 = 1e10;
   //   *x2 = 1e10;
   //   *x3 = 1e10;
   //   *y1 = 1e10;
   //   *y2 = 1e10;
   //   *y3 = 1e10;
   //   return;
   //}
   //   printf("hoge icell_sense %d dist_sense %lf\n", icell_sense, dist_sense);
   //   printf("hoge icell_field %d dist_field %lf\n", icell_field, dist_field);
   if (dist_field < dist_sense) {
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell_field+1, WIRE_TYPE_SENSE, dz, z_origin, x3, y3);
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell_field,   WIRE_TYPE_FIELD, dz, z_origin, x2, y2);
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell_field,   WIRE_TYPE_SENSE, dz, z_origin, x1, y1);
   } else {
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell_sense,   WIRE_TYPE_FIELD, dz, z_origin, x3, y3);
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell_sense,   WIRE_TYPE_SENSE, dz, z_origin, x2, y2);
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell_sense-1, WIRE_TYPE_FIELD, dz, z_origin, x1, y1);
   }
}
void config_get_cell_shape(struct config* config, int cid, int icell, double dz, char* z_origin, struct cell_shape* cell_shape)
{
   // f_wire  s_wire  f_wire
   // icell+0 icell+0 icell-1    Prototype                 Real
   //    a       b       c    : ilayer+0 (field layer)   ilayer+1 (field layer)
   //    d       e       f    : ilayer+0 (sense layer)   ilayer+0 (sense layer)
   //    g       h       i    : ilayer-1 (field layer)   ilayer+0 (field layer)
   //
   double ax,bx,cx,dx,ex,fx,gx,hx,ix;
   double ay,by,cy,dy,ey,fy,gy,hy,iy;
   if (strcmp(config->format_type,"prototype")==0) {
      config_get_wire_pos(config, cid, LAYER_TYPE_SENSE, icell,   WIRE_TYPE_SENSE, dz, z_origin, &ex, &ey); // e
      config_get_wire_pos(config, cid, LAYER_TYPE_SENSE, icell,   WIRE_TYPE_FIELD, dz, z_origin, &dx, &dy); // d
      config_get_wire_pos(config, cid, LAYER_TYPE_SENSE, icell-1, WIRE_TYPE_FIELD, dz, z_origin, &fx, &fy); // f
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell,   WIRE_TYPE_FIELD, dz, z_origin, &ax, &ay); // a
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell,   WIRE_TYPE_SENSE, dz, z_origin, &bx, &by); // b
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell-1, WIRE_TYPE_FIELD, dz, z_origin, &cx, &cy); // c
      config_find_closest_three_field_wires_in_field_layer(config, ex, ey, dz, z_origin, cid-1, icell, &gx, &gy, &hx, &hy, &ix, &iy); // g,h,i
   } else {

      config_get_wire_pos(config, cid, LAYER_TYPE_SENSE, icell,   WIRE_TYPE_FIELD, dz, z_origin, &dx, &dy); // d
      config_get_wire_pos(config, cid, LAYER_TYPE_SENSE, icell,   WIRE_TYPE_SENSE, dz, z_origin, &ex, &ey); // e
      config_get_wire_pos(config, cid, LAYER_TYPE_SENSE, icell-1, WIRE_TYPE_FIELD, dz, z_origin, &fx, &fy); // f

      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell,   WIRE_TYPE_FIELD, dz, z_origin, &gx, &gy); // g
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell,   WIRE_TYPE_SENSE, dz, z_origin, &hx, &hy); // h
      config_get_wire_pos(config, cid, LAYER_TYPE_FIELD, icell-1, WIRE_TYPE_FIELD, dz, z_origin, &ix, &iy); // i
      //printf("hoge cid %d icell %d z %lf\n", cid, icell, z);

      //printf("HOGE: cid %d gx %lf gy %lf\n", cid, gx, gy);
      config_find_closest_three_field_wires_in_field_layer(config, ex, ey, dz, z_origin, cid+1, icell, &ax, &ay, &bx, &by, &cx, &cy); // a,b,c
   }


   config_set_cell_shape(cell_shape,
         ax,ay,bx,by,cx,cy,
         dx,dy,ex,ey,fx,fy,
         gx,gy,hx,hy,ix,iy);
   //if (cid==0 && icell==0) {
   //   config_print_cell_shape(cell_shape);
   //}
}
void config_get_cell_shape(struct config* config, int cid, int icell, double dz, char* z_origin, double* xpos, double* ypos, int* wire_id, double* beta1_deg, double* beta2_deg)
{
   struct cell_shape cell_shape;
   config_get_cell_shape(config, cid, icell, dz, z_origin, &cell_shape);

   *beta1_deg = calc_rad2deg(cell_shape.beta1);
   *beta2_deg = calc_rad2deg(cell_shape.beta2);

   xpos[0] = cell_shape.ax;
   xpos[1] = cell_shape.bx;
   xpos[2] = cell_shape.cx;
   xpos[3] = cell_shape.dx;
   xpos[4] = cell_shape.ex;
   xpos[5] = cell_shape.fx;
   xpos[6] = cell_shape.gx;
   xpos[7] = cell_shape.hx;
   xpos[8] = cell_shape.ix;
   ypos[0] = cell_shape.ay;
   ypos[1] = cell_shape.by;
   ypos[2] = cell_shape.cy;
   ypos[3] = cell_shape.dy;
   ypos[4] = cell_shape.ey;
   ypos[5] = cell_shape.fy;
   ypos[6] = cell_shape.gy;
   ypos[7] = cell_shape.hy;
   ypos[8] = cell_shape.iy;

   wire_id[0] = 1;
   wire_id[1] = 2;
   wire_id[2] = 3;
   wire_id[3] = 4;
   wire_id[4] = 0; 
   wire_id[5] = 5;
   wire_id[6] = 6;
   wire_id[7] = 7;
   wire_id[8] = 8;
   if (cid==0) { 
      *beta1_deg = -1;
      wire_id[4] = 0;
      wire_id[6] = -1; // inner-wall
      wire_id[7] = -1; // inner-wall
      wire_id[8] = -1; // inner-wall
   }
   if (cid==config->sense_layer_size-1) {
      *beta2_deg = -1;
      wire_id[4] = 0;
      wire_id[0] = -1; // outer-wall
      wire_id[1] = -1; // outer-wall
      wire_id[2] = -1; // outer-wall
   }
}
//   config_draw_cell_shape(&config, cid, icell, &cell_shape, true, true);
void config_draw_cell_shape(struct config* config, int cid, int icell, struct cell_shape* cell_shape, bool draw_wire, bool draw_cell_shape, int line_color, double line_width)
{
   // Assumed that wires are alrady drawn.
   //
   //       l1   l2
   //    a-----b-----c
   // l8 |           | l3
   //    d     e     f
   // l7 |           | l4
   //    g-----h-----i
   //       l6    l5
   //
   //

   if (setup_line_width==0) {
      fprintf(stderr,"ERROR: call read_draw_setup_file first!!\n");
      exit(1);
   }
   double offx=0;
   double offy=0;
   double my_line_width;
   if (line_width<0) {
      my_line_width = setup_line_width;
   } else {
      my_line_width = line_width;
   }
   //printf("line_with %lf setup_line_width %lf my_line_width %lf\n", line_width, setup_line_width, my_line_width);

   if (draw_cell_shape) {
      int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
      if (strcmp(config->format_type,"prototype")==0 && ( icell==0 || icell == config->cell_size[wid] -1)) goto out;
      if (cid!=0 && cid != config->sense_layer_size-1) {
         TLine* l1 = new TLine(cell_shape->ax-offx, cell_shape->ay-offy, cell_shape->bx-offx, cell_shape->by-offy); /*l1->SetLineStyle();*/ l1->SetLineColor(line_color); l1->SetLineWidth(my_line_width); l1->Draw();
         TLine* l2 = new TLine(cell_shape->bx-offx, cell_shape->by-offy, cell_shape->cx-offx, cell_shape->cy-offy); /*l2->SetLineStyle();*/ l2->SetLineColor(line_color); l2->SetLineWidth(my_line_width); l2->Draw();
         TLine* l3 = new TLine(cell_shape->cx-offx, cell_shape->cy-offy, cell_shape->fx-offx, cell_shape->fy-offy); /*l3->SetLineStyle();*/ l3->SetLineColor(line_color); l3->SetLineWidth(my_line_width); l3->Draw();
         TLine* l4 = new TLine(cell_shape->fx-offx, cell_shape->fy-offy, cell_shape->ix-offx, cell_shape->iy-offy); /*l4->SetLineStyle();*/ l4->SetLineColor(line_color); l4->SetLineWidth(my_line_width); l4->Draw();
         TLine* l5 = new TLine(cell_shape->ix-offx, cell_shape->iy-offy, cell_shape->hx-offx, cell_shape->hy-offy); /*l5->SetLineStyle();*/ l5->SetLineColor(line_color); l5->SetLineWidth(my_line_width); l5->Draw();
         TLine* l6 = new TLine(cell_shape->hx-offx, cell_shape->hy-offy, cell_shape->gx-offx, cell_shape->gy-offy); /*l6->SetLineStyle();*/ l6->SetLineColor(line_color); l6->SetLineWidth(my_line_width); l6->Draw();
         TLine* l7 = new TLine(cell_shape->gx-offx, cell_shape->gy-offy, cell_shape->dx-offx, cell_shape->dy-offy); /*l7->SetLineStyle();*/ l7->SetLineColor(line_color); l7->SetLineWidth(my_line_width); l7->Draw();
         TLine* l8 = new TLine(cell_shape->dx-offx, cell_shape->dy-offy, cell_shape->ax-offx, cell_shape->ay-offy); /*l8->SetLineStyle();*/ l8->SetLineColor(line_color); l8->SetLineWidth(my_line_width); l8->Draw();
      }
   }
out:

   if (draw_wire) {
      if (cid != config->sense_layer_size-1) {
         TMarker* ma = new TMarker(cell_shape->ax-offx, cell_shape->ay-offy, setup_field_marker_style); ma->SetMarkerSize(setup_field_marker_size); ma->SetMarkerColor(setup_field_marker_color); ma->Draw();
         TMarker* mb = new TMarker(cell_shape->bx-offx, cell_shape->by-offy, setup_field_marker_style); mb->SetMarkerSize(setup_field_marker_size); mb->SetMarkerColor(setup_field_marker_color); mb->Draw();
         TMarker* mc = new TMarker(cell_shape->cx-offx, cell_shape->cy-offy, setup_field_marker_style); mc->SetMarkerSize(setup_field_marker_size); mc->SetMarkerColor(setup_field_marker_color); mc->Draw();
      }
      TMarker* md = new TMarker(cell_shape->dx-offx, cell_shape->dy-offy, setup_field_marker_style); md->SetMarkerSize(setup_field_marker_size); md->SetMarkerColor(setup_field_marker_color); md->Draw();
      TMarker* me = new TMarker(cell_shape->ex-offx, cell_shape->ey-offy, setup_sense_marker_style); me->SetMarkerSize(setup_sense_marker_size); me->SetMarkerColor(setup_sense_marker_color); me->Draw();
      TMarker* mf = new TMarker(cell_shape->fx-offx, cell_shape->fy-offy, setup_field_marker_style); mf->SetMarkerSize(setup_field_marker_size); mf->SetMarkerColor(setup_field_marker_color); mf->Draw();
      if (cid != 0) {
         TMarker* mg = new TMarker(cell_shape->gx-offx, cell_shape->gy-offy, setup_field_marker_style); mg->SetMarkerSize(setup_field_marker_size); mg->SetMarkerColor(setup_field_marker_color); mg->Draw();
         TMarker* mh = new TMarker(cell_shape->hx-offx, cell_shape->hy-offy, setup_field_marker_style); mh->SetMarkerSize(setup_field_marker_size); mh->SetMarkerColor(setup_field_marker_color); mh->Draw();
         TMarker* mi = new TMarker(cell_shape->ix-offx, cell_shape->iy-offy, setup_field_marker_style); mi->SetMarkerSize(setup_field_marker_size); mi->SetMarkerColor(setup_field_marker_color); mi->Draw();
      }
   }

   if (setup_text_size>0) {
      TText* txt = new TText(cell_shape->ex, cell_shape->ey, Form("%d-%d",cid+1,icell+1)); // start from 1
      txt->SetTextSize(setup_text_size);
      txt->Draw("same");
   }
}
void config_print_cell_shape(struct cell_shape* cell_shape)
{
   printf("\n");
   printf("       l1   l2\n");
   printf("    a-----b-----c\n");
   printf(" l8 |           | l3\n");
   printf("    d     e     f\n");
   printf(" l7 |           | l4\n");
   printf("    g-----h-----i\n");
   printf("       l6    l5\n");
   printf("\n");
   printf("\n");
   printf("a: %lf,%lf\n", cell_shape->ax, cell_shape->ay);
   printf("b: %lf,%lf\n", cell_shape->bx, cell_shape->by);
   printf("c: %lf,%lf\n", cell_shape->cx, cell_shape->cy);
   printf("d: %lf,%lf\n", cell_shape->dx, cell_shape->dy);
   printf("e: %lf,%lf\n", cell_shape->ex, cell_shape->ey);
   printf("f: %lf,%lf\n", cell_shape->fx, cell_shape->fy);
   printf("g: %lf,%lf\n", cell_shape->gx, cell_shape->gy);
   printf("h: %lf,%lf\n", cell_shape->hx, cell_shape->hy);
   printf("i: %lf,%lf\n", cell_shape->ix, cell_shape->iy);
   printf("beta1: %lf (deg)\n", calc_rad2deg(cell_shape->beta1));
   printf("beta2: %lf (deg)\n", calc_rad2deg(cell_shape->beta2));
}
void config_print_cell_shape_oneline(char* prefix, struct cell_shape* cell_shape)
{
   printf("%s ", prefix);
   printf("( %lf , %lf ) ", cell_shape->ax, cell_shape->ay);
   printf("( %lf , %lf ) ", cell_shape->bx, cell_shape->by);
   printf("( %lf , %lf ) ", cell_shape->cx, cell_shape->cy);
   printf("( %lf , %lf ) ", cell_shape->dx, cell_shape->dy);
   printf("( %lf , %lf ) ", cell_shape->ex, cell_shape->ey);
   printf("( %lf , %lf ) ", cell_shape->fx, cell_shape->fy);
   printf("( %lf , %lf ) ", cell_shape->gx, cell_shape->gy);
   printf("( %lf , %lf ) ", cell_shape->hx, cell_shape->hy);
   printf("( %lf , %lf ) ", cell_shape->ix, cell_shape->iy);
   printf("beta1: %lf (deg) ", calc_rad2deg(cell_shape->beta1));
   printf("beta2: %lf (deg)\n", calc_rad2deg(cell_shape->beta2));
}
void config_get_pos_in_cell(struct config* config, int cid, int icell, double x, double y, double z_from_center, double* lx, double* ly, double* lr, 
      double* atan2,
      double* beta,
      int* iatan2,  //  [0, 17] <= ltheta/10, 10 deg binning
      int* ibeta,  //  [0, 6] <= (beta1-60)/10, 10 deg binning
      char* UD)  // 'U': up side cell, 'D': down side cell
{
   if (cid==0 || cid==config->sense_layer_size-1) {
      return;
   }
   if (strcmp(config->format_type,"prototype")==0) {
      if (icell==0 || icell==1) {
         return;
      }
   }

   double local_x, local_y;
   struct cell_shape cell1;
   struct cell_shape cell2;
   config_get_cell_shape(config, cid, icell, z_from_center, "center", &cell1);
   config_transform_cell_shape(&cell1, &cell2);
   config_transform_xypos(&cell1, x, y, &local_x, &local_y);
   //fprintf(stderr,"x %lf y %lf\n", x, y);
   //fprintf(stderr,"local_x %lf local_y %lf\n", local_x, local_y);
   double ltheta = TMath::ATan2(local_y, local_x);
   *atan2 = ltheta;

   *UD ='U';
   if (ltheta<0) *UD = 'D';

   if (*UD=='U') {
      *beta = cell1.beta2;
   } else {
      *beta = cell1.beta1;
   }

   *lx = local_x;
   *ly = local_y;
   *lr = TMath::Sqrt(local_x*local_x + local_y*local_y);
   *iatan2 = TMath::Abs(ltheta)/TMath::Pi()*180.0/10.0;

   *ibeta = ((*beta)/TMath::Pi()*180.0 - 60.0)/10.0;
   if (*ibeta<0 || *ibeta>6) {
      //if (strcmp(config->format_type, "prototype")==0) {
      fprintf(stderr,"ERROR: config_get_pos_in_cell: bad beta1. something wrong with cell shape. Closed cell?\n");
      fprintf(stderr,"cid %d icell %d z_from_center %lf cell2.beta1 %lf cell2.beta2 %lf\n", cid, icell,z_from_center, 
            cell2.beta1/TMath::Pi()*180, cell2.beta2/TMath::Pi()*180);
      config_print_cell_shape(&cell1);
      exit(1);
      //}
   }
   if (strcmp(config->format_type,"prototype")==0) {
      if (*UD=='U') *ibeta = 0;
   } else {
      if (*UD=='D') *ibeta = 0;
   }

   if (*ibeta<0 || *ibeta>=6) { 
      fprintf(stderr,"ERROR: ibeta %d --> must not happen (ibeta should be from 0 to 5)\n", *ibeta);
      exit(1);
   }
   if (*iatan2<0 || *iatan2>=18) { 
      fprintf(stderr,"ERROR: iatan2 %d --> must not happen (iatan2 should be from 0 to 17)\n", *iatan2);
      exit(1);
   }

}

void config_find_cell_bondary(struct config* config, int cid, int icell, double dz, char* z_origin, double rad, bool in_local_coord, double* xbound, double* ybound, double* rbound)
{
   //
   //Asuumption: rad is from 0 to 360
   //
   if (rad < 0) {
      rad += TMath::Pi()*2.0;
      //fprintf(stderr,"config_find_cell_boundary: ERROR: input 'rad' should be from 0 to 180 deg (input is %lf)\n", rad/TMath::Pi()*180);
      //exit(1);
   }
   struct cell_shape cell_shape_org;
   struct cell_shape cell_shape; // transformed cell
   config_get_cell_shape(config, cid, icell, dz, z_origin, &cell_shape_org);
   //config_print_cell_shape(&cell_shape_org); // HOGE
   config_transform_cell_shape(&cell_shape_org, &cell_shape);
   config_print_cell_shape(&cell_shape);
   printf("config_: rad %lf\n", rad/TMath::Pi()*180);

   //       l1   l2
   //    a-----b-----c
   // l8 |           | l3
   //    d     e     f
   // l7 |           | l4
   //    g-----h-----i
   //       l6    l5
   //
   //
   //  Note that: d and f might be below horizon
   //
   double rad_a = calc_drad(cell_shape.ax, cell_shape.ay);
   double rad_b = calc_drad(cell_shape.bx, cell_shape.by);
   double rad_c = calc_drad(cell_shape.cx, cell_shape.cy);
   double rad_d = calc_drad(cell_shape.dx, cell_shape.dy);
   double rad_f = calc_drad(cell_shape.fx, cell_shape.fy);
   double rad_g = calc_drad(cell_shape.gx, cell_shape.gy);
   double rad_h = calc_drad(cell_shape.hx, cell_shape.hy);
   double rad_i = calc_drad(cell_shape.ix, cell_shape.iy);

   bool debug=false;

   double xcrs, ycrs;
   if      (rad_f<0.05/*3deg*/ && rad > rad_f && rad <= rad_c) { calc_get_cross_point_with_line(cell_shape.fx, cell_shape.fy, cell_shape.cx, cell_shape.cy, rad, &xcrs, &ycrs); if (debug) printf("L3\n"); }
   else if (rad_f>0.05/*3deg*/ && rad <= rad_c) { calc_get_cross_point_with_line(cell_shape.fx, cell_shape.fy, cell_shape.cx, cell_shape.cy, rad, &xcrs, &ycrs); if (debug) printf("L3\n"); }
   else if (rad > rad_c && rad <= rad_b) { calc_get_cross_point_with_line(cell_shape.cx, cell_shape.cy, cell_shape.bx, cell_shape.by, rad, &xcrs, &ycrs); if (debug) printf("L2\n"); }
   else if (rad > rad_b && rad <= rad_a) { calc_get_cross_point_with_line(cell_shape.bx, cell_shape.by, cell_shape.ax, cell_shape.ay, rad, &xcrs, &ycrs); if (debug) printf("L1\n"); }
   else if (rad > rad_a && rad <= rad_d) { calc_get_cross_point_with_line(cell_shape.ax, cell_shape.ay, cell_shape.dx, cell_shape.dy, rad, &xcrs, &ycrs); if (debug) printf("L8\n"); }
   else if (rad > rad_d && rad <= rad_g) { calc_get_cross_point_with_line(cell_shape.dx, cell_shape.dy, cell_shape.gx, cell_shape.gy, rad, &xcrs, &ycrs); if (debug) printf("L7\n"); }
   else if (rad > rad_g && rad <= rad_h) { calc_get_cross_point_with_line(cell_shape.gx, cell_shape.gy, cell_shape.hx, cell_shape.hy, rad, &xcrs, &ycrs); if (debug) printf("L6\n"); }
   else if (rad > rad_h && rad <= rad_i) { calc_get_cross_point_with_line(cell_shape.hx, cell_shape.hy, cell_shape.ix, cell_shape.iy, rad, &xcrs, &ycrs); if (debug) printf("L5\n"); }
   else if (rad > rad_i && rad <= rad_f) { calc_get_cross_point_with_line(cell_shape.ix, cell_shape.iy, cell_shape.fx, cell_shape.fy, rad, &xcrs, &ycrs); if (debug) printf("L4\n"); }
   else {
      fprintf(stderr,"ERROR: config_find_cell_bondary: must not happen !!\n");
      fprintf(stderr,"cid %d icell %d dz %lf z_origin %s\n", cid, icell, dz, z_origin);
      fprintf(stderr,"rad   %lf (deg) %lf (rad)\n", rad  /TMath::Pi()*180.0, rad);
      fprintf(stderr,"rad_a %lf (deg)\n", rad_a/TMath::Pi()*180.0);
      fprintf(stderr,"rad_b %lf (deg)\n", rad_b/TMath::Pi()*180.0);
      fprintf(stderr,"rad_c %lf (deg)\n", rad_c/TMath::Pi()*180.0);
      fprintf(stderr,"rad_d %lf (deg)\n", rad_d/TMath::Pi()*180.0);
      fprintf(stderr,"rad_f %lf (deg)\n", rad_f/TMath::Pi()*180.0);
      fprintf(stderr,"rad_g %lf (deg)\n", rad_g/TMath::Pi()*180.0);
      fprintf(stderr,"rad_h %lf (deg)\n", rad_h/TMath::Pi()*180.0);
      fprintf(stderr,"rad_i %lf (deg)\n", rad_i/TMath::Pi()*180.0);
      fprintf(stderr,"beta1 %lf (deg)\n", cell_shape.beta1/TMath::Pi()*180.0);
      fprintf(stderr,"beta2 %lf (deg)\n", cell_shape.beta2/TMath::Pi()*180.0);
      exit(1);
   }
   if (debug) {
      fprintf(stderr,"cid %d icell %d dz %lf z_origin %s\n", cid, icell, dz, z_origin);
      fprintf(stderr,"rad   %lf (deg) %lf (rad)\n", rad  /TMath::Pi()*180.0, rad);
      fprintf(stderr,"rad_a %lf (deg)\n", rad_a/TMath::Pi()*180.0);
      fprintf(stderr,"rad_b %lf (deg)\n", rad_b/TMath::Pi()*180.0);
      fprintf(stderr,"rad_c %lf (deg)\n", rad_c/TMath::Pi()*180.0);
      fprintf(stderr,"rad_d %lf (deg)\n", rad_d/TMath::Pi()*180.0);
      fprintf(stderr,"rad_f %lf (deg)\n", rad_f/TMath::Pi()*180.0);
      fprintf(stderr,"rad_g %lf (deg)\n", rad_g/TMath::Pi()*180.0);
      fprintf(stderr,"rad_h %lf (deg)\n", rad_h/TMath::Pi()*180.0);
      fprintf(stderr,"rad_i %lf (deg)\n", rad_i/TMath::Pi()*180.0);
      fprintf(stderr,"beta1 %lf (deg)\n", cell_shape.beta1/TMath::Pi()*180.0);
      fprintf(stderr,"beta2 %lf (deg)\n", cell_shape.beta2/TMath::Pi()*180.0);
   }

   *xbound = xcrs;
   *ybound = ycrs;
   *rbound = TMath::Sqrt(xcrs*xcrs + ycrs*ycrs);
   printf("xbound %lf ybound %lf rbound %lf\n", *xbound, *ybound, *rbound);
   if (!in_local_coord) {
      // transform back to original coordinate
      double new_x, new_y;
      config_transform_xypos(&cell_shape_org, xcrs, ycrs, &new_x, &new_y);
      *xbound = new_x + cell_shape_org.ex;
      *ybound = new_y + cell_shape_org.ey;
   }
}
void config_transform_xypos(struct cell_shape* cell_shape, double org_x, double org_y, double* new_x, double* new_y)
{
   // new_x, new_y is in local coordinate
   double x0 = cell_shape->ex;
   double y0 = cell_shape->ey;
   //   double rad = TMath::ATan2(y0, x0); <== bug (2014/06/22)
   double rad = TMath::Pi()/2.0 - TMath::ATan2(y0, x0);
   //   printf("configtransform_xypos x0 %lf y0 %lf rad %lf\n", x0, y0, rad/TMath::Pi()*180);
   double mycos = TMath::Cos(rad);
   double mysin = TMath::Sin(rad);
   double x2 = (org_x - x0)*mycos - (org_y - y0)*mysin;
   double y2 = (org_x - x0)*mysin + (org_y - y0)*mycos;
   *new_x = x2;
   *new_y = y2;
   //   printf("configtransform_xypos org_x %lf orgy %lf rad %lf ---> new_x %lf new_y %lf rad %lf\n", org_x, org_y, TMath::ATan2(org_y, org_x)/TMath::Pi()*180, x2, y2, TMath::ATan2(y2, x2)/TMath::Pi()*180);
}

void config_transform_cell_shape(struct cell_shape* src, struct cell_shape* dst)
{
   // sense wire position
   double x0 = src->ex;
   double y0 = src->ey;
   double rad = TMath::Pi()/2.0 - TMath::ATan2(y0, x0); // 90 - wpos
   //   printf("config_transform_cell_shape: x0 %lf y0 %lf rad %lf\n", x0, y0, rad/TMath::Pi()*180); // HOGE

   config_rotate_cell(src, x0, y0, rad, dst);
}
void config_copy_cell_shape(struct cell_shape* src, struct cell_shape* dst)
{
   dst->beta1 = src->beta1;
   dst->beta2 = src->beta2;
   dst->width = src->width;
   dst->height = src->height;
   dst->ax = src->ax; dst->ay = src->ay;
   dst->bx = src->bx; dst->by = src->by;
   dst->cx = src->cx; dst->cy = src->cy;
   dst->ex = src->ex; dst->ey = src->ey;
   dst->dx = src->dx; dst->dy = src->dy;
   dst->ex = src->ex; dst->ey = src->ey;
   dst->fx = src->fx; dst->fy = src->fy;
   dst->gx = src->gx; dst->gy = src->gy;
   dst->hx = src->hx; dst->hy = src->hy;
   dst->ix = src->ix; dst->iy = src->iy;
}

void config_rotate_cell(struct cell_shape* src, double x0, double y0, double rad, struct cell_shape* dst)
{
   // Rotate around sense wire
   calc_rotate_and_move_origin(x0, y0, rad, src->ax, src->ay, &dst->ax, &dst->ay);
   calc_rotate_and_move_origin(x0, y0, rad, src->bx, src->by, &dst->bx, &dst->by);
   calc_rotate_and_move_origin(x0, y0, rad, src->cx, src->cy, &dst->cx, &dst->cy);
   calc_rotate_and_move_origin(x0, y0, rad, src->dx, src->dy, &dst->dx, &dst->dy);
   calc_rotate_and_move_origin(x0, y0, rad, src->ex, src->ey, &dst->ex, &dst->ey);
   calc_rotate_and_move_origin(x0, y0, rad, src->fx, src->fy, &dst->fx, &dst->fy);
   calc_rotate_and_move_origin(x0, y0, rad, src->gx, src->gy, &dst->gx, &dst->gy);
   calc_rotate_and_move_origin(x0, y0, rad, src->hx, src->hy, &dst->hx, &dst->hy);
   calc_rotate_and_move_origin(x0, y0, rad, src->ix, src->iy, &dst->ix, &dst->iy);

   dst->height = src->height;
   dst->width = src->width;
   dst->beta1 = src->beta1;
   dst->beta2 = src->beta2;
}
void config_generate_xtcurve_list(struct config* config,
      struct XTcurve* xt_up, struct XTcurve* xt_down,
      char* output_txt)
{
   FILE* fp = fopen(output_txt,"w");
   char line[1280];

   // UP side
   for (int cid=1; cid<config->sense_layer_size-1; cid++) {
      int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
      int num_cells = config->cell_size[wid];
      for (int ibeta=0; ibeta<xt_up->nbins_beta; ibeta++) {
         for (int iatan2=0; iatan2<18; iatan2++) {
            int icell = xt_up->longest_icell[cid][ibeta][iatan2];
            double max_angle = xt_up->atan2[cid][ibeta][iatan2];
            double max_zpos = xt_up->zpos[cid][ibeta][iatan2];
            double max_rbound = xt_up->rbound[cid][ibeta][iatan2];
            if (xt_up->nbins_beta==1) {
               fprintf(fp, "UP: cid %d icell %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf\n", cid, icell, iatan2, max_angle/TMath::Pi()*180, max_zpos, max_rbound);
            } else {
               fprintf(fp, "UP: cid %d icell %d ibeta %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf\n", cid, icell, ibeta, iatan2, max_angle/TMath::Pi()*180, max_zpos, max_rbound);
            }
         }
      }
   }

   // DOWN side
   for (int cid=1; cid<config->sense_layer_size-1; cid++) {
      int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
      int num_cells = config->cell_size[wid];
      for (int ibeta=0; ibeta<xt_down->nbins_beta; ibeta++) {
         for (int iatan2=0; iatan2<18; iatan2++) {
            int icell = xt_down->longest_icell[cid][ibeta][iatan2];
            double max_angle = xt_down->atan2[cid][ibeta][iatan2];
            double max_zpos = xt_down->zpos[cid][ibeta][iatan2];
            double max_rbound = xt_down->rbound[cid][ibeta][iatan2];
            if (xt_down->nbins_beta==1) {
               fprintf(fp, "DOWN: cid %d icell %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf\n", cid, icell, iatan2, max_angle/TMath::Pi()*180, max_zpos, max_rbound);
            } else {
               fprintf(fp, "DOWN: cid %d icell %d ibeta %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf\n", cid, icell, ibeta, iatan2, max_angle/TMath::Pi()*180, max_zpos, max_rbound);
            }
         }
      }
   }

   fclose(fp);
}
// 
//
// Garfield's input file for
// calculating XT curve (2014/06/13)
void generate_garfield_xtcurve(
      struct config* config,
      char* output_dir,
      char* txt_calc_list,
      int bfield, // 0: 0T, 1: 1T
      int gas_type,  // 0: He90Iso10, 1: He50Ethane50, 2: He80Met20
      int voltage, // volt 
      double diam_sense_um,
      double diam_field_um)
{
   //char* txt = "prototype_xtcurve_calc_list.txt";
   FILE* fp = fopen(txt_calc_list, "r");
   if (fp==NULL) {
      fprintf(stderr,"ERROR: cannot find calc_list %s\n", txt_calc_list);
      exit(1);
   }
   // do not include two slash!!! (2014/06/21) 
   int slen = strlen(output_dir);
   if (output_dir[slen-1]=='/') output_dir[slen-1]='\0';
   if (output_dir[slen-2]=='/') output_dir[slen-2]='\0';
   fprintf(stderr,"output_dir %s <--- not two slash??\n", output_dir);
   //exit(1);

   int cid;
   int icell;
   int iatan2;
   int ibeta; // 1 or 2
   ///int max_angle; // [0, 360] deg
   double max_angle; // <= change to double !!! (2014/06/22)
   double max_zpos; // z_from_center
   double max_rbound;
   char line[1280];
   char output_txt_fname[1280];
   char xt_file_path[1280];
   double rot_angle;
   while (fgets(line,sizeof(line),fp)) {
      if (strstr(line, "UP")) {

         if (strcmp(config->format_type,"prototype")==0) {
            sscanf(line,"UP: cid %d icell %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf", &cid, &icell, &iatan2, &max_angle, &max_zpos, &max_rbound);
            sprintf(output_txt_fname, "%s/tmp/ST_UP_L_%02d_A_%02d.garf", output_dir, cid, iatan2);
            sprintf(xt_file_path, "%s/ST/ST_UP_L_%02d_A_%02d", output_dir, cid, iatan2);
         } else {
            sscanf(line,"UP: cid %d icell %d ibeta %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf", &cid, &icell, &ibeta, &iatan2, &max_angle, &max_zpos, &max_rbound);
            sprintf(output_txt_fname, "%s/tmp/ST_UP_L_%02d_B_%02d_A_%02d.garf", output_dir, cid, ibeta, iatan2);
            sprintf(xt_file_path, "%s/ST/ST_UP_L_%02d_B_%02d_A_%02d", output_dir, cid, ibeta, iatan2);
         }
         rot_angle = -max_angle; // should be negative (clock wise)
      } else {
         if (strcmp(config->format_type,"prototype")==0) {
            sscanf(line,"DOWN: cid %d icell %d ibeta %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf", &cid, &icell, &ibeta, &iatan2, &max_angle, &max_zpos, &max_rbound);
            sprintf(output_txt_fname, "%s/tmp/ST_DOWN_L_%02d_B_%02d_A_%02d.garf", output_dir, cid, ibeta, iatan2);
            sprintf(xt_file_path, "%s/ST/ST_DOWN_L_%02d_B_%02d_A_%02d", output_dir, cid, ibeta, iatan2);
         } else {
            sscanf(line,"DOWN: cid %d icell %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf", &cid, &icell, &iatan2, &max_angle, &max_zpos, &max_rbound);
            sprintf(output_txt_fname, "%s/tmp/ST_DOWN_L_%02d_A_%02d.garf", output_dir, cid, iatan2);
            sprintf(xt_file_path, "%s/ST/ST_DOWN_L_%02d_A_%02d", output_dir, cid, iatan2);
         }

         rot_angle = 360-max_angle; // should be positive (anti-clock wise)

         //if (cid==1 && icell==14 && ibeta1==1) {
         //   printf("ret %d max_angle %d max_zpos %lf max_rbound %lf\n", ret, max_angle, max_zpos, max_rbound);
         //}
      }
      struct cell_shape cell_shape;
      struct cell_shape new_cell_shape;
      config_get_cell_shape(config, cid, icell, max_zpos, "center", &cell_shape);
      config_transform_cell_shape(&cell_shape, &new_cell_shape);
      double rot_rad = rot_angle/180.0*TMath::Pi();
      double x0 = 0.0;
      double y0 = 0.0;
      config_rotate_cell(&new_cell_shape, x0, y0, rot_rad, &cell_shape);

      gen_xtcurve_file(output_txt_fname, xt_file_path, &cell_shape, bfield, gas_type, voltage, diam_sense_um, diam_field_um, max_rbound);
   }

   fclose(fp);
}
void gen_xtcurve_file(
      char* txt_fname,
      char* xt_file_path,
      struct cell_shape* cell_shape,
      int bfield, // 0: 0T, 1: 1T
      int gas_type,  // 0: He90Iso10, 1: He50Ethane50, 2: He80Met20
      int voltage, // volt 
      double diam_sense_um,
      double diam_field_um,
      double rbound)
{
   FILE* fp = fopen(txt_fname, "w");
   if (fp==NULL) {
      fprintf(stderr,"ERROR: cannot make file %s\n", txt_fname);
      exit(1);
   }
   fprintf(fp, "& CELL\n");
   fprintf(fp, "option nolayer cell-print wire-markers\n");
   fprintf(fp, "rows\n");
   fprintf(fp, "s 1 %lf %lf %lf %d\n", diam_sense_um*1e-4/2.0, cell_shape->ex, cell_shape->ey, voltage);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->ax, cell_shape->ay);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->bx, cell_shape->by);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->cx, cell_shape->cy);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->dx, cell_shape->dy);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->fx, cell_shape->fy);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->gx, cell_shape->gy);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->hx, cell_shape->hy);
   fprintf(fp, "f 1 %lf %lf %lf 0\n", diam_field_um*1e-4/2.0,  cell_shape->ix, cell_shape->iy);
   fprintf(fp, "\n");
   fprintf(fp, "& GAS\n");
   if (gas_type==0) {
      fprintf(fp, "global gas_file=`GASHEISO.DAT`\n");
      fprintf(fp, "get {gas_file}\n");
      fprintf(fp, "heed helium 90 isobutane 10\n");
   } else if (gas_type==1) {
      fprintf(fp, "global gas_file=`G_NO.DAT`\n");
      fprintf(fp, "get {gas_file}\n");
      fprintf(fp, "heed helium 50 ethane 50\n");
   } else if (gas_type==2) {
      fprintf(fp, "global gas_file=`METHANE.DAT`\n");
      fprintf(fp, "HEMETHA80.DAT\n");
      fprintf(fp, "get {gas_file}\n");
      fprintf(fp, "heed helium 80 methane 20\n");
   }
   fprintf(fp, "\n");
   if (bfield==1) {
      fprintf(fp, "& MAGNETIC\n");
      fprintf(fp, "comp 0 0 1.0 T\n");
      fprintf(fp, "\n");
   }
   fprintf(fp, "& DRIFT\n");
   fprintf(fp, "lines 1000\n");
   fprintf(fp, "select 1\n");
   fprintf(fp, "xt-plot x-range 0.0 %lf x-step=0.05 prec=1e-4 print-xt-relation dataset %s\n", rbound, xt_file_path);
   fprintf(fp, "\n");
   fprintf(fp, "& STOP\n");

   fclose(fp);
}

void config_get_rmax(char* txt_calc_list, struct Rmax* rmax)
{
   FILE* fp = fopen(txt_calc_list, "r");
   if (fp==NULL) {
      fprintf(stderr,"ERROR: cannot find calc_list %s\n", txt_calc_list);
      exit(1);
   }
   int cid;
   int icell;
   int iatan2;
   int ibeta1;
   int max_angle; // [0, 360] deg
   double max_zpos; // z_from_center
   double max_rbound;
   char line[1280];
   while (fgets(line,sizeof(line),fp)) {
      if (strstr(line, "UP")) {
         sscanf(line,"UP: cid %d icell %d iatan2 %d max_angle %d max_zpos %lf max_rbound %lf",
               &cid, &icell, &iatan2, &max_angle, &max_zpos, &max_rbound);

         rmax->rmax_up_list[cid][iatan2] = max_rbound;

      } else {
         int ret = sscanf(line,"DOWN: cid %d icell %d ibeta1 %d iatan2 %d max_angle %d max_zpos %lf max_rbound %lf",
               &cid, &icell, &ibeta1, &iatan2, &max_angle, &max_zpos, &max_rbound);

         rmax->rmax_down_list[cid][ibeta1][iatan2] = max_rbound;
      }
   }

   fclose(fp);
}

void config_find_zrange_in_beta_vs_zpos(struct config* config, int cid, int icell, int beta1_or_2, double start_zpos, int direction, double zstep, 
      double* zpos_found, double* beta_found)
{
   struct cell_shape cell_shape;
   double beta;
   double beta_prev=1e10;
   for (int iz=0; ; iz++) {
      double z_from_center = start_zpos + direction*iz*zstep;
      config_get_cell_shape(config, cid, icell, z_from_center, "center", &cell_shape);
      if (beta1_or_2 == 1)      beta = cell_shape.beta1;
      else if (beta1_or_2 == 2) beta = cell_shape.beta2;

      double dbeta = TMath::Abs(beta_prev-beta);
      //printf("cid %d icell %d beta1_or_2 %d z_from_center %lf beta %lf beta_prev %lf dbeta %lf\n", 
      //      cid, icell, beta1_or_2, z_from_center, beta/3.14*180., beta_prev/3.14*180., dbeta/3.14*180.);
      if (dbeta<0.0017 /* 0.1 deg*/) {
         *zpos_found = z_from_center;
         *beta_found = beta;
         return;
      }

      if (iz>0 && dbeta> 0.17 /* 10 deg */) {
         return config_find_zrange_in_beta_vs_zpos(config, cid, icell, beta1_or_2, z_from_center-direction*zstep, direction, zstep*0.1, zpos_found, beta_found);
      }

      beta_prev = beta;
   }
   fprintf(stderr,"ERROR: something wrong...\n");
   exit(1);
}
void config_get_zpos_beta_range(struct config* config, int cid, int icell, int beta1_or_2, double* zmin, double* zmax, double* beta_a, double* beta_b)
{
   struct cell_shape cell_shape;
   config_find_zrange_in_beta_vs_zpos(config, cid, icell, beta1_or_2, 0, -1, 1.0, zmin, beta_a);
   config_find_zrange_in_beta_vs_zpos(config, cid, icell, beta1_or_2, 0, +1, 1.0, zmax, beta_b);
   double dz = *zmax-*zmin;
   //printf("cid %d icell %d beta1_or_2 %d zmin %lf (cm) zmax %lf (cm) dz %lf (cm)\n", cid, icell, beta1_or_2, *zmin, *zmax, dz);
}
void config_init_ZposBeta(struct config* config,  int beta1_or_2, struct ZposBeta* zpos_beta, int nbins_beta, char* name)
{
   strcpy(zpos_beta->name, name);
   double zmin, zmax;
   double beta_a, beta_b;
   zpos_beta->beta1_or_2 = beta1_or_2;
   zpos_beta->nbins_beta = nbins_beta;
   for (int cid=1; cid<config->sense_layer_size-1; cid++) {
      int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
      double dz_max = -1;
      for (int icell=0; icell<config->cell_size[wid]; icell++) {
         config_get_zpos_beta_range(config, cid, icell, beta1_or_2, &zmin, &zmax, &beta_a, &beta_b);

         zpos_beta->zpos_min[cid][icell] = zmin;
         zpos_beta->zpos_max[cid][icell] = zmax;
         zpos_beta->beta_a[cid][icell] = beta_a;
         zpos_beta->beta_b[cid][icell] = beta_b;

         double dz = zmax-zmin;
         //printf("cid %d icell %d dz %lf\n", cid, icell, dz);
         if (dz > dz_max) {
            dz_max = dz;
            zpos_beta->longest_icell[cid] = icell;
         }
      }
   }
   printf("config_init_ZposBeta: done\n");
}
void config_print_ZposBeta(struct config* config, struct ZposBeta* zpos_beta)
{
   for (int cid=1; cid<config->sense_layer_size-1; cid++) {
      int wid = config_get_wid(config, cid, LAYER_TYPE_SENSE);
      int num_cells = config->cell_size[wid];
      for (int icell=0; icell<num_cells; icell++) {
         printf("config_print_ZposBeta: %s ", zpos_beta->name);
         printf("cid %d icell %d: ", cid, icell);
         printf("zpos_min %lf ", zpos_beta->zpos_min[cid][icell]);
         printf("zpos_max %lf ", zpos_beta->zpos_max[cid][icell]);
         printf("dz %lf ",       zpos_beta->zpos_max[cid][icell] - zpos_beta->zpos_min[cid][icell]);
         printf("beta_a %lf ",   zpos_beta->beta_a[cid][icell]/TMath::Pi()*180.0);
         printf("beta_b %lf ",   zpos_beta->beta_b[cid][icell]/TMath::Pi()*180.0);
         printf("\n");
      }
      printf("\t --> longest_icell %d\n", zpos_beta->longest_icell[cid] );
   }
}
double config_find_zpos_from_beta(struct config* config, struct ZposBeta* zpos_beta, int cid, int icell_longest, double beta_rad)
{
   //
   // TODO: check that beta vs zpos is linear function.
   //


   // Before calling this function, call config_init_ZposBeta
   int beta1_or_2 = zpos_beta->beta1_or_2;

   double zmin = zpos_beta->zpos_min[cid][icell_longest];
   double zmax = zpos_beta->zpos_max[cid][icell_longest];
   double ba = zpos_beta->beta_a[cid][icell_longest];
   double bb = zpos_beta->beta_b[cid][icell_longest];

   if (
         (ba > bb && (beta_rad>ba || beta_rad<bb)) ||
         (ba < bb && (beta_rad<ba || beta_rad>bb)) ) {
      printf("cid %d icell_longest %d beta_a %lf beta_b %lf | beta_rad (input) %lf\n", cid, icell_longest, ba/TMath::Pi()*180, bb/3.14*180, beta_rad/TMath::Pi()*180);
      return -2e10; // out of range
   }

   return zmin + (zmax-zmin)/(bb-ba)*(beta_rad-ba);
}

void config_init_XTcurve(struct config* config, 
      struct XTcurve* xt,
      int beta1_or_2,
      int nbins_beta,
      char* name)
{
   xt->beta1_or_2 = beta1_or_2;
   xt->nbins_beta = nbins_beta;
   strcpy(xt->name,name);
   for (int cid=1; cid<config->sense_layer_size-1; cid++) {
      for (int ibeta=0; ibeta<nbins_beta; ibeta++) {
         for (int iatan2=0; iatan2<18;iatan2++) {
            xt->longest_icell[cid][ibeta][iatan2] = -1;
            xt->rbound[cid][ibeta][iatan2] = -1;
            xt->beta[cid][ibeta][iatan2] = -1;
            xt->atan2[cid][ibeta][iatan2] = -1;
            xt->xpos[cid][ibeta][iatan2] = -1e9;
            xt->ypos[cid][ibeta][iatan2] = -1e9;
            xt->zpos[cid][ibeta][iatan2] = -1e9;
            xt->spl[cid][ibeta][iatan2] = NULL;
         }
      }
   }
}
void config_setup_XTcurve(struct config* config,
      char* xt_file_path,
      char* xt_curve_list,
      struct XTcurve* xt_up,
      struct XTcurve* xt_down)
{

   xt_up->xtcurve_file = new TFile(xt_file_path);
   xt_down->xtcurve_file = new TFile(xt_file_path);

   FILE* fp = fopen(xt_curve_list, "r");
   if (fp==NULL) {
      fprintf(stderr,"ERROR: failed to open %s\n", xt_curve_list);
   }
   char line[1280];
   int cid, icell, iatan2, ibeta;
   double max_angle, max_zpos, max_rbound;
   while(fgets(line,sizeof(line),fp)) {
      if (strstr(line,"UP")) {
         if (xt_up->nbins_beta==1) {
            sscanf(line, "UP: cid %d icell %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf", &cid, &icell, &iatan2, &max_angle, &max_zpos, &max_rbound);
            ibeta = 0;
            xt_up->longest_icell[cid][ibeta][iatan2] = icell;
            xt_up->rbound[cid][ibeta][iatan2] = max_rbound;
            xt_up->beta[cid][ibeta][iatan2] = 0;
            xt_up->atan2[cid][ibeta][iatan2] = max_angle*180/TMath::Pi();
            xt_up->zpos[cid][ibeta][iatan2] = max_zpos;
         } else {
            sscanf(line, "UP: cid %d icell %d ibeta %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf", &cid, &icell, &ibeta, &iatan2, &max_angle, &max_zpos, &max_rbound);
            xt_up->longest_icell[cid][ibeta][iatan2] = icell;
            xt_up->rbound[cid][ibeta][iatan2] = max_rbound;
            xt_up->beta[cid][ibeta][iatan2] = ibeta;
            xt_up->atan2[cid][ibeta][iatan2] = max_angle*180/TMath::Pi();
            xt_up->zpos[cid][ibeta][iatan2] = max_zpos;
         }
      } else {
         if (xt_down->nbins_beta==1) {
            fprintf(fp, "DOWN: cid %d icell %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf", &cid, &icell, &iatan2, &max_angle, &max_zpos, &max_rbound);
            ibeta = 0;
            xt_up->longest_icell[cid][ibeta][iatan2] = icell;
            xt_up->rbound[cid][ibeta][iatan2] = max_rbound;
            xt_up->beta[cid][ibeta][iatan2] = 0;
            xt_up->atan2[cid][ibeta][iatan2] = max_angle*180/TMath::Pi();
            xt_up->zpos[cid][ibeta][iatan2] = max_zpos;
         } else {
            fprintf(fp, "DOWN: cid %d icell %d ibeta %d iatan2 %d max_angle %lf max_zpos %lf max_rbound %lf\n", &cid, &icell, &ibeta, &iatan2, &max_angle, &max_zpos, &max_rbound);
            xt_down->longest_icell[cid][ibeta][iatan2] = icell;
            xt_down->rbound[cid][ibeta][iatan2] = max_rbound;
            xt_down->beta[cid][ibeta][iatan2] = ibeta;
            xt_down->atan2[cid][ibeta][iatan2] = max_angle*180/TMath::Pi();
            xt_down->zpos[cid][ibeta][iatan2] = max_zpos;
         }
      }
   }
   fclose(fp);
}


// this will be deleted
void config_init_XTcurve(struct config* config, 
      struct ZposBeta* zpos_beta, 
      struct XTcurve* xt,
      char* name)
{
   strcpy(xt->name,name);
   xt->nbins_beta = 0;
   for (int cid=1; cid<config->sense_layer_size-1;cid++) {
      for (int ibeta=0; ibeta<zpos_beta->nbins_beta;ibeta++) {
         for (int iatan2=0; iatan2<18;iatan2++) {
            xt->longest_icell[cid][ibeta][iatan2]=-1000;
            xt->rbound[cid][ibeta][iatan2] = -1;
            xt->beta[cid][ibeta][iatan2] = -1;
            xt->atan2[cid][ibeta][iatan2] = -1;
            xt->zpos[cid][ibeta][iatan2] = -1e9;
            xt->spl[cid][ibeta][iatan2] = NULL;
         }
      }
   }

   int beta_start = 60;
   int beta_last = 120;
   if (zpos_beta->nbins_beta==1) {
      beta_start = 90;
      beta_last  = 91;
   }
   int nlayers = config->sense_layer_size-1;

   for (int cid=1; cid<nlayers;cid++) {
      int icell_longest = zpos_beta->longest_icell[cid];
      printf("config_set_XTcurve: check cid %d... (nbins_beta %d)\n", cid, zpos_beta->nbins_beta);
      for (int beta=beta_start; beta<beta_last; beta++) {

         int ibeta = (beta-60)/10;
         if (zpos_beta->nbins_beta==1) {
            ibeta = 0;
         }
         double beta_rad;
         double z_from_center;
         if (zpos_beta->nbins_beta==1) {
            beta_rad      = (zpos_beta->beta_a[cid][0]   + zpos_beta->beta_b[cid][0])/2.0;
            z_from_center = (zpos_beta->zpos_min[cid][0] + zpos_beta->zpos_max[cid][0])/2.0;
         } else {
            beta_rad = beta/180.0*TMath::Pi();
            //printf("beta_rad %lf --> beta_deg %lf\n", beta_rad, beta_rad/TMath::Pi()*180.0);

            z_from_center = config_find_zpos_from_beta(config, zpos_beta, cid, icell_longest, beta_rad);
            if (z_from_center < -1e10) continue; // out of range
            //printf("cid %d icell_longest %d beta %d ibeta %d z_from_center %lf\n", cid, icell_longest, beta, ibeta, z_from_center);
            //exit(1);
         }

         for (int atan2=0; atan2<180; atan2++) {
            int iatan2 = atan2/10;
            bool in_local_coord=true;
            double xbound, ybound, rbound;
            double rad = atan2/180.0*TMath::Pi();

            config_find_cell_bondary(config, cid, icell_longest, z_from_center, "center", rad, in_local_coord, &xbound, &ybound, &rbound);
            if (zpos_beta->nbins_beta==1) {
               printf("##### cid %d icell %d z_from_center %lf rbound %lf\n", cid, icell_longest, z_from_center, rbound);
            }

            if (rbound > xt->rbound[cid][ibeta][iatan2]) {
               xt->rbound[cid][ibeta][iatan2] = rbound;
               xt->beta[cid][ibeta][iatan2] = beta;
               xt->atan2[cid][ibeta][iatan2] = atan2;
               xt->zpos[cid][ibeta][iatan2] = z_from_center;
               //if (zpos_beta->nbins_beta==1) {
               //   fprintf(stdout, "ok found !!!! cid %d rbround %lf\n", cid, rbound);
               //}
            }
         }
      }
   }
}
void config_print_XTcurve(struct config* config, struct XTcurve* xt)
{
   int nlayers = config->sense_layer_size-1;
   //int nlayers = 2;
   for (int cid=1; cid<nlayers; cid++) {
      for (int ibeta=0; ibeta<xt->nbins_beta; ibeta++) {
         for (int iatan2=0; iatan2<18; iatan2++) {
            printf("config_print_XTcurve: %s cid %d icell %d ibeta %d iatan2 %d rbound %lf beta %lf atan2 %lf xpos %lf ypos %lf zpos %lf\n", 
                  xt->name,
                  cid, xt->longest_icell[cid][ibeta][iatan2], ibeta, iatan2, 
                  xt->rbound[cid][ibeta][iatan2],
                  xt->beta[cid][ibeta][iatan2]/TMath::Pi()*180,
                  xt->atan2[cid][ibeta][iatan2]/TMath::Pi()*180,
                  xt->xpos[cid][ibeta][iatan2],
                  xt->ypos[cid][ibeta][iatan2],
                  xt->zpos[cid][ibeta][iatan2]);
         }
      }
   }
}

int config_get_drift_time(struct config* config, int iev, int cid, int icell, double hitx, double hity, double hitz_from_center,
      struct XTcurve* xt_up, struct XTcurve* xt_down,
      double* drift_time_ns, double* local_posx, double* local_posy, double* drift_radius, 
      double* cell_beta, // rad
      double* cell_atan2, // rad
      int* cell_ibeta, int* cell_iatan2, int* cell_up_down)
{
   // Do not set for guard layer
   if (strcmp(config->format_type,"prototype")==0) {
      if (cid==0 || cid==10) {
         return -1;
      }
   } else {
      if (cid==0 || cid==19) {
         return -1;
      }
   }
   // Do not set for open cell
   // For Prototype ONLY,
   // Skipe first cell because it is not closed cell
   if (strcmp(config->format_type,"prototype")==0) {
      if (icell==0 || icell==1) {
         return -1;
      }
   }

   // Find position in cell
   double lx, ly, lr;
   int iatan2; // ATan2(y, x) => [-pi, pi] rad
   int ibeta;
   char UD; // 'U': up side , 'D': down side
   double atan2, beta;
   config_get_pos_in_cell(config, cid, icell, hitx, hity, hitz_from_center, &lx, &ly, &lr, &atan2, &beta, &iatan2, &ibeta, &UD);


   //printf("hitx %lf hity %lf hitz %lf lx %lf ly %lf lr %lf atan2 %lf beta %lf iatan2 %d ibeta %d UD %c\n", hitx, hity, hitz_from_center, lx, ly, lr, atan2, beta, iatan2, ibeta, UD);

   int iret=0;
   // Check that lr is less than RMax
   if ((UD=='U' && lr > xt_up->rbound[cid][ibeta][iatan2]) ||  (UD=='D' && (lr > xt_down->rbound[cid][ibeta][iatan2])) ){
      fprintf(stderr,"Warning: lr is larger than Rmax so skip this hit\n");
      iret = 1;
      //      return -1;
      //      return 1;
   }
   int up_down = 1;
   if (UD=='D') up_down = 2;

   // Get corresponding XT curve
   TSpline3* spl = get_xtcurve_spline(config, xt_up, xt_down, up_down, cid, ibeta, iatan2);

   //fprintf(stderr,"A\n");
   // Now XT is ready
   *drift_time_ns = spl->Eval(lr) * 1e3; // us -> ns
   //fprintf(stderr,"B\n");
   *local_posx = lx;
   *local_posy = ly;
   *drift_radius = lr;
   *cell_ibeta = ibeta;
   *cell_iatan2 =iatan2;
   *cell_up_down = (UD=='U') ? 1 : 2;
   *cell_beta=beta;
   *cell_atan2=atan2;

   return iret; // no error
}

static double find_xval(int ntry, double Tmax, double Rmax, TSpline3* spl, double y, double x1, double x2)
{
   double y_epsilon = 1.0; // Stop when reeach 1.0 ns
   if (x2> Rmax) {
      x2 = Rmax;
   }
   if (x1<0) {
      x1 =0;
   }
   if (spl==NULL) {
      fprintf(stderr,"ERROR: find_xval: spl of xt curve is NULL\n");
      exit(1);
   }
   double y1 = spl->Eval(x1) * 1e3; // us -> ns
   double y2 = spl->Eval(x2) * 1e3; // us -> ns
   if (y2<y1) return x2; // Special treatment (2014/06/15)
   //fprintf(stderr,"find_xval: ntry %d Tmax %lf Rmax %lf y %lf x1 %lf x2 %lf | y1 %lf y2 %lf\n", ntry, Tmax, Rmax, y, x1, x2, y1, y2);
   if (y1==y2) return x1;
   if (ntry>0 && y2>Tmax) return x2;

   if (ntry==1000) return -10; // forgive
   ntry++;

   // Finish condition
   if (TMath::Abs(y1-y)<=y_epsilon) {
      return x1;
   } else if (TMath::Abs(y2-y)<=y_epsilon) {
      return x2;
   }

   if (y1>y) {
      return find_xval(ntry, Tmax, Rmax, spl, y, x1/2, x1);
   } else if (y2<=y) {
      return find_xval(ntry, Tmax, Rmax, spl, y, x2, x2*2);
   }
   // Ok, y is between x1 and x2
   double d1 = y - y1; // should be positive
   double d2 = y2 - y; // should be positive
   if (d1<0 || d2<0) {
      fprintf(stderr,"must not happen (d1 %lf d2 %lf)\n", d1, d2);
      exit(1);
   }
   double dd = x2-x1;
   if (d1 < d2) {
      return find_xval(ntry, Tmax, Rmax, spl, y, x1, x2 - dd/2.0);
   } else {
      return find_xval(ntry, Tmax, Rmax, spl, y, x1 + dd/2.0, x2);
   }
}

static TSpline3* get_xtcurve_spline(struct config* config, struct XTcurve* xt_up, struct XTcurve* xt_down, int up_down, int cid, int ibeta, int iatan2)
{
   TSpline3* spl = NULL;
   char spl_name[128];
   if (up_down) { // (up side) beta2
      spl = xt_up->spl[cid][ibeta][iatan2];

      if (spl==NULL) {
         if (strcmp(config->format_type,"prototype")==0) {
            sprintf(spl_name, "ST_U_L_%02d_A_%02d", cid, iatan2);
         } else {
            sprintf(spl_name, "ST_U_L_%02d_B_%02d_A_%02d", cid, ibeta, iatan2);
         }
         //printf("cid %d ibeta %d iatan2 %d spl_name-> %s\n", cid, ibeta, iatan2, spl_name);
         spl = (TSpline3*)xt_up->xtcurve_file->Get(spl_name);
         xt_up->spl[cid][ibeta][iatan2] = spl;
      }

   } else { // (down side) beta1
      spl = xt_down->spl[cid][ibeta][iatan2];

      if (spl==NULL) {
         if (strcmp(config->format_type,"prototype")==0) {
            sprintf(spl_name, "ST_D_L_%02d_B_%02d_A_%02d", cid, ibeta, iatan2);
         } else {
            sprintf(spl_name, "ST_D_L_%02d_A_%02d", cid, iatan2);
         }
         //printf("cid %d ibeta %d iatan2 %d spl_name-> %s\n", cid, ibeta, iatan2, spl_name);
         spl = (TSpline3*)xt_down->xtcurve_file->Get(spl_name);
         xt_down->spl[cid][ibeta][iatan2] = spl;
      }
   }
   if (spl==NULL) {
      fprintf(stderr,"ERROR: get_xtcurve_spline: cannot find xt spline\n");
      exit(1);
   }
   return spl;
}
static double get_xtcurve_rbound(struct XTcurve* xt_up, struct XTcurve* xt_down, int up_down, int cid, int ibeta, int iatan2)
{
   if (up_down==1) {
      return xt_up->rbound[cid][ibeta][iatan2];
   } else {
      return xt_down->rbound[cid][ibeta][iatan2];
   }
   fprintf(stderr,"get_xtcurve_rbound must not happen\n");
   exit(1);
}
double config_find_dist_from_time(int iev, struct config* config, 
      struct XTcurve* xt_up,
      struct XTcurve* xt_down,
      int base_t0_ns, int cid, int icell, double drift_time_ns, int up_down, int ibeta, int iatan2)
{
   TSpline3* spl = get_xtcurve_spline(config, xt_up, xt_down, up_down, cid, ibeta, iatan2);
   double Rmax = get_xtcurve_rbound(xt_up, xt_down, up_down, cid, ibeta, iatan2);

   // Update (2014/06/15)
   // Tmax is very importance because if TMax is not correct, find_xval will surely fail !!
   // Possible reason is Rmax (corner of cell) is outside of position where XT curve is defined because
   // Garfield calculation faield so Evaled value is not correct...
   // 
   // The other reason found is shape around corner is not smooth (monotonic increase)
   // so in this case dist always return Rmax!! => if get unnormal return immediately => `if (y2<y1) return x2; // Special treatment (2014/06/15)`
   //
   //double Tmax = spl->Eval(Rmax)* 1e3; // us -> ns
   double new_Rmax = spl->GetXmax();
   if (new_Rmax<Rmax) {
      // Too many message so hide it ...
      //fprintf(stderr,"Warning: spl defiend range of x is shorter than real cell size\n");
   }
   double Tmax = spl->Eval(new_Rmax)* 1e3; // us -> ns

   double dist = find_xval(0, Tmax, Rmax, spl, drift_time_ns - base_t0_ns, 0.0, new_Rmax);

   /*
    * 2014/06/15: 
    if (cid==9) {
    fprintf(stderr,"iev %d ilayer %d drift_time_ns %d dist %lf Tmax %lf Rmax %lf mc_up_down %d mc_ibeta1 %d mc_iatan2 %d | mc_dist %lf\n",
    iev, cid, drift_time_ns, dist, Tmax, Rmax, mc_up_down, mc_ibeta1, mc_iatan2, mc_dist);
    }
    */
   //if (iev==13 && cid==9) exit(1);

   return dist;
}

#endif
