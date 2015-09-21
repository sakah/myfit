#ifndef _MYMAGFIELD_H
#define _MYMAGFIELD_H

#include <stdio.h>
#include <stdlib.h>
#include "TMath.h"
#include "TVirtualMagField.h"

class MyMagField : public TVirtualMagField
{
   public:
      MyMagField(const char* field_map, double a_center_z, double a_step_x, double a_step_z, double a_start_x, double a_start_z, bool a_debug);
      virtual ~MyMagField() {};
      //virtual TClass* IsA() const {};
      //virtual void ShowMembers(TMemberInspector& insp) {};
      //virtual void Streamer(TBuffer& b) {};
      virtual void Field(const Double_t* pos, Double_t* B);

   private:
      void read_field_map(const char* field_map, bool debug);
//#define MAX_X 181
#define MAX_X 200
//#define MAX_Z 541
#define MAX_Z 650
      int ix_min;
      int iz_min;
      int ix_max;
      int iz_max;
      double vector_x[MAX_X][MAX_Z]; // cm
      double vector_z[MAX_X][MAX_Z]; // cm
      double vector_bx[MAX_X][MAX_Z]; // tesla
      double vector_bz[MAX_X][MAX_Z]; // tesla
      double center_z; // cm
      double step_x; // cm
      double step_z; // cm
      double start_x; // cm
      double start_z; // cm
      int center_iz;

      //void get_weighted_field(double xpos_in, double zpos, double& bx_weight, double& bz_weight);
      void get_weighted_field(double rpos, double zpos, double& bx_weight, double& bz_weight);
      bool debug;
};

#endif
