#ifndef _COMF_H
#define _COMF_H

#include "Circle.h"

class Conformal
{
   int num_hits;
   int ilayers[10000];
   int icells[10000];
   int iturns[10000];
   // before
   double xhits[10000];
   double yhits[10000];
   // after
   double uhits[10000];
   double vhits[10000];
   double eu[10000];
   double ev[10000];
   Conformal()
   {
      num_hits = 0;
   };
   void add_hits(Circle& circ)
   {
      int n = num_hits;
      for (int ihit=0; ihit<circ.nhits; ihit++) {
         if (n>=10000) {
            fprintf(stderr,"Conformal: too many hits...\n");
            break;
         }
         ilayers[n] = circ.hits_ilayer[ihit];
         icells[n] = circ.hits_icell[ihit];
         iturns[n] = circ.hits_iturn[ihit];
         xhits[n] = circ.xhits[ihit];
         yhits[n] = circ.yhits[ihit];
         double r2 = xhits[ihit]*xhits[ihit] + yhits[ihit]*yhits[ihit];
         uhits[n] = 2.0*xhits[ihit]/r2;
         vhits[n] = 2.0*yhits[ihit]/r2;
         eu[n] = 1.0;
         ev[n] = 1.0;
         n++;
      }
      num_hits = n;
   };
};

#endif
