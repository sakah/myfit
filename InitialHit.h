#ifndef INITIALHIT_H
#define INITIALHIT_H

class InitialHit
{
   public:
      InitialHit();
      void SetBranchAddress(TTree*t, char* x, char* y, char*z, char* px, char* py, char* pz);
      double GetX();
      double GetY();
      double GetR();
      double GetZ();
      double GetPx();
      double GetPy();
      double GetPt();
      double GetPz();
      double GetPa();
      void PrintHit();

   private:
      double fX;
      double fY;
      double fZ;
      double fPx;
      double fPy;
      double fPz;
};

#endif
