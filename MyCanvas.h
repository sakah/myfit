#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "TCanvas.h"
#include "TPad.h"
#include "TPaveText.h"

class MyCanvas
{
   public:
      MyCanvas(const char* name, const char* title, double wtopx, double wtopy, double ww, double wh);
      void Divide(int nx, int ny);
      void SetTitle(char* title);
      void cd(int pos);
      void Update();
      void Print(char* name);
   private:
      TCanvas* fCanvas;
      TPad* fPad1;
      TPad* fPad2;
      TPaveText* fTitleBar;
};

#endif
