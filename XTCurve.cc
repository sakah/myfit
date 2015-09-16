#include "XTCurve.h"

double XTCurve::GetTime(double x)
{
   // x: cm
   double const_velocity = 2.0e-3; // 2.0 [cm/us]
   return x/const_velocity; // ns
}
