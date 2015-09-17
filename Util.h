#ifndef UTIL_H
#define UTIL_H

double pow2(double a, double b);
double sqrt2(double a, double b);
double sqrt3(double a, double b, double c);
void draw_ellipse(double x, double y, double r, int col);
void draw_marker(double x, double y, int col, int style);
void draw_frame(char* title, int nx, double xmin, double xmax, int ny, double ymin, double ymax);
void draw_graph(char* title, double xmin, double xmax, double ymin, double ymax, int nhits, double* x, double* y, int col, int style);

#endif
