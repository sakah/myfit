#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "TMath.h"
#include "TH2F.h"

#include "Util.h"
#include "WireConfig.h"

WireConfig::WireConfig()
{
}
void WireConfig::Init(char* fname)
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
           strcpy(fFormatType, body);
        } else if (strcmp(type,"layer_size")==0) { // <= include both sense and field layers
           fSenseLayerSize = 0;
           fLayerSize = atoi(body); 
           fLayerRadiusAtEndplate = (double*)malloc(sizeof(double)*fLayerSize);
           fCellSize = (int*)malloc(sizeof(int)*fLayerSize);
           fCellWidth = (double*)malloc(sizeof(double)*fLayerSize);
           fShift = (double*)malloc(sizeof(double)*fLayerSize);
           fTheta0AtEndplate = (double*)malloc(sizeof(double)*fLayerSize);
           fLength = (double*)malloc(sizeof(double)*fLayerSize);
        } else if (strcmp(type,"layer")==0) { 
           char name[12];
           int wid=-1;                    // Wire Layer ID (start from 1)
           int cid=-1;                    // Cell Layer ID (start from 0)
           char wireType='?';                  // G, F, S
           char stsign='?';                // +, -
           double radius_at_center=-1;    // cm
           double radius_at_endplate=-1;  // cm
           double length=-1;              // Distance between bushes of feedthrough
           int num_wires=-1;              // Number of wires (=2*Cells)
           int num_skip=-1;               // Number of skip holes (=2*Shift)
           double dphi_mrad=-1;           // Difference of angle at endplates = theta_AB
           double stdrop_cm=-1;           // stereo drop
           double stangle_mrad=-1;        // stereo angle
           double theta0_at_endplate=-1;  // first hole's angle at the end plate
           double cell_width=-1;          // cell_width (mrad)
           double shift=-1;               // shift (double, for format_type=prototype)
           int first_sense_hole_pos=-1;  // 0,1,2... (2014/02/01)
           if (strcmp(fFormatType,"prototype")==0) {
              int ncol = sscanf(line,"%s %d %d %c %c %lf %lf %d %lf %lf %d %lf",
                    name, &wid, &cid, &wireType, &stsign, &radius_at_endplate, &length, &num_wires, &shift, &theta0_at_endplate, &first_sense_hole_pos, &cell_width);
              if (ncol!=12) {
                 fprintf(stderr,"ERROR: format is not correct!\n");
                 exit(1);
              }
           } else if (strcmp(fFormatType,"20140104")==0) {
              int ncol = sscanf(line,"%s %d %d %c %c %lf %lf %lf %d %d %lf %lf %lf %lf",
                    name, &wid, &cid, &wireType, &stsign, &radius_at_center, &radius_at_endplate, &length, &num_wires, &num_skip, &dphi_mrad, &stdrop_cm, &stangle_mrad, &theta0_at_endplate);
              if (ncol!=14) {
                 fprintf(stderr,"ERROR: format is not correct!\n");
                 exit(1);
              }
           } else {
              fprintf(stderr,"ERROR: format_type is not set!\n");
              exit(1);
           }
           if (wireType=='G'||wireType=='S') {
              fSenseLayerSize++;
           }

           fLength[layer_size] = length;
           fLayerRadiusAtEndplate[layer_size] = radius_at_endplate;
           fCellSize[layer_size] = num_wires/2;

           if (strcmp(fFormatType,"prototype")==0) {
              fCellWidth[layer_size] = cell_width*1e-3; // mrad -> rad
              fShift[layer_size] = shift;
              fTheta0AtEndplate[layer_size] = theta0_at_endplate*1e-3 + first_sense_hole_pos * cell_width*1e-3/2.0;
           } else {
              fCellWidth[layer_size] = 2.0*TMath::Pi()/fCellSize[layer_size]; 
              fShift[layer_size] = num_skip/2;
              fTheta0AtEndplate[layer_size] = theta0_at_endplate*1e-3;
           }

           printf("wireType %c wid %d cid %d raidus_at_endplate %lf (cm) length %lf (cm) cell_size %d shift %lf theta0_at_endplate %lf (mrad) stereo_drop %lf (cm) first_sense_hole_pos %d\n", 
                 wireType,wid,cid,radius_at_endplate,length, fCellSize[layer_size],fShift[layer_size],theta0_at_endplate, stdrop_cm, first_sense_hole_pos);

           layer_size++;
        }
        else if (strcmp(type,"inner_wall_radius(cm)")==0) { fInnerWallRadius = atof(body); }  // 2013/12/04
        else if (strcmp(type,"outer_wall_radius(cm)")==0) { fOuterWallRadius = atof(body); }  // 2013/12/04
        else {
           fprintf(stderr,"ERROR: unknow wireType -> '%s'\n", type);
           exit(1);
        }
    }
    if (layer_size!=fLayerSize) {
       fprintf(stderr,"ERROR: layer size is not equal with one you set in layer_size (ilayer=%d, layer_size %d)\n", layer_size, fLayerSize);
       exit(1);
    }

    fclose(fp);
    printf("config_init: read %d layers (%d sense layers)\n", fLayerSize, fSenseLayerSize);
    //exit(1);
}
void WireConfig::Print(FILE* fp)
{
   fprintf(fp, "layer_size        %d\n", fLayerSize);
   fprintf(fp, "inner_wall_radius %lf\n",fInnerWallRadius);
   fprintf(fp, "outer_wall_radius %lf\n",fOuterWallRadius);
}
void WireConfig::PrintAll(FILE* fp)
{
   double xs, ys;
   double xf, yf;
   double z_from_up = 0.0; // at end plate
   fprintf(fp, "#layer wire global  local wire  x(cm)      y(cm)\n");
   for (int wid = 0; wid < fLayerSize; wid++) {
      for (int icell = 0; icell < fCellSize[wid]; icell++) {
         GetWirePos(wid, icell, WIRE_TYPE_SENSE, z_from_up, "up", &xs, &ys);
         GetWirePos(wid, icell, WIRE_TYPE_FIELD, z_from_up, "up", &xf, &yf);
         fprintf(fp, "sense wire %5d %5d %10.5lf %10.5lf\n", wid+1,icell+1,xs,ys);
         fprintf(fp, "field wire %5d %5d %10.5lf %10.5lf\n", wid+1,icell+1,xf,yf);
      }
   }
}
int WireConfig::GetSenseLayerSize()
{
   return fSenseLayerSize;
}
int WireConfig::GetCellSize(int cid)
{
   int wid = GetWid(cid, LAYER_TYPE_SENSE);
   return fCellSize[wid];
}
int WireConfig::GetWid(int cid, int layer_type)
{
   // Start from Guard layer
   // Note on wid: In Excel, wid start from 1, but in code, start from 0
   int ilayer;
   if (strcmp(fFormatType,"prototype")==0) {
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
double WireConfig::GetLayerRadiusAtCenter(int wid)
{
   double drad = GetCellWidthRad(wid);
   double theta_AB =  drad*fShift[wid];
   double Rz0 = fLayerRadiusAtEndplate[wid]*TMath::Cos(theta_AB/2.0);
   return Rz0;
}
double WireConfig::GetLayerRadiusAtCenter(int cid, int layer_type)
{
   int wid = GetWid(cid, layer_type);
   return GetLayerRadiusAtCenter(wid);
}
double WireConfig::GetLayerRadius(int wid, double z_from_up)
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
      return fInnerWallRadius;
   } else if (wid>=fLayerSize) { // layer after last layer
      return fOuterWallRadius;
   }
   if (z_from_up<0) {
      z_from_up = 0;
   }
   if (z_from_up>fLength[wid]) {
      z_from_up = fLength[wid];
   }

   double radius_at_center = GetLayerRadiusAtCenter(wid);
   double theta_from_z0    = GetThetaFromZ0(wid, z_from_up);
   double radius_at_z = radius_at_center/TMath::Cos(theta_from_z0);
   return radius_at_z;
}
double WireConfig::GetLayerRadius(int cid, int layer_type, double z_from_up)
{
   int wid = GetWid(cid, layer_type);
   return GetLayerRadius(wid, z_from_up);
}
double WireConfig::GetCellWidthRad(int wid)
{ 
   /*
    *  2pi/ncells: not z-independent
    */
   if (wid==-1) wid=0; // 2013/120/09: inner_wall (layer==-1) consider as first layeer(ilayer=0)
   return fCellWidth[wid];  // Modified for prototype chamber (2014/01/21)
}
double WireConfig::GetCellWidthRad(int cid, int layer_type)
{
   int wid = GetWid(cid, layer_type);
   return GetCellWidthRad(wid);
}
double WireConfig::GetThetaFromZ0(int wid, double z_from_up)
{
   /* Sign(theta) = Sign(shift) * Sign(f) */
   double Rz0 = GetLayerRadiusAtCenter(wid);
   double zratio = z_from_up/fLength[wid]; // Range: [0.0, 1.0]
   double f = zratio - 0.5;
   double drad = GetCellWidthRad(wid);
   double theta_AB =  drad*fShift[wid];
   double dLe = Rz0*TMath::Tan(theta_AB/2.0);
   double dLz = 2.0*dLe*f;
   return TMath::ATan(dLz/Rz0);
}
double WireConfig::GetThetaFromZ0(int cid, int layer_type, double z_from_up)
{
   int wid = GetWid(cid, layer_type);
   return GetThetaFromZ0(wid, z_from_up);
}

double WireConfig::GetWireTheta(int wid, int icell, int wire_type, double z_from_up)
{
   // Comments(2014/02/06)
   // For prototype, icell == -1 works
   // For readl, icell += cell_size, so always positive

   // How to determine theta at given z
   // 1. calc theta at center
   // 2. add theta by config_get_theta_from_center
   double drad = GetCellWidthRad(wid);
   double theta_AB = drad*fShift[wid];
   double theta0_at_endplate = fTheta0AtEndplate[wid];
   double theta0_at_center = theta0_at_endplate + theta_AB/2.0;
   double theta0 = theta0_at_center + drad*icell + GetThetaFromZ0(wid, z_from_up);
   if (wire_type==WIRE_TYPE_FIELD) {
      theta0 += drad/2.0;
   }
   return theta0;
}
double WireConfig::GetWireTheta(int cid, int layer_type, int icell, int wire_type, double z_from_up)
{
   int wid = GetWid(cid, layer_type);
   return GetWireTheta(wid, icell, wire_type, z_from_up);
}
void WireConfig::GetWirePos(int wid, int icell, int wire_type, double dz, const char* z_origin, double* wx, double* wy)
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

   if (icell<0) icell += fCellSize[wid];

   double z_from_up = dz;
   if (strcmp(z_origin,"center")==0) {
      z_from_up += fLength[wid]/2.0;
   } else if (strcmp(z_origin,"up")==0) {
   } else {
      fprintf(stderr,"z_origin should be center or up (%s)\n",z_origin);
      exit(1);
   }
   double Rz  = GetLayerRadius(wid, z_from_up);
   double rad = GetWireTheta(wid, icell, wire_type, z_from_up);
//   printf("hoge Rz %lf rad %lf\n", Rz, rad);
   
   *wx = Rz*TMath::Cos(rad);
   *wy = Rz*TMath::Sin(rad);
}
void WireConfig::GetWirePos(int cid, int layer_type, int icell, int wire_type, double dz, const char* z_origin, double* wx, double* wy)
{
   int wid = GetWid(cid, layer_type);
   GetWirePos(wid, icell, wire_type, dz, z_origin, wx, wy);
}
void WireConfig::GetSenseWirePosAndVector(int cid, int icell_z0, double* px, double* py, double* pz, double* vx, double *vy, double* vz)
{
   int wid = GetWid(cid, LAYER_TYPE_SENSE);
   /*
    * calculate wire position at upstream end cap and wire's direction
    */
   double x1,y1, z1=0; // upstream
   double x2,y2, z2=fLength[wid]; // downstream
   //printf("config_sense_wire_pos_and_vector wid %d cid %d icell_z1 %d zw %lf\n", wid, cid, icell_z0, z2);

   GetWirePos(wid, icell_z0, WIRE_TYPE_SENSE, z1, "up", &x1, &y1);
   GetWirePos(wid, icell_z0, WIRE_TYPE_SENSE, z2, "up", &x2, &y2);
   *px = x1;
   *py = y1;
   *pz = z1;
   *vx = x2-x1;
   *vy = y2-y1;
   *vz = z2-z1;
   //printf("shift %d *vx %lf *vy %lf *vz %lf deg %lf\n",shift, *vx, *vy, *vz, rad1/3.14159*180.0);
}
void WireConfig::DrawEndPlate(const char* frame_name)
{
   TH2F* hframe = new TH2F(frame_name, "", 100, -100, 100, 100, -100, 100);
   hframe->SetStats(0);
   hframe->Draw();

   for (int ilayer=0; ilayer<20; ilayer++) {
      if (ilayer%2==0) continue;
      double r = GetLayerRadius(ilayer, LAYER_TYPE_SENSE, 0);
      draw_ellipse(0, 0, r, kGray);
   }
}
