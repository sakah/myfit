#include "Util.h"

#include "TMath.h"

double pow2(double a, double b) { return a*a + b*b; }
double sqrt2(double a, double b) { return TMath::Sqrt(a*a+b*b); }
double sqrt3(double a, double b, double c) { return TMath::Sqrt(a*a+b*b+c*c); };
