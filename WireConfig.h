#ifndef _WIRECONFIG_H_
#define _WIRECONFIG_H_

#define LAYER_TYPE_SENSE 1
#define LAYER_TYPE_FIELD 0
#define WIRE_TYPE_SENSE 1
#define WIRE_TYPE_FIELD 0

class WireConfig
{
   public:
      WireConfig();
      void Init(char* fname);
      void Print(FILE* fp);
      void PrintAll(FILE* fp);

      int GetSenseLayerSize();
      int GetCellSize(int cid);

      int GetWid(int cid, int layer_type);

      double GetLayerRadiusAtCenter(int wid);
      double GetLayerRadiusAtCenter(int cid, int layer_type);

      double GetLayerRadius(int wid, double z_from_up);
      double GetLayerRadius(int cid, int layer_type, double z_from_up);

      double GetCellWidthRad(int wid);
      double GetCellWidthRad(int cid, int layer_type);

      double GetThetaFromZ0(int wid, double z_from_up);
      double GetThetaFromZ0(int cid, int layer_type, double z_from_up);

      double GetWireTheta(int wid, int icell, int wire_type, double z_from_up);
      double GetWireTheta(int cid, int layer_type, int icell, int wire_type, double z_from_up);

      void GetWirePos(int wid, int icell, int wire_type, double dz, const char* z_origin, double* wx, double* wy);
      void GetWirePos(int cid, int layer_type, int icell, int wire_type, double dz, const char* z_origin, double* wx, double* wy);
      void GetSenseWirePosAndVector(int cid, int icell, double* px, double* py, double* pz, double* vx, double *vy, double* vz);

      void DrawEndPlate(const char* frame_name);

   private:
      double fInnerWallRadius; // 2013/12/04 -> This is outside of inner wall (2014/01/05)
      double fOuterWallRadius; // 2013/12/04 -> This is inside of outer wall (2014/01/05)

      int fLayerSize; // include both sense and field layer
      int fSenseLayerSize; // cell layer size (pair of same stereo angle of sense and field layer)
      double* fLayerRadiusAtEndplate;  // [ilayer] // added 2013/12/04 -> changed back to Rze
      int* fCellSize;              // [ilayer]
      double *fShift;               // [ilayer] Sense-wire to sense-wire, not hole-to-hole => Changed to double (2014/01/22) for protoytpe chamber
      double *fCellWidth;          // [ilayer] added to manage prototype (dphi=32 deg) (2014/01/21)
      double* fTheta0AtEndplate;  // [ilayer] added 2014/01/05
      double* fLength; // [ilayer] because of end plate is tilted!

      char fFormatType[128];

      bool fDebug;
};

#endif
