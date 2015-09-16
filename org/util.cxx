#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TMath.h"
#include "util.h"

void calc_point_on_circle_near_point(double x0, double y0, double R, double x, double y, double* x_on_wire, double* y_on_wire)
{
   double dx = x - x0;
   double dy = y - y0;
   double rad = TMath::ATan2(dy, dx); // [-pi, pi]
   *x_on_wire = R*TMath::Cos(rad) + x0;
   *y_on_wire = R*TMath::Sin(rad) + y0;
}

double calc_rad2deg(double rad)
{
   return rad/TMath::Pi()*180.0;
}
double calc_sqrt2(double x, double y)
{
   return TMath::Sqrt(x*x+y*y);
}
double calc_dist(double x1, double y1, double x2, double y2)
{
    double dx = x1-x2;
    double dy = y1-y2;
    return sqrt(dx*dx+dy*dy);
}
double calc_drad(double x, double y)
{
    if (x == 0.0) {
        if (y > 0)
            return PI/2.0;
        else if (y < 0)
            return -PI/2.0;
        else {
            fprintf(stderr,"calc_drad: x == y == 0, cannot calculate angle\n");
            exit(1);
        }
    } else if (y == 0.0) {
        if (x > 0) 
            return 0.0;
        else if (x < 0)
            return -PI;
    }
    
    double r = sqrt(x*x+y*y);
    if (y > 0) { 
        return acos(x/r);
    } else if (y < 0) {
        if (x > 0) {
            return 2.0*PI + asin(y/r);
        } else {
            return PI - asin(y/r);
        }
    }
    fprintf(stderr,"ERROR: calc_drad must not happen\n");
    exit(1);
    return 0;
}
double calc_closest_point_by_two_lines(
    double px1, double py1, double pz1,  // point on line1
    double vx1, double vy1, double vz1,  // vector of line1
    double px2, double py2, double pz2,  //point on line2
    double vx2, double vy2, double vz2,  // vecotr of line2
    double* x1, double* y1, double *z1, // closest point on line1
    double* x2, double* y2, double *z2,  // closest point on line2
    bool debug)
{
  double dist = 0.0;

  // normalize vectors
  double nvx1, nvy1, nvz1;
  double nvx2, nvy2, nvz2;
  norm_vector(vx1, vy1, vz1, &nvx1, &nvy1, &nvz1);
  norm_vector(vx2, vy2, vz2, &nvx2, &nvy2, &nvz2);
  double p21x = px2 - px1;
  double p21y = py2 - py1;
  double p21z = pz2 - pz1;
  double D1 = calc_dot(p21x, p21y, p21z, nvx1, nvy1, nvz1);
  double D2 = calc_dot(p21x, p21y, p21z, nvx2, nvy2, nvz2);
  double V  = calc_dot(nvx1, nvy1, nvz1, nvx2, nvy2, nvz2);
  //fprintf(stderr,"nvx1 %lf nvy1 %lf nvz1 %lf\n",nvx1,nvy1,nvz1);
  //fprintf(stderr,"nvx2 %lf nvy2 %lf nvz2 %lf\n",nvx2,nvy2,nvz2);
  //fprintf(stderr,"D1 %lf D2 %lf V %lf\n",D1,D2,V);
  if (V==1.0 || V==-1.0) {
    fprintf(stderr,"ERROR: calc_closest_point_by_two_lines: two lines are parallel\n");
    exit(1);
  }
  double t1 = (D1-V*D2)/(1.0-V*V);
  double t2 = (V*D1-D2)/(1.0-V*V);
  double ux = p21x + t2*nvx2 - t1*nvx1;
  double uy = p21y + t2*nvy2 - t1*nvy1;
  double uz = p21z + t2*nvz2 - t1*nvz1;
  dist = sqrt(ux*ux+uy*uy+uz*uz);
  if (debug) {
     fprintf(stdout,"calc_closest px1 %lf py1 %lf pz1 %lf\n",px1, py1, pz1);
     fprintf(stdout,"calc_closest vx1 %lf vy1 %lf vz1 %lf\n",vx1, vy1, vz1);
     fprintf(stdout,"calc_closest px2 %lf py2 %lf pz2 %lf\n",px2, py2, pz2);
     fprintf(stdout,"calc_closest vx2 %lf vy2 %lf vz2 %lf\n",vx2, vy2, vz2);
     fprintf(stdout,"calc_closest D1 %lf D2 %lf V %lf t1 %lf t2 %lf dist %lf\n",D1,D2,V,t1,t2,dist);
  }
  
  *x1 = px1 + t1*nvx1;
  *y1 = py1 + t1*nvy1;
  *z1 = pz1 + t1*nvz1;
  *x2 = px2 + t2*nvx2;
  *y2 = py2 + t2*nvy2;
  *z2 = pz2 + t2*nvz2;

  return dist;
}
void norm_vector(double vx, double vy, double vz, double* nvx, double* nvy, double* nvz)
{
  double length = sqrt(vx*vx+vy*vy+vz*vz);
  *nvx = vx/length;
  *nvy = vy/length;
  *nvz = vz/length;
}
double calc_dot(double x1, double y1, double z1, double x2, double y2, double z2)
{
  return x1*x2 + y1*y2 + z1*z2;
}
double calc_angle_between_two_lines(double x1, double y1, double x2, double y2)
{
   double r1 = TMath::Sqrt(x1*x1+y1*y1);
   double r2 = TMath::Sqrt(x2*x2+y2*y2);
   double nx1 = x1/r1;
   double ny1 = y1/r1;
   double nx2 = x2/r2;
   double ny2 = y2/r2;
   return TMath::ACos(nx1*nx2+ny1*ny2);
   /*
   double rad1 = TMath::ATan2(y1, x1);
   double rad2 = TMath::ATan2(y2, x2);
   printf("rad1 %lf\n", rad1/TMath::Pi()*180.0);
   printf("rad2 %lf\n", rad2/TMath::Pi()*180.0);
   return TMath::Abs(rad2 - rad1);
   */
}
int calc_point_is_anti_clock_wise_side(double xp, double yp, double line_x2, double line_y2, double line_x1, double line_y1)
{
   //
   //
   //  (x2, y2)
   //
   //     |
   //     |
   //     |     (xp, yp)
   //     |
   //     |
   //
   //  (x1, y1)
   //
   //
   //
   double dx2 = line_x2 - line_x1;
   double dy2 = line_y2 - line_y1;
   double dxp = xp - line_x1;
   double dyp = yp - line_y1;
   double crx = dx2*dyp - dy2*dxp;
   int iret = 0;
   if (crx>0) iret =  CALC_ANTI_CLOCK_SIDE;
   else if (crx<0) iret =  CALC_CLOCK_SIDE;
   else if (crx==0) iret =  CALC_ONLINE;
   //printf("dx2 %lf dy2 %lf dxp %lf dyp %lf iret %d crx %lf\n", dx2, dy2, dxp, dyp, iret, crx);
   return iret;
}
void calc_rotate_and_move_origin(double x0, double y0, double rad, double old_x, double old_y, double* new_x, double* new_y)
{
   double mycos = TMath::Cos(rad);
   double mysin = TMath::Sin(rad);
   *new_x = (old_x - x0) * mycos - (old_y - y0) * mysin;
   *new_y = (old_x - x0) * mysin + (old_y - y0) * mycos;
}
void calc_get_cross_point_with_line(double x1, double y1, double x2, double y2, double rad, double* xcrs, double* ycrs)
{
   double slope1 = TMath::Tan(rad);
   double offset1 = 0.0;
   double dx = x2-x1;
   double dy = y2-y1;
   if (dx==0) {
      fprintf(stderr,"ERROR: calc_get_cross_point_with_line: slope dx==0\n");
      exit(1);
   }
   double slope2 = dy/dx;
   double offset2 = -slope2 * x1 + y1;
   *xcrs = (offset2 - offset1)/(slope1 - slope2);
   *ycrs = slope1*(*xcrs) + offset1;
}
void calc_get_cross_point_with_invert_line(double x1, double y1, double x2, double y2, double* xcrs, double* ycrs, double* rad_crs)
{
   if (x1==x2) {
      *xcrs = x1;
      *ycrs = 0.0;
      *rad_crs = 0.0;
      return;
   }
   double a = (y2-y1)/(x2-x1);
   *xcrs = a*x1-y1/(a*1.0/a);
   *ycrs = -(*xcrs)/a;
   *rad_crs = TMath::ATan2(*ycrs, *xcrs); // [-pi, pi]
}

