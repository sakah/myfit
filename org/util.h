#ifndef UTIL_H
#define UTIL_H

#define PI  3.14159265358979312

#define CALC_ANTI_CLOCK_SIDE -1
#define CALC_CLOCK_SIDE 1
#define CALC_ONLINE 0
#define CALC_MIDDLE 10

void calc_point_on_circle_near_point(double x0, double y0, double R, double x, double y, double* x_on_wire, double* y_on_wire);
double calc_rad2deg(double rad);
double calc_sqrt2(double x, double y);
double calc_dist(double x1, double y1, double x2, double y2);
double calc_drad(double x, double y);
double calc_closest_point_by_two_lines(
    double px1, double py1, double pz1,  // point on line1
    double vx1, double vy1, double vz1,  // vector of line1
    double px2, double py2, double pz2,  //point on line2
    double vx2, double vy2, double vz2,  // vecotr of line2
    double* x1, double* y1, double *z1,  // closest point on line1
    double* x2, double* y2, double *z2,  // closest point on line2
    bool debug); // return closest distance
void norm_vector(double vx, double vy, double vz, double* nvx, double* nvy, double* nvz);
double calc_dot(double x1, double y1, double z1, double x2, double y2, double z2);
double calc_angle_between_two_lines(double x1, double y1, double x2, double y2);
int calc_point_is_anti_clock_wise_side(double xp, double yp, double line_x1, double line_y1, double line_x2, double line_y2);
void calc_rotate_and_move_origin(double x0, double y0, double rad, double old_x, double old_y, double* new_x, double* new_y);
void calc_get_cross_point_with_line(double x1, double y1, double x2, double y2, double rad, double* xcrs, double* ycrs);
void calc_get_cross_point_with_invert_line(double x1, double y1, double x2, double y2, double* xcrs, double* ycrs, double* rad_crs);
#endif
