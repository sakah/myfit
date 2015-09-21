#include "MyMagField2.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    // Ver5
    const char* fmap = "FieldMap_for_COMET_Phase1/fieldmap_by_sasaki_ver5/Bmap130927fm.dat";
    double center_z = 1210; //cm
    double step_x = 1.0; // cm
    double step_z = 1.0; // cm
    double start_x = 0.0; //cm
    double start_z = 946.239; //cm
//    bool debug = true;
    bool debug = false;

    MyMagField2 * fMagField = new MyMagField2(fmap, center_z, step_x, step_z, start_x, start_z, debug);
    printf("fMagField %p\n", fMagField);

    char *fname = argv[1];
    FILE* fp = fopen(fname, "r");
    if (fp==NULL) {
       fprintf(stderr,"error to open %s\n", fname);
       exit(1);
    }

    double x,y,z;
    double bx,by,bz;
    double pos[3], B[3];
    char line[1280];
    while (fgets(line,sizeof(line),fp)) {
       sscanf(line, "%lf %lf %lf", &x, &y, &z);
       pos[0] = x;
       pos[1] = y;
       pos[2] = z + 40; // offset from wuchen
       fMagField->Field(pos, B);
       printf("%lf %lf %lf %lf %lf %lf\n", x, y, z, B[0], B[1], B[2]);
    }
    fclose(fp);
    return 0;

}


