/* Copyright 2008-2010, Technische Universitaet Muenchen,
   Authors: Christian Hoeppner & Sebastian Neubert & Johannes Rauch

   This file is part of GENFIT.

   GENFIT is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GENFIT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with GENFIT.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "FieldMap.h"
#include <stdlib.h>

namespace genfit {

   FieldMap::FieldMap(char* field_map, bool debug)
   {
      // IHEP ver1 (140905)
      //       const char* fmap = "/work2/sakamoto/mu3e/Genfit/genfit/geant4_vmc/examples/C01/MyMagField/FieldMap_for_COMET_Phase1/fieldmap_by_IHEP_ver1/IHEP_A9_140905.txt";
      if (!strstr(field_map, "IHEP_A9_140905.txt")) {
         fprintf(stderr,"FieldMap::FieldMap IHEP ver1 is expected. Modify `%s` manually\n", __FILE__);
         exit(1);
      }
      //         double center_z = 1210; //cm    <= comment out at 2014/05/10
      //         double center_z = 1210 - 3.5; // minium case (2014/05/10)
      // Move chamber to field map... => so zshift is 0
      double zshift = 0;
      double center_z = 595.26 - zshift; // cm (3m + 2952.6mm)
      double step_x = 1.002; // cm
      double step_z = 1.002; // cm
      double start_x = 0.501253; //cm
      double start_z = 300;
      //bool debug = false;

      fld = new MyMagField(field_map, center_z, step_x, step_z, start_x, start_z, debug);
      printf("FieldMap:: read fild_map %s start_z %f (modified 2014/10/14)\n", field_map, start_z);
   }

   TVector3 FieldMap::get(const TVector3& pos) const
   {
      fprintf(stderr,"not implemented\n");
      exit(1);
   }

   void FieldMap::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const
   {
      Double_t pos[3];
      Double_t B[3];
      pos[0] = posX;
      pos[1] = posY;
      pos[2] = posZ;

      fld->Field(pos, B);

      Bx = B[0]; // kGaus
      By = B[1]; // kGaus
      Bz = B[2]; // kGaus
   }

} /* End of namespace genfit */
