{
  // x: 0 - 0.9 m
  // z: 11.2095 - 13.9095 m
  // step: 5mm 
  char* fname = "DetectorArea130701fm.txt";
  FILE* fp = fopen(fname,"r");

  double z_offset = 12.5;

  double vector_x[100000];
  double vector_z[100000];
  double vector_bx[100000];
  double vector_bz[100000];
  int num = 0;
  char line[1280];
  double x, y, z, Bx, By, Bz;
  double min=1e10;
  double max=-1000;
  while (fgets(line,sizeof(line),fp)) {
    int nitems =  sscanf(line, "%lf %lf %lf %lf %lf %lf", &x, &y, &z, &Bx, &By, &Bz);
    if (nitems != 6)
      continue;
    double Ba = TMath::Sqrt(Bx*Bx+Bz*Bz);
    if (min > Ba) min = Ba;
    if (max < Ba) max = Ba;
    vector_x[num] = x;
    vector_z[num] = z;
    vector_bx[num] = Bx;
    vector_bz[num] = Bz;
    num++;
  }
  fclose(fp);
  printf("num %d min %lf max %lf\n", num, min, max);

  double xmin = 0.0;
  double xmax = 0.95;
  double zmin = 11-z_offset;
  double zmax = 14-z_offset;
  double w = (zmax-zmin)*450;
  double h = (xmax-xmin)*450;
  TCanvas* c1 = new TCanvas("c1", "", w, h);
  TH2F* h0 = new TH2F("h0", fname, 100, zmin, zmax, 100, xmin, xmax);
  h0->SetMinimum(min);
  h0->SetMaximum(max);
  h0->SetContour(20);
  h0->GetXaxis()->SetTitle("Z (m)");
  h0->GetYaxis()->SetTitle("X (m)");
  h0->GetXaxis()->SetTitleSize(0.05);
  h0->GetYaxis()->SetTitleSize(0.05);
  h0->GetYaxis()->SetTitleOffset(0.5);
  h0->Draw();
  TPaletteAxis *pal = new TPaletteAxis(1.5,0.0,1.6,0.95,h0);
  gStyle->SetOptStat(0);
  double scale = 0.1;
  double arrow_size = 0.008;
  for (int i=0; i<num; i++) {
    if (i%200==0) {
    TArrow *a = new TArrow(
        vector_z[i] - z_offset, 
        vector_x[i],
        vector_z[i]  - z_offset+ scale*vector_bz[i], 
        vector_x[i] + scale*vector_bx[i],
        arrow_size);
    a->SetLineWidth(2);
    double Bx = vector_bx[i];
    double Bz = vector_bz[i];
    double Ba = TMath::Sqrt(Bx*Bx+Bz*Bz);
    int col = pal->GetValueColor(Ba);
    a->SetLineColor(col);
    a->Draw();
    }
  }
  pal->Draw();
  c1->RedrawAxis();

  TFrame *frame = c1->GetFrame();
  frame->SetFillColor(kGray+3);

  c1->Print("fielmap.pdf");
}
