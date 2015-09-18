#ifndef UTIL_H
#define UTIL_H

double pow2(double a, double b);
double sqrt2(double a, double b);
double sqrt3(double a, double b, double c);
void rotate_by(double x0, double y0, double angle, int num, double* x1, double* y1, double* x2, double* y2);
void draw_ellipse(double x, double y, double r, int col);
void draw_marker(double x, double y, int col, int style);
void draw_frame(char* title, int nx, double xmin, double xmax, int ny, double ymin, double ymax);
void draw_graph(char* title, double xmin, double xmax, double ymin, double ymax, int nhits, double* x, double* y, int col, int style);
void draw_line_AB(double a, double b, double xmin, double xmax, int col, int style);
void draw_line_AB2(double a, double b, double xmin, double xmax, int col, double threshold);
void draw_line_TR(double theta, double rho, double xmin, double xmax, int col, int style);

#endif
