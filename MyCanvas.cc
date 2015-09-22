#include "MyCanvas.h"
#include "TPaveText.h"

MyCanvas::MyCanvas()
{
}

MyCanvas::MyCanvas(const char* name, const char* title, double wtopx, double wtopy, double ww, double wh)
{
   Setup(name, title, wtopx, wtopy, ww, wh);
}

void MyCanvas::SetTitle(char* title)
{
   fPad1->cd();
   fTitleBar->Clear();
   fTitleBar->AddText(title);
   fTitleBar->Draw();
}

void MyCanvas::Divide(int nx, int ny)
{
   //fCanvas->SetWindowSize(300*nx,300*ny);
   fPad2->cd();
   fPad2->Clear();
   fPad2->Divide(nx,ny);
}

void MyCanvas::cd(int pos)
{
   fPad2->cd(pos);
}

void MyCanvas::Update()
{
   fCanvas->Modified();
   fCanvas->Update();
}

void MyCanvas::Print(char* name)
{
   fCanvas->Print(name);
}

void MyCanvas::Setup(const char* name, const char* title, double wtopx, double wtopy, double ww, double wh)
{
   fCanvas = new TCanvas(name,title,wtopx, wtopy, ww, wh);
   fPad1 = new TPad("pad1","pad1", 0.00, 0.95, 1.00, 1.00); // title
   fPad2 = new TPad("pad2","pad2", 0.00, 0.00, 1.00, 0.95); // body
   fPad1->Draw();
   fPad2->Draw();
   fTitleBar = new TPaveText(0,0,1,1); 
   fTitleBar->SetFillColor(0);
   fTitleBar->SetBorderSize(0);
}
