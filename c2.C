{
//=========Macro generated from canvas: c2/c2
//=========  (Tue Sep 22 01:49:41 2015) by ROOT version5.34/18
   TCanvas *c2 = new TCanvas("c2", "c2",601,45,600,600);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "pad1",0,0.95,1,1);
   pad1->Draw();
   pad1->cd();
   pad1->Range(0,0,1,1);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetFrameBorderMode(0);
   
   TPaveText *pt = new TPaveText(0,0,1,1,"br");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   TText *text = pt->AddText("iev 10");
   pt->Draw();
   pad1->Modified();
   c2->cd();
  
// ------------>Primitives in pad: pad2
   pad2 = new TPad("pad2", "pad2",0,0,1,0.95);
   pad2->Draw();
   pad2->cd();
   pad2->Range(0,0,1,1);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad2_1
   pad2_1 = new TPad("pad2_1", "pad2_1",0.01,0.51,0.49,0.99);
   pad2_1->Draw();
   pad2_1->cd();
   pad2_1->Range(-125,-125,125,125);
   pad2_1->SetFillColor(0);
   pad2_1->SetBorderMode(0);
   pad2_1->SetBorderSize(2);
   pad2_1->SetFrameBorderMode(0);
   pad2_1->SetFrameBorderMode(0);
   
   TH2F *c1 = new TH2F("c1","",100,-100,100,100,-100,100);
   c1->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   c1->SetLineColor(ci);
   c1->GetXaxis()->SetTitle("X(cm)");
   c1->GetXaxis()->SetLabelFont(42);
   c1->GetXaxis()->SetLabelSize(0.035);
   c1->GetXaxis()->SetTitleSize(0.035);
   c1->GetXaxis()->SetTitleFont(42);
   c1->GetYaxis()->SetTitle("Y(cm)");
   c1->GetYaxis()->SetLabelFont(42);
   c1->GetYaxis()->SetLabelSize(0.035);
   c1->GetYaxis()->SetTitleSize(0.035);
   c1->GetYaxis()->SetTitleFont(42);
   c1->GetZaxis()->SetLabelFont(42);
   c1->GetZaxis()->SetLabelSize(0.035);
   c1->GetZaxis()->SetTitleSize(0.035);
   c1->GetZaxis()->SetTitleFont(42);
   c1->Draw("");
   
   TEllipse *ellipse = new TEllipse(0,0,53,53,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,56.2,56.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,59.4,59.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,62.6,62.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,65.8,65.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,69,69,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,72.2,72.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,75.4,75.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,78.6,78.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,81.8,81.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(52.19481,9.203373,0.7798077,0.7798077,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.87653,10.85477,0.545661,0.545661,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.50601,12.49524,0.9255945,0.9255945,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.08363,14.12313,0.3676029,0.3676029,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(14.93181,50.85313,0.7529406,0.7529406,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(13.31082,51.30129,1.578516,1.578516,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-47.48768,23.53551,0.6057289,0.6057289,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-48.2105,22.01698,0.3011108,0.3011108,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-48.88479,20.47627,1.195208,1.195208,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-52.93997,2.521822,0.5610504,0.5610504,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-52.99333,0.8408765,0.3667281,0.3667281,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-52.99333,-0.8409157,0.6942134,0.6942134,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-37.77278,-37.17818,0.8902511,0.8902511,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-36.57417,-38.35792,0.6021811,0.6021811,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0.8407187,56.19371,0.1956263,0.1956263,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-0.8407187,56.19371,1.017119,1.017119,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-2.521403,56.14341,0.6635211,0.6635211,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-4.199831,56.04285,0.5282726,0.5282726,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-53.1836,18.16438,1.154085,1.154085,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-53.70319,16.56524,0.7045553,0.7045553,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(56.00692,19.7885,0.6576904,0.6576904,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(55.4245,21.36551,0.4772472,0.4772472,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(5.8745,59.1088,1.015912,1.015912,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(4.199435,59.25137,0.1306584,0.1306584,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0.8405602,59.39405,0.4247053,0.4247053,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-0.8405602,59.39405,0.7608164,0.7608164,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-29.7,-51.44191,1.558358,1.558358,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-28.23236,-52.26178,0.6911633,0.6911633,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-26.7421,-53.0398,0.1867167,0.1867167,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.10689,20.61882,0.1757442,0.1757442,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.53201,22.19829,0.8673097,0.8673097,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.91493,23.76175,0.9647798,0.9647798,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.2561,25.30809,0.044971,0.044971,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(10.04172,61.78935,0.7034443,0.7034443,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(8.379182,62.03668,0.3129388,0.3129388,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(5.037183,62.39701,0.1795375,0.1795375,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(3.360133,62.50976,0.8169096,0.8169096,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(1.68066,62.57744,0.05385389,0.05385389,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-2.443712e-05,62.6,0.7713735,0.7713735,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-60.9766,-14.16384,1.27704,1.27704,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-60.57435,-15.79583,0.7467454,0.7467454,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.71056,25.37455,0.2576497,0.2576497,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.04273,26.91673,0.6316431,0.6316431,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.59002,29.94744,0.312877,0.312877,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.8061,31.43398,0.5421976,0.5421976,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(14.99274,64.06916,0.3973545,0.3973545,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(13.35161,64.43116,0.5164097,0.5164097,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(11.70178,64.75113,0.7900741,0.7900741,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(10.0443,65.02885,0.0663368,0.0663368,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.11467,30.04609,0.9019551,0.9019551,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(61.3646,31.54974,0.1143194,0.1143194,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.57813,33.03467,0.2195296,0.2195296,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.75574,34.50002,0.6788678,0.6788678,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.89791,35.9449,0.4316064,0.4316064,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.00515,37.36847,0.2621535,0.2621535,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(21.4819,65.57078,0.4134758,0.4134758,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(19.87882,66.07445,0.4331795,0.4331795,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(18.26394,66.53892,0.5811898,0.5811898,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(16.63824,66.96394,0.1443359,0.1443359,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(15.00266,67.34924,0.8927832,0.8927832,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(61.67008,37.54519,0.7495274,0.7495274,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.77974,38.97003,0.1140361,0.1140361,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.85649,40.37376,0.437303,0.437303,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.91327,43.11488,0.7029429,0.7029429,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(56.89436,44.45079,0.1450167,0.1450167,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(55.84463,45.76262,0.3574144,0.3574144,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.76466,47.04968,0.8291782,0.8291782,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(30.89318,65.25681,0.4432672,0.4432672,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(29.36635,65.958,0.1391687,0.1391687,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(27.82363,66.62346,0.4895831,0.4895831,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(26.26584,67.25285,0.1369852,0.1369852,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(24.69382,67.84582,0.4072525,0.4072525,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-29.36642,65.95797,1.531631,1.531631,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-30.89324,65.25678,0.415411,0.415411,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-32.40333,64.52026,0.6421519,0.6421519,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-57.91327,-43.11488,0.05775988,0.05775988,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-56.89436,-44.45079,0.6407779,0.6407779,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-46.40924,-55.30843,0.2667551,0.2667551,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-45.1097,-56.37335,0.8333573,0.8333573,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.0335,49.31876,0.5548378,0.5548378,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(55.92057,50.57717,0.2533738,0.2533738,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.77988,51.81047,0.02235343,0.02235343,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(53.612,53.01805,0.2380029,0.2380029,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(52.41751,54.19931,0.4340973,0.4340973,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.19699,55.35366,0.5618487,0.5618487,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(49.95107,56.48054,0.4726313,0.4726313,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(48.68034,57.57938,0.2818154,0.2818154,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(47.38545,58.64963,0.177587,0.177587,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(46.06703,59.69077,0.08623272,0.08623272,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(44.72575,60.70228,0.0420276,0.0420276,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(43.36227,61.68366,0.03359842,0.03359842,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(41.97726,62.63441,0.1003966,0.1003966,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(40.57141,63.55408,0.03277224,0.03277224,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(39.14542,64.44219,0.2288339,0.2288339,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(37.7,65.29832,0.4258492,0.4258492,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(36.23586,66.12202,0.6869795,0.6869795,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(35.60882,-70.07119,1.473461,1.473461,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(37.09809,-69.29424,1.32512,1.32512,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(38.57042,-68.48564,0.9185196,0.9185196,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(75.3513,-22.36384,0.4409491,0.4409491,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(75.812,-20.7485,0.9860172,0.9860172,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(44.48099,68.64897,0.6477576,0.6477576,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(43.06213,69.54778,0.4928152,0.4928152,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(10.05223,81.18,0.59944,0.59944,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(8.383339,81.36928,1.302144,1.302144,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-81.7612,-2.519065,1.284769,1.284769,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-81.69225,-4.197242,0.2040686,0.2040686,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-73.95753,-34.95031,1.456837,1.456837,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-73.22434,-36.46142,0.5234794,0.5234794,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-13.37661,-80.69886,0.4599566,0.4599566,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-11.71689,-80.9565,1.597307,1.597307,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-10.05223,-81.18,1.303209,1.303209,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   pad2_1->Modified();
   pad2->cd();
  
// ------------>Primitives in pad: pad2_2
   pad2_2 = new TPad("pad2_2", "pad2_2",0.51,0.51,0.99,0.99);
   pad2_2->Draw();
   pad2_2->cd();
   pad2_2->Range(-125,-125,125,125);
   pad2_2->SetFillColor(0);
   pad2_2->SetBorderMode(0);
   pad2_2->SetBorderSize(2);
   pad2_2->SetFrameBorderMode(0);
   pad2_2->SetFrameBorderMode(0);
   
   TH2F *c2 = new TH2F("c2","",100,-100,100,100,-100,100);
   c2->SetStats(0);

   ci = TColor::GetColor("#000099");
   c2->SetLineColor(ci);
   c2->GetXaxis()->SetTitle("X(cm)");
   c2->GetXaxis()->SetLabelFont(42);
   c2->GetXaxis()->SetLabelSize(0.035);
   c2->GetXaxis()->SetTitleSize(0.035);
   c2->GetXaxis()->SetTitleFont(42);
   c2->GetYaxis()->SetTitle("Y(cm)");
   c2->GetYaxis()->SetLabelFont(42);
   c2->GetYaxis()->SetLabelSize(0.035);
   c2->GetYaxis()->SetTitleSize(0.035);
   c2->GetYaxis()->SetTitleFont(42);
   c2->GetZaxis()->SetLabelFont(42);
   c2->GetZaxis()->SetLabelSize(0.035);
   c2->GetZaxis()->SetTitleSize(0.035);
   c2->GetZaxis()->SetTitleFont(42);
   c2->Draw("");
   
   ellipse = new TEllipse(0,0,53,53,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,56.2,56.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,59.4,59.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,62.6,62.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,65.8,65.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,69,69,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,72.2,72.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,75.4,75.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,78.6,78.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,81.8,81.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-41.39089,30.47547,1.271325,1.271325,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-42.33698,29.14688,0.8113279,0.8113279,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-36.05581,-36.63248,1.11579,1.11579,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-34.87538,-37.75801,0.4298402,0.4298402,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.59353,0.8408068,0.1893581,0.1893581,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(29.45465,45.97373,1.195811,1.195811,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(28.02492,46.85898,1.17769,1.17769,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(18.93743,51.21068,0.7555019,0.7555019,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(17.35141,51.76957,0.597511,0.597511,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(10.85802,53.50947,0.8435625,0.8435625,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(9.205044,53.81846,0.404696,0.404696,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.07641,-7.543335,0.4055025,0.4055025,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.28306,-5.874471,0.9677353,0.9677353,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.43822,-4.200035,0.2698424,0.2698424,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.59353,-0.8408028,1.016629,1.016629,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(22.11912,53.40023,0.7838916,0.7838916,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(20.55664,54.02097,0.4693744,0.4693744,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(18.97676,54.596,1.016594,1.016594,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(14.14619,56.04217,0.7889222,0.7889222,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(12.51023,56.4299,0.345129,0.345129,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-23.6629,-52.73431,0.407101,0.407101,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-22.11912,-53.40023,1.415946,1.415946,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.74499,-2.521224,0.8947721,0.8947721,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.79389,-0.840661,0.2978762,0.2978762,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.97684,1.680815,0.6177454,0.6177454,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.90737,3.360353,0.4377767,0.4377767,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.42185,8.378567,0.1762473,0.1762473,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.16804,10.04027,0.7994129,0.7994129,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.52358,13.33955,0.800059,0.800059,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.13342,14.97461,0.468807,0.468807,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.69835,16.59831,1.449177,1.449177,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(26.03336,55.16579,0.89001,0.89001,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(24.50342,55.86217,0.2249767,0.2249767,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(18.2094,58.21871,0.8867204,0.8867204,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(16.59831,58.69835,0.1754558,0.1754558,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-52.82755,30.5,1.426938,1.426938,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-53.6479,29.03279,1.548216,1.548216,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.84831,6.710727,0.4415889,0.4415889,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.65076,8.379782,0.567283,0.567283,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.79708,13.34793,0.3361858,0.3361858,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.42615,14.98719,0.5779419,0.5779419,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(29.14619,57.20262,0.028668,0.028668,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(27.63881,57.94598,0.9918367,0.9918367,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(24.56828,59.31307,0.3313303,0.3313303,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(23.00722,59.93586,0.8704479,0.8704479,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(21.4304,60.51758,0.08022357,0.08022357,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(8.379782,63.65076,0.7336813,0.7336813,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(6.710727,63.84831,1.489031,1.489031,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-24.56828,-59.31307,0.7697467,0.7697467,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-23.00722,-59.93586,0.5437213,0.5437213,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-21.4304,-60.51758,0.8270361,0.8270361,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(66.37604,11.70389,0.7060441,0.7060441,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(66.06363,13.35505,0.1343826,0.1343826,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(64.40561,19.8665,0.149443,0.149443,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.8903,21.466,0.6574513,0.6574513,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(35.14473,57.51181,0.5758823,0.5758823,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(33.7,58.37011,0.2977013,0.2977013,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(27.72075,61.43549,0.2263328,0.2263328,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(26.18051,62.1075,0.540575,0.540575,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-16.63145,-65.31581,1.086741,1.086741,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-14.99791,-65.71014,0.8206002,0.8206002,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(68.19436,18.27262,0.8018373,0.8018373,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.7402,19.89032,0.09854025,0.09854025,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.24768,21.49675,0.5845476,0.5845476,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(65.54278,26.23937,0.6977237,0.6977237,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(64.89978,27.79171,0.06697205,0.06697205,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(64.22002,29.3283,0.5628907,0.5628907,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(42.309,56.51821,0.1507528,0.1507528,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(40.95202,57.50906,0.2314115,0.2314115,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(39.57184,58.46734,0.4898608,0.4898608,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(35.3,61.14139,0.3312641,0.3312641,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(33.83498,61.96414,0.2224038,0.2224038,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-36.74503,60.28402,0.4683625,0.4683625,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-38.16924,59.3925,0.6619052,0.6619052,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-70.42012,-5.036546,1.373779,1.373779,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-70.28032,-6.710957,1.516066,1.516066,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(68.34194,27.85354,0.5809173,0.5809173,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.69019,29.402,0.1138322,0.1138322,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.00337,30.93523,0.3343506,0.3343506,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(66.28182,32.45242,0.7262168,0.7262168,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.91267,36.9,0.5139358,0.5139358,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.05615,38.3453,0.1107746,0.1107746,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.16695,39.77072,0.2598863,0.2598863,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(61.24553,41.17553,0.5618782,0.5618782,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(50.37242,53.93569,0.5630015,0.5630015,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(49.13162,55.06836,0.1555924,0.1555924,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(47.86536,56.17248,0.3620322,0.3620322,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(46.57429,57.24749,0.5565977,0.5565977,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(45.25909,58.29284,0.22244,0.22244,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(43.92043,59.30798,0.165443,0.165443,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(42.55901,60.29238,0.513952,0.513952,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-73.32243,-8.382218,0.7971501,0.7971501,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-73.11262,-10.0491,0.07005417,0.07005417,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-62.16695,-39.77072,0.1287682,0.1287682,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-61.24553,-41.17553,0.2415186,0.2415186,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-47.86536,-56.17248,0.8434563,0.8434563,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-46.57429,-57.24749,0.4609273,0.4609273,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(66.68396,-38.5,1.505356,1.505356,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.50796,-37.03614,0.9797157,0.9797157,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(73.93342,31.07875,1.07466,1.07466,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(73.26635,32.62028,1.410466,1.410466,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(44.382,66.80028,0.6734769,0.6734769,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(42.97331,67.7151,0.6178408,0.6178408,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   pad2_2->Modified();
   pad2->cd();
  
// ------------>Primitives in pad: pad2_3
   pad2_3 = new TPad("pad2_3", "pad2_3",0.01,0.01,0.49,0.49);
   pad2_3->Draw();
   pad2_3->cd();
   pad2_3->Range(-125,-125,125,125);
   pad2_3->SetFillColor(0);
   pad2_3->SetBorderMode(0);
   pad2_3->SetBorderSize(2);
   pad2_3->SetFrameBorderMode(0);
   pad2_3->SetFrameBorderMode(0);
   
   TH2F *c3 = new TH2F("c3","",100,-100,100,100,-100,100);
   c3->SetStats(0);

   ci = TColor::GetColor("#000099");
   c3->SetLineColor(ci);
   c3->GetXaxis()->SetTitle("X(cm)");
   c3->GetXaxis()->SetLabelFont(42);
   c3->GetXaxis()->SetLabelSize(0.035);
   c3->GetXaxis()->SetTitleSize(0.035);
   c3->GetXaxis()->SetTitleFont(42);
   c3->GetYaxis()->SetTitle("Y(cm)");
   c3->GetYaxis()->SetLabelFont(42);
   c3->GetYaxis()->SetLabelSize(0.035);
   c3->GetYaxis()->SetTitleSize(0.035);
   c3->GetYaxis()->SetTitleFont(42);
   c3->GetZaxis()->SetLabelFont(42);
   c3->GetZaxis()->SetLabelSize(0.035);
   c3->GetZaxis()->SetTitleSize(0.035);
   c3->GetZaxis()->SetTitleFont(42);
   c3->Draw("");
   
   ellipse = new TEllipse(0,0,53,53,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,56.2,56.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,59.4,59.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,62.6,62.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,65.8,65.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,69,69,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,72.2,72.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,75.4,75.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,78.6,78.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,81.8,81.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(52.19481,9.203373,0.7798077,0.7798077,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.87653,10.85477,0.545661,0.545661,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.50601,12.49524,0.9255945,0.9255945,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.08363,14.12313,0.3676029,0.3676029,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0.8407187,56.19371,0.1956263,0.1956263,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-0.8407187,56.19371,1.017119,1.017119,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-2.521403,56.14341,0.6635211,0.6635211,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-4.199831,56.04285,0.5282726,0.5282726,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(56.00692,19.7885,0.6576904,0.6576904,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(55.4245,21.36551,0.4772472,0.4772472,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(5.8745,59.1088,1.015912,1.015912,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(4.199435,59.25137,0.1306584,0.1306584,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0.8405602,59.39405,0.4247053,0.4247053,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-0.8405602,59.39405,0.7608164,0.7608164,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.10689,20.61882,0.1757442,0.1757442,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.53201,22.19829,0.8673097,0.8673097,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.91493,23.76175,0.9647798,0.9647798,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.2561,25.30809,0.044971,0.044971,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(10.04172,61.78935,0.7034443,0.7034443,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(8.379182,62.03668,0.3129388,0.3129388,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(5.037183,62.39701,0.1795375,0.1795375,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(3.360133,62.50976,0.8169096,0.8169096,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(1.68066,62.57744,0.05385389,0.05385389,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(-2.443712e-05,62.6,0.7713735,0.7713735,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.71056,25.37455,0.2576497,0.2576497,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.04273,26.91673,0.6316431,0.6316431,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.59002,29.94744,0.312877,0.312877,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.8061,31.43398,0.5421976,0.5421976,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(14.99274,64.06916,0.3973545,0.3973545,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(13.35161,64.43116,0.5164097,0.5164097,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(11.70178,64.75113,0.7900741,0.7900741,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(10.0443,65.02885,0.0663368,0.0663368,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.11467,30.04609,0.9019551,0.9019551,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(61.3646,31.54974,0.1143194,0.1143194,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.57813,33.03467,0.2195296,0.2195296,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.75574,34.50002,0.6788678,0.6788678,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.89791,35.9449,0.4316064,0.4316064,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.00515,37.36847,0.2621535,0.2621535,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(21.4819,65.57078,0.4134758,0.4134758,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(19.87882,66.07445,0.4331795,0.4331795,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(18.26394,66.53892,0.5811898,0.5811898,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(16.63824,66.96394,0.1443359,0.1443359,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(15.00266,67.34924,0.8927832,0.8927832,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(61.67008,37.54519,0.7495274,0.7495274,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.77974,38.97003,0.1140361,0.1140361,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.85649,40.37376,0.437303,0.437303,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.91327,43.11488,0.7029429,0.7029429,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(56.89436,44.45079,0.1450167,0.1450167,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(55.84463,45.76262,0.3574144,0.3574144,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.76466,47.04968,0.8291782,0.8291782,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(30.89318,65.25681,0.4432672,0.4432672,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(29.36635,65.958,0.1391687,0.1391687,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(27.82363,66.62346,0.4895831,0.4895831,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(26.26584,67.25285,0.1369852,0.1369852,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(24.69382,67.84582,0.4072525,0.4072525,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.0335,49.31876,0.5548378,0.5548378,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(55.92057,50.57717,0.2533738,0.2533738,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.77988,51.81047,0.02235343,0.02235343,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(53.612,53.01805,0.2380029,0.2380029,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(52.41751,54.19931,0.4340973,0.4340973,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(51.19699,55.35366,0.5618487,0.5618487,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(49.95107,56.48054,0.4726313,0.4726313,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(48.68034,57.57938,0.2818154,0.2818154,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(47.38545,58.64963,0.177587,0.177587,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(46.06703,59.69077,0.08623272,0.08623272,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(44.72575,60.70228,0.0420276,0.0420276,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(43.36227,61.68366,0.03359842,0.03359842,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(41.97726,62.63441,0.1003966,0.1003966,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(40.57141,63.55408,0.03277224,0.03277224,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(39.14542,64.44219,0.2288339,0.2288339,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(37.7,65.29832,0.4258492,0.4258492,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(36.23586,66.12202,0.6869795,0.6869795,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(44.48099,68.64897,0.6477576,0.6477576,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(43.06213,69.54778,0.4928152,0.4928152,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(24.77576,32.87898,34.93417,34.93417,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   pad2_3->Modified();
   pad2->cd();
  
// ------------>Primitives in pad: pad2_4
   pad2_4 = new TPad("pad2_4", "pad2_4",0.51,0.01,0.99,0.49);
   pad2_4->Draw();
   pad2_4->cd();
   pad2_4->Range(-125,-125,125,125);
   pad2_4->SetFillColor(0);
   pad2_4->SetBorderMode(0);
   pad2_4->SetBorderSize(2);
   pad2_4->SetFrameBorderMode(0);
   pad2_4->SetFrameBorderMode(0);
   
   TH2F *c4 = new TH2F("c4","",100,-100,100,100,-100,100);
   c4->SetStats(0);

   ci = TColor::GetColor("#000099");
   c4->SetLineColor(ci);
   c4->GetXaxis()->SetTitle("X(cm)");
   c4->GetXaxis()->SetLabelFont(42);
   c4->GetXaxis()->SetLabelSize(0.035);
   c4->GetXaxis()->SetTitleSize(0.035);
   c4->GetXaxis()->SetTitleFont(42);
   c4->GetYaxis()->SetTitle("Y(cm)");
   c4->GetYaxis()->SetLabelFont(42);
   c4->GetYaxis()->SetLabelSize(0.035);
   c4->GetYaxis()->SetTitleSize(0.035);
   c4->GetYaxis()->SetTitleFont(42);
   c4->GetZaxis()->SetLabelFont(42);
   c4->GetZaxis()->SetLabelSize(0.035);
   c4->GetZaxis()->SetTitleSize(0.035);
   c4->GetZaxis()->SetTitleFont(42);
   c4->Draw("");
   
   ellipse = new TEllipse(0,0,53,53,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,56.2,56.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,59.4,59.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,62.6,62.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,65.8,65.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,69,69,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,72.2,72.2,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,75.4,75.4,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,78.6,78.6,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(0,0,81.8,81.8,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#cccccc");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.59353,0.8408068,0.1893581,0.1893581,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(17.35141,51.76957,0.597511,0.597511,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(10.85802,53.50947,0.8435625,0.8435625,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(9.205044,53.81846,0.404696,0.404696,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.07641,-7.543335,0.4055025,0.4055025,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.28306,-5.874471,0.9677353,0.9677353,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.43822,-4.200035,0.2698424,0.2698424,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(54.59353,-0.8408028,1.016629,1.016629,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(22.11912,53.40023,0.7838916,0.7838916,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(20.55664,54.02097,0.4693744,0.4693744,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(18.97676,54.596,1.016594,1.016594,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(14.14619,56.04217,0.7889222,0.7889222,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(12.51023,56.4299,0.345129,0.345129,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.74499,-2.521224,0.8947721,0.8947721,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(57.79389,-0.840661,0.2978762,0.2978762,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.97684,1.680815,0.6177454,0.6177454,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.90737,3.360353,0.4377767,0.4377767,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.42185,8.378567,0.1762473,0.1762473,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(60.16804,10.04027,0.7994129,0.7994129,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.52358,13.33955,0.800059,0.800059,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(59.13342,14.97461,0.468807,0.468807,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(58.69835,16.59831,1.449177,1.449177,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(26.03336,55.16579,0.89001,0.89001,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(24.50342,55.86217,0.2249767,0.2249767,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(18.2094,58.21871,0.8867204,0.8867204,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(16.59831,58.69835,0.1754558,0.1754558,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.84831,6.710727,0.4415889,0.4415889,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.65076,8.379782,0.567283,0.567283,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.79708,13.34793,0.3361858,0.3361858,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.42615,14.98719,0.5779419,0.5779419,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(29.14619,57.20262,0.028668,0.028668,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(27.63881,57.94598,0.9918367,0.9918367,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(24.56828,59.31307,0.3313303,0.3313303,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(23.00722,59.93586,0.8704479,0.8704479,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(21.4304,60.51758,0.08022357,0.08022357,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(8.379782,63.65076,0.7336813,0.7336813,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(6.710727,63.84831,1.489031,1.489031,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(66.37604,11.70389,0.7060441,0.7060441,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(66.06363,13.35505,0.1343826,0.1343826,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(64.40561,19.8665,0.149443,0.149443,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.8903,21.466,0.6574513,0.6574513,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(35.14473,57.51181,0.5758823,0.5758823,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(33.7,58.37011,0.2977013,0.2977013,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(27.72075,61.43549,0.2263328,0.2263328,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(26.18051,62.1075,0.540575,0.540575,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(68.19436,18.27262,0.8018373,0.8018373,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.7402,19.89032,0.09854025,0.09854025,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.24768,21.49675,0.5845476,0.5845476,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(65.54278,26.23937,0.6977237,0.6977237,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(64.89978,27.79171,0.06697205,0.06697205,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(64.22002,29.3283,0.5628907,0.5628907,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(42.309,56.51821,0.1507528,0.1507528,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(40.95202,57.50906,0.2314115,0.2314115,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(39.57184,58.46734,0.4898608,0.4898608,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(35.3,61.14139,0.3312641,0.3312641,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(33.83498,61.96414,0.2224038,0.2224038,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(68.34194,27.85354,0.5809173,0.5809173,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.69019,29.402,0.1138322,0.1138322,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(67.00337,30.93523,0.3343506,0.3343506,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(66.28182,32.45242,0.7262168,0.7262168,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.91267,36.9,0.5139358,0.5139358,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(63.05615,38.3453,0.1107746,0.1107746,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(62.16695,39.77072,0.2598863,0.2598863,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(61.24553,41.17553,0.5618782,0.5618782,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(50.37242,53.93569,0.5630015,0.5630015,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(49.13162,55.06836,0.1555924,0.1555924,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(47.86536,56.17248,0.3620322,0.3620322,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(46.57429,57.24749,0.5565977,0.5565977,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(45.25909,58.29284,0.22244,0.22244,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(43.92043,59.30798,0.165443,0.165443,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(42.55901,60.29238,0.513952,0.513952,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(73.93342,31.07875,1.07466,1.07466,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(73.26635,32.62028,1.410466,1.410466,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(44.382,66.80028,0.6734769,0.6734769,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(42.97331,67.7151,0.6178408,0.6178408,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#00ffff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   
   ellipse = new TEllipse(30.64127,24.54128,36.01819,36.01819,0,360,0);
   ellipse->SetFillStyle(0);

   ci = TColor::GetColor("#0000ff");
   ellipse->SetLineColor(ci);
   ellipse->Draw();
   pad2_4->Modified();
   pad2->cd();
   pad2->Modified();
   c2->cd();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
