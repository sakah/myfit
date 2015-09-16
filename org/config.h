#ifndef CONFIG_H
#define CONFIG_H

#define LAYER_TYPE_SENSE 1
#define LAYER_TYPE_FIELD 0
#define WIRE_TYPE_SENSE 1
#define WIRE_TYPE_FIELD 0

#include "TFile.h"
#include "TCanvas.h"
#include "TSpline.h"

struct config
{
    double inner_wall_radius; // 2013/12/04 -> This is outside of inner wall (2014/01/05)
    double outer_wall_radius; // 2013/12/04 -> This is inside of outer wall (2014/01/05)

    int layer_size; // include both sense and field layer
    int sense_layer_size; // cell layer size (pair of same stereo angle of sense and field layer)
    double* layer_radius_at_endplate;  // [ilayer] // added 2013/12/04 -> changed back to Rze
    int* cell_size;              // [ilayer]
    double *shift;               // [ilayer] Sense-wire to sense-wire, not hole-to-hole => Changed to double (2014/01/22) for protoytpe chamber
    double *cell_width;          // [ilayer] added to manage prototype (dphi=32 deg) (2014/01/21)
    double* theta0_at_endplate;  // [ilayer] added 2014/01/05
    double* length; // [ilayer] because of end plate is tilted!

    char format_type[128];
    // for debug
    int debug;
    int iev;
};

int config_get_sense_layer_size(struct config* config);
int config_get_cell_size(struct config* config, int cid);

void config_init(char* fname, struct config* config);
void config_print(FILE* fp, struct config* config);
void config_print_all(FILE* fp, struct config* config);
//int config_get_axial_layer(struct config* config, int *axials); // 2013/05/03

int config_get_wid(struct config* config, int cid, int layer_type);

double config_get_layer_radius_at_center(struct config* config, int wid);
double config_get_layer_radius_at_center(struct config* config, int cid, int layer_type);

double config_get_layer_radius(struct config* config, int wid, double z_from_up);
double config_get_layer_radius(struct config* config, int cid, int layer_type, double z_from_up);
//void config_get_sense_and_field_layer_radius(struct config* config, int cid, double z_from_up, double* r_sense, double* r_field);

double config_get_cell_width_rad(struct config* config, int wid);
double config_get_cell_width_rad(struct config* config, int cid, int layer_type);

double config_get_theta_from_z0(struct config* config, int wid, double z_from_up);
double config_get_theta_from_z0(struct config* config, int cid, int layer_type, double z_from_up);

double config_get_wire_theta(struct config* config, int wid, int icell, int wire_type, double z_from_up);
double config_get_wire_theta(struct config* config, int cid, int layer_type, int icell, int wire_type, double z_from_up);
//void config_get_sense_and_field_wire_theta(struct config* config, int cid, int icell, double z_from_up, double* theta_sense, double* theta_field);

//double config_get_cell_width_cm(struct config* config, int wid, double z_from_up);
//double config_get_cell_height_cm(struct config* config, int wid, double z_from_up);
//double config_get_stereo_angle(struct config* config, int wid);

void config_get_wire_pos(struct config* config, int wid, int icell, int wire_type, double dz, char* z_origin, double* wx, double* wy);
void config_get_wire_pos(struct config* config, int cid, int layer_type, int icell, int wire_type, double dz, char* z_origin, double* wx, double* wy);
//void config_get_sense_wire_pos_in_sense_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up);
//void config_get_field_wire_pos_in_sense_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up);
//void config_get_sense_wire_pos_in_field_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up); // this is actually field wire!!
//void config_get_field_wire_pos_in_field_layer(struct config* config, int cid, int icell, double* wx, double* wy, double z_from_up);
void config_sense_wire_pos_and_vector(struct config* config, int cid, int icell, double* px, double* py, double* pz, double* vx, double *vy, double* vz);

// Different of config_find_sense_wire_pos/(_and_dist) is that config_get_wire_pos is calculated from arbinary (x,y,z),
// while config_get_wire_pos_internal is calculated from ilayer/icell
int config_hit_is_outside(struct config* config, double x, double y, double z_from_center);
int config_find_sense_wire_pos(struct config* config, double x, double y, double z_from_center, int* cid, int* icell, double* wx, double* wy);
int config_find_sense_wire_pos_and_dist(struct config* config, double x, double y, double z_from_center, int* cid, int* icell, double* wx, double* wy, double* dist);


//int config_check_hit_pos_is_corner(struct config* config, double x, double y, double z);


//int config_get_ishift(struct config* config, int ilayer, double z);
//double config_get_shift_rad(struct config* config, int ilayer, double z);
//void config_draw_hit_on_wire(struct config* config, int ilayer, int icell, double z);

int config_get_ilayer_at_z0(struct config* config, double x, double y);

// added 2013/4/17
double config_get_wire_cross_point(struct config* config, int cid1, int icell1, int cid2, int icell2, double* cx, double *cy, double *cz);


// Cell Shape
// added 2013/12/06
struct cell_shape
{
   //
   //  a   b   c
   //  d   e   f
   //  g   h   i
   //
   double beta1; // angle of hif (down-right)
   double beta2; // angle of bad (up-left)
   double width; // distance between gi
   double height; // distance between bh
   double ax, ay;
   double bx, by;
   double cx, cy;
   double dx, dy;
   double ex, ey;
   double fx, fy;
   double gx, gy;
   double hx, hy;
   double ix, iy;
};
void config_set_cell_shape(
      struct cell_shape* cell_shape,
      double ax,double ay,double bx,double by,double cx,double cy,
      double dx,double dy,double ex,double ey,double fx,double fy,
      double gx,double gy,double hx,double hy,double ix,double iy);
void config_find_closest_sense_or_field_wire_in_field_layer(struct config* config, double x, double y, double dz, char* z_origin, int cid, int icell_start, int wire_type, int* icell_out, double* dist_out);
void config_find_closest_three_field_wires_in_field_layer(struct config* config, double x, double y, double dz, char* z_origin, int cid, int icell_start,
      double* x3, double* y3,
      double* x2, double* y2,
      double* x1, double* y1);
void config_get_cell_shape(struct config* config, int cid, int icell, double dz, char* z_origin, struct cell_shape* cell_shape);
void config_get_cell_shape(struct config* config, int cid, int icell, double dz, char* z_origin, double* xpos, double* ypos, int* wire_id, double* beta1_deg, double* beta2_deg);

/* before drawing, one need to call config_draw_setup(_file) */
void config_draw_setup_file(char* fname);
void config_draw_setup( int xcen, int xwid, int ycen, int ywid, double text_size, double line_width, double s_size, double s_style, double s_color, double f_size, double f_style, double f_color);

TCanvas* config_get_canvas(char* canv_name);
void config_draw_walls(struct config* config);
void config_draw_wires(struct config* config, double dz, char* z_origin, bool draw_cell_shape=true);

void config_draw_cell_shape(struct config* config, int cid, int icell, struct cell_shape* cell_shape, bool draw_wire=false, bool draw_cell_shape=true, int line_color=1, double line_width=-1);
void config_print_cell_shape(struct cell_shape* cell_shape);
void config_print_cell_shape_oneline(char* prefix, struct cell_shape* cell_shape);

void config_draw_mchit_conformal(struct config* config, int color, int ilayer, int icell, double rhit);
void config_draw_mchits_conformal(struct config* config, int color, int nhits, int* ilayer, int* icell, double* rhit);

void config_draw_mchit(struct config* config, int color, int ilayer, int icell, double rhit);
void config_draw_mchits(struct config* config, int color, int nhits, int* ilayer, int* icell, double* rhit);
void config_draw_mchits_from_ROOT(struct config* config, int color, char* root_fname, int iev);

void config_get_pos_in_cell(struct config* config, int cid, int icell, double x, double y, double z_from_center, double* lx, double* ly, double* lr, double* atan2, double* beta, int* iatan2, int* ibeta, char* UD);
void config_find_cell_bondary(struct config* config, int cid, int icell, double dz, char* z_origin, double rad, bool in_local_coord, double* xbound, double* ybound, double* rbound);
void config_transform_cell_shape(struct cell_shape* src, struct cell_shape* dst);
void config_copy_cell_shape(struct cell_shape* src, struct cell_shape* dst);
void config_transform_xypos(struct cell_shape* cell_shape, double org_x, double org_y, double* new_x, double* new_y);
void config_rotate_cell(struct cell_shape* src, double x0, double y0, double rad, struct cell_shape* dst);

// Garfield's calculation file
//void config_generate_xtcurve_list(struct config* config, struct ZposBeta* zb_up, struct ZposBeta* zb_down, struct XTcurve* xt_up, struct XTcurve* xt_down, char* output_txt);
void config_generate_xtcurve_list(struct config* config, struct XTcurve* xt_up, struct XTcurve* xt_down, char* output_txt);
void generate_garfield_xtcurve( struct config* config, char* output_dir, char* txt_calc_list, int bfield, int gas_type, int voltage, double diam_sense_um, double diam_field_um);
void gen_xtcurve_file(char* txt_fname, char* xt_file_path, struct cell_shape* cell_shape, int bfield, int gas_type, int voltage, double diam_sense_um, double diam_field_um, double rbound);

////////////////////
// To be deleted...
// This is for Prototype only (2014/06/14)
struct Rmax
{
   double rmax_up_list[11][18]; // [ilayer][iatan2]
   double rmax_down_list[11][6][18]; // [ilayer][ibeta1][iatan2]
   //int ibeta1_at_z0[11];
};
void config_get_rmax(char* txt_calc_list, struct Rmax* rmax);
////////////////////

void config_find_zrange_in_beta_vs_zpos(struct config* config, int cid, int icell, int beta1_or_2, double start_zpos, int direction, double zstep, double* zpos_found, double* beta_found);
void config_get_zpos_beta_range(struct config* config, int cid, int icell, int beta1_or_2, double* zmin, double* zmax, double* beta_min, double* beta_max);

struct ZposBeta
{
   char name[128];
   int longest_icell[20]; // icell of longest period (largest size of cell) in zpos
   int beta1_or_2; // beta1 is DOWN side, beta2 is UP side of cell
   int nbins_beta; // 1 or 6
   double zpos_min[20][310]; // [18][306] (B1T_square_1.5m_2014_02_10.txt)
   double zpos_max[20][310]; // [18][306] (B1T_square_1.5m_2014_02_10.txt)
   double beta_a[20][310];   // [18][306] (B1T_square_1.5m_2014_02_10.txt)
   double beta_b[20][310];   // [18][306] (B1T_square_1.5m_2014_02_10.txt)
   // There are two cases: beta_a > beta_b or beta_a < beta_b

};
void config_init_ZposBeta(struct config* config,  int beta1_or_2, struct ZposBeta* zpos_beta, int nbins_beta, char* name);
void config_print_ZposBeta(struct config* config, struct ZposBeta* zpos_beta);
double config_find_zpos_from_beta(struct config* config, struct ZposBeta* zpos_beta, int cid, int icell_longest, double beta_rad);
struct XTcurve
{
   char name[128];
   TFile* xtcurve_file;
   int longest_icell[20][6][18]; // icell of longest period (largest size of cell) in zpos
   int beta1_or_2; // beta1 is DOWN side, beta2 is UP side of cell
   int nbins_beta; // 1 or 6
  double rbound[20][6][18]; // [ilayer][ibeta][iatan2]
  double beta[20][6][18];   // [ilayer][ibeta][iatan2]
  double atan2[20][6][18];  // [ilayer][ibeta][iatan2]
  double zpos[20][6][18];  // [ilayer][ibeta][iatan2]
  double xpos[20][6][18];  // [ilayer][ibeta][iatan2]
  double ypos[20][6][18];  // [ilayer][ibeta][iatan2]
  TSpline3* spl[20][6][18];
};
void config_init_XTcurve(struct config* config, struct XTcurve* xt, int beta1_or_2, int nbins_beta, char* name);
void config_print_XTcurve(struct config* config, struct XTcurve* xt);
void config_setup_XTcurve(struct config* config, char* xt_file_path, char* xtcurve_list, struct XTcurve* xt_up, struct XTcurve* xt_down);

int config_get_drift_time(struct config* config, int iev, int cid, int icell, double hitx, double hity, double hitz_from_center,
      struct XTcurve* xt_up, struct XTcurve* xt_down,
      double* drift_time_ns, double* local_posx, double* local_posy, double* drift_radius, 
      double* cell_beta,
      double* cell_atan2,
      int* cell_ibeta, int* cell_iatan2, int* cell_up_down);

double config_find_dist_from_time(int iev, struct config* config, 
      struct XTcurve* xt_up,
      struct XTcurve* xt_down,
      int base_t0_ns, int cid, int icell, int drift_time_ns, int up_down, int ibeta, int iatan2);

#endif
