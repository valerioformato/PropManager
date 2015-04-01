#include <TFile.h>

#include <AnalysisTools.h>

#include <GalpropManager.h>

int main(){

  GalpropManager* mgr = new GalpropManager("test");
  //  mgr->Print();
  mgr->Run();

  // TGraph* b11_lis = AnalysisTools::GetSolarModFlux(mgr->GetFlux(5, 11), 11, 5, 0.2);
  // TGraph* b10_lis = AnalysisTools::GetSolarModFlux(mgr->GetFlux(5, 10), 10, 5, 0.2);
  // TGraph* c_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(6, 12), 12, 6, 0.2);
  // TGraph* o_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(8, 16), 16, 8, 0.2);
  // TFile* test_out = new TFile("test_output.root", "recreate");

  // TGraph* b_flux = new TGraph(*b10_lis);
  // for(int ip=0; ip<b_flux->GetN(); ip++)
  //   b_flux->GetY()[ip] += b11_lis->GetY()[ip];

  // test_out->WriteTObject(b_flux, "b_flux");
  // test_out->WriteTObject(c_flux, "c_flux");
  // test_out->WriteTObject(o_flux, "o_flux");
  // test_out->Close();

}

