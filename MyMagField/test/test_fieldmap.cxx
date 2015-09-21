#include "MyMagField2.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    if (argc!=2) {
       fprintf(stderr, "Usage %s <input_x_y_z.txt>\n", argv[0]);
       return -1;
    }
    char* input_txt = argv[1];
#if 0
    // Ver5
    const char* fmap = "FieldMap_for_COMET_Phase1/fieldmap_by_sasaki_ver5/Bmap130927fm.dat";
    double center_z = 1210; //cm
    double step_x = 1.0; // cm
    double step_z = 1.0; // cm
    double start_x = 0.0; //cm
    double start_z = 946.239; //cm
//    bool debug = true;
    bool debug = false;
#endif

    // IHEP ver1 (140905)
    const char* fmap = "../MyMagField/FieldMap_for_COMET_Phase1/fieldmap_by_IHEP_ver1/IHEP_A9_140905.txt";
    //         double center_z = 1210; //cm    <= comment out at 2014/05/10
    //         double center_z = 1210 - 3.5; // minium case (2014/05/10)
    double center_z = 595.26; // cm (3m + 2952.6mm)
    double step_x = 1.002; // cm
    double step_z = 1.002; // cm
    double start_x = 0.501253; //cm
    double start_z = 300; 
    //bool debug = true;
    bool debug = false;

    MyMagField2 * fMagField = new MyMagField2(fmap, center_z, step_x, step_z, start_x, start_z, debug);
    printf("fMagField %p\n", fMagField);

    FILE* fp = fopen(input_txt, "r");
    if (fp==NULL) {
       fprintf(stderr,"failed to open %s\n", input_txt);
       return -1;
    }
    double x,y,z;
    double bx,by,bz;
    double pos[3], B[3];
    char line[1280];
    while (fgets(line,sizeof(line),fp)) {
       if (line[0]=='#') continue;
       sscanf(line, "%lf %lf %lf", &x, &y, &z);
       pos[0] = x;
       pos[1] = y;
       pos[2] = z;
       fMagField->Field(pos, B);
       printf("%lf %lf %lf %lf %lf %lf\n", x, y, z, B[0], B[1], B[2]);
    }
    fclose(fp);
    return 0;

}
