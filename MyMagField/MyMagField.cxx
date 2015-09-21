#include "MyMagField.h"

MyMagField::MyMagField(const char* field_map, double a_center_z, double a_step_x, double a_step_z, double a_start_x, double a_start_z, bool a_debug)
{
   printf("MyMagField: constructor called (field_map %s) updated 2014/01/10 (2nd)\n", field_map);
   debug = a_debug;
   center_z = a_center_z;
   step_x = a_step_x;
   step_z = a_step_z;
   start_x = a_start_x;
   start_z = a_start_z;

   // Set inital values ==> after reading, check value is set correctly
   for (int ix=0; ix<MAX_X; ix++) {
   for (int iz=0; iz<MAX_Z; iz++) {
      vector_bx[ix][iz] = 1e9;
      vector_bz[ix][iz] = 1e9;
   }
   }
   ix_min = 1e9;
   iz_min = 1e9;
   ix_max = -1e9;
   iz_max = -1e9;
   //printf("center_z %lf\n", center_z);
   read_field_map(field_map, a_debug);

   /* doesn't work for Sasaki-san's field map because region is not square....
   for (int ix=ix_min; ix<=ix_max; ix++) {
   for (int iz=iz_min; iz<=iz_max; iz++) {
      double bx = vector_bx[ix][iz];
      double bz = vector_bz[ix][iz];
      if (bx==1e9 || bz==1e9) {
         fprintf(stderr,"field map is not set correctly!!! there is gap. Check step_x or step_z @ix %d iz %d\n", ix, iz);
         exit(1);
      }
   }
   }
   */
}

void MyMagField::Field(const Double_t* pos, Double_t* B)
{
   /* NOTE : Unit pos (cm) B (kGaus) */

   double x = pos[0];
   double y = pos[1];
   double z = pos[2];

   double r = TMath::Sqrt(x*x+y*y);
   double bx_weight, bz_weight;
   //get_weighted_field(x, z, bx_weight, bz_weight);
   get_weighted_field(r, z, bx_weight, bz_weight);

//   double rad = TMath::ATan2(x,y); // y-axis is x
   double rad = TMath::ATan2(y,x); // use same axis as sasaki-san
//   double bx = bx_weight*TMath::Sin(rad);
//   double by = bx_weight*TMath::Cos(rad);

   // Fix bug.... (2014/01/10)
//   double bx = bx_weight*TMath::Cos(rad);
//   double by = bx_weight*(-1.0)*TMath::Sin(rad);

   // Again Fix bug.... (2014/01/10)
   double bx = bx_weight*TMath::Cos(rad);
   double by = bx_weight*TMath::Sin(rad);

//   B[0] = bx*10.0; // T => kGaus
//   B[1] = by*10.0; // T => kGaus
//   B[2] = bz_weight*10.0; // T => kGaus
   B[0] = -bx*10.0; // T => kGaus
   B[1] = -by*10.0; // T => kGaus
   B[2] = -bz_weight*10.0; // T => kGaus
   //fprintf(stderr,"hoge x %lf y %lf z %lf rad %lf Bx (kG) %lf By (kG) %lf Bz (kG) %lf\n", x,y,z,rad, B[0], B[1], B[2]);
   if (debug) {
      fprintf(stderr,"x %lf y %lf z %lf rad %lf Bx (kGaus) %lf By (kGaus) %lf Bz (kGaus) %lf\n", x,y,z,rad, bx, by, bz_weight);
   }
}
void MyMagField::read_field_map(const char* field_map, bool debug)
{
   /*
   // x: 0 - 0.9 m
   // z: 11.2095 - 13.9095 m
   // step: 5mm 
   // center at z = 12.5 m
    */
   // following values set by constructor (2013/8/1)
//   center_z = 1250.; // cm
//   step_x  = 0.5; // cm = 5mm
//   step_z  = 0.5; // cm = 5mm
//   start_x = 0.0;  // cm
//   start_z = 1120.95;  // cm

   center_iz = (center_z-start_z)/step_z;

   printf("MyMagField:: center_z %lf start_z %lf center_iz %d\n",center_z, start_z, center_iz);
  FILE* fp = fopen(field_map,"r");
  if (fp==NULL) {
     fprintf(stderr,"ERROR: read_field_map:: failed to open %s\n", field_map);
     exit(1);
  }
  char line[1280];
  int num=0;
  double x, y, z, Bx, By, Bz;
  while (fgets(line,sizeof(line),fp)) {
    int nitems =  sscanf(line, "%lf %lf %lf %lf %lf %lf", &x, &y, &z, &Bx, &By, &Bz);
    if (nitems != 6)
      continue;
    x *= 100; // m -> cm
    z *= 100; // m -> cm
    int ix = (x + step_x*0.5 - start_x)/step_x;
    int iz = (z + step_z*0.5 - start_z)/step_z; // iz=0 is at start_z
    if (ix<ix_min) ix_min = ix;
    if (ix>ix_max) ix_max = ix;
    if (iz<iz_min) iz_min = iz;
    if (iz>iz_max) iz_max = iz;
   //printf("MyMagField:: ix %d iz %d\n", ix,iz);
    if (ix>=MAX_X||iz>=MAX_Z) {
       fprintf(stderr,"ERROR: read_field_map:: overflow ix %d (max=%d) iz %d (max=%d) @num %d line %s\n", ix, MAX_X, iz, MAX_Z, num, line);
       fprintf(stderr,"ERROR: read_field_map:: overflow z %lf step_z %lf start_z %lf\n", z, step_z, start_z);
       exit(1);
    }
    vector_x[ix][iz] = x;
    vector_z[ix][iz] = z - center_z;
    vector_bx[ix][iz] = Bx;
    vector_bz[ix][iz] = Bz;
    if (debug) {
    fprintf(stdout,"x %lf (cm) ix %d  ", x, ix);
    fprintf(stdout,"z %lf (cm) iz %d  ", z, iz);
    fprintf(stdout,"Bx %g (tesla) Bz %g (tesla)\n", Bx,Bz);
    }
    num++;
  }
  fclose(fp);
  printf("read_field_map:: read %d points from %s (ix_min %d ix_max %d) (iz_min %d iz_max %d)\n",num,field_map,
        ix_min, ix_max, iz_min, iz_max);

}
//void MyMagField::get_weighted_field(double xpos_in, double zpos, double& bx_weight, double& bz_weight)
void MyMagField::get_weighted_field(double rpos, double zpos, double& bx_weight, double& bz_weight)
{
   //double xpos=xpos_in;
   //if (xpos<0) xpos *= -1.0;

   //int ix = xpos/step_x;
   //int ix_org = ix;
   //double x1 = ix*step_x;
   //double xw = xpos - x1;

   int ix = rpos/step_x;
   int ix_org = ix;
   double x1 = ix*step_x;
   double xw = rpos - x1;

   int iz = (zpos + center_z - start_z)/step_z;
   int iz_org = iz;
   double z1 = iz*step_z;
   double zw = (zpos + center_z - start_z) - z1;
#if 0
   int iz;
   if (zpos<0) {
      iz = (zpos-step_z*0.5)/step_z;
   } else {
      iz = (zpos+step_z*0.5)/step_z;
   }
   //iz = zpos/step_z;
   if (zpos<0) iz -= 1;
   int iz_org = iz;
   double z1 = iz*step_z;
   //double zw = zpos - z1;
   double zw = TMath::Abs(zpos) - z1;
   iz += center_iz;
#endif

//   if (ix>=MAX_X || iz>=MAX_Z || ix <0 || iz<0) { // 2015/02/04 
   if (ix>=(MAX_X-1) || iz>=(MAX_Z-1) || ix <0 || iz<0) {
      bx_weight = 0.0;
      bz_weight = 0.0;
      if (debug) {
         fprintf(stderr,"output region rpos %lf (cm) ix %d zpos %lf (cm) iz %d\n",rpos,ix,zpos,iz);
      }
   } else {
      double bx_A = vector_bx[ix+0][iz+0];
      double bx_B = vector_bx[ix+1][iz+0];
      double bx_C = vector_bx[ix+0][iz+1];
//      double bx_D = vector_bz[ix+1][iz+1];
      double bx_D = vector_bx[ix+1][iz+1];

      double bz_A = vector_bz[ix+0][iz+0];
      double bz_B = vector_bz[ix+1][iz+0];
      double bz_C = vector_bz[ix+0][iz+1];
      double bz_D = vector_bz[ix+1][iz+1];

      bx_weight = bx_A*(1-xw)*(1-zw) + bx_B*xw*(1-zw) + bx_C*(1-xw)*zw + bx_D*xw*zw;
      bz_weight = bz_A*(1-xw)*(1-zw) + bz_B*xw*(1-zw) + bz_C*(1-xw)*zw + bz_D*xw*zw;

      if (debug) {
         fprintf(stderr,"get_weighted_field: rpos %7.3lf (cm) ix %5d (ix_org %5d) x1 %7.3lf (cm) xw %7.3lf (cm) bx_(A,B,C,D) (%lf,%lf,%lf,%lf)\n", rpos, ix, ix_org, x1, xw, bx_A, bx_B, bx_C, bx_D);
         fprintf(stderr,"get_weighted_field: zpos %8.3lf (cm) iz %5d (iz_org %5d) z1 %7.3lf (cm) zw %7.3lf (cm) bz_(A,B,C,D) (%lf,%lf,%lf,%lf)\n", zpos, iz, iz_org, z1, zw, bz_A, bz_B, bz_C, bz_D);
      }
   }

   //    ClassDef(MyMagField,1)  //Interface to MonteCarlo application
}
