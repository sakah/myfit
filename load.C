{
   gInterpreter->AddIncludePath("./genfit-code/fields/include/");
   gInterpreter->AddIncludePath("./genfit-code/measurements/include/");
   gInterpreter->AddIncludePath("./genfit-code/core/include/");
   gInterpreter->AddIncludePath("./genfit-code/trackReps/include/");
   gInterpreter->AddIncludePath("./genfit-code/fitters/include/");
   gInterpreter->AddIncludePath("./genfit-code/eventDisplay/include/");
   gInterpreter->AddIncludePath("./genfit-code/utilities/include/");
   gInterpreter->AddIncludePath("./MyMagField//");
   gSystem->AddLinkedLibs("./genfit-code/build/lib/libgenfit2.2.0.0.dylib");

   gROOT->ProcessLine(".L Util.cc+");
   gROOT->ProcessLine(".L XTCurve.cc+");
   gROOT->ProcessLine(".L WireConfig.cc+");
   gROOT->ProcessLine(".L InitialHit.cc+");
   gROOT->ProcessLine(".L CounterHit.cc+");
   gROOT->ProcessLine(".L CdcHit.cc+");
   gROOT->ProcessLine(".L Hough.cc+");
   gROOT->ProcessLine(".L Circle.cc+");
   gROOT->ProcessLine(".L Fitter.cc+");
   //gROOT->ProcessLine(".L run.cc+");
   //gROOT->ProcessLine(".L test_genfit.cc+");
}

