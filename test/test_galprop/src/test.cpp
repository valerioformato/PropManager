#include <TFile.h>

#include <AnalysisTools.h>

#include <GalpropManager.h>

int main(){

  TGraph* p_flux, *pbar_flux;

  GalpropManager* mgr = new GalpropManager("example");
  mgr->Run();
  p_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(1, 1), 1, 1, 0.4);
  pbar_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(-1, 1), 1, 1, 0.4);

  TGraph* pbarp_00 = AnalysisTools::DivideGraph(pbar_flux, p_flux);

  mgr->SetBubbleDimension(-1);
  mgr->SetGasDensityFactor(1.1);
  mgr->Print();
  mgr->Run();
  p_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(1, 1), 1, 1, 0.4);
  pbar_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(-1, 1), 1, 1, 0.4);

  TGraph* pbarp_01 = AnalysisTools::DivideGraph(pbar_flux, p_flux);

  // TGraph* b11_lis = AnalysisTools::GetSolarModFlux(mgr->GetFlux(5, 11), 11, 5, 0.2);
  // TGraph* b10_lis = AnalysisTools::GetSolarModFlux(mgr->GetFlux(5, 10), 10, 5, 0.2);
  // TGraph* c_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(6, 12), 12, 6, 0.2);
  // TGraph* o_flux = AnalysisTools::GetSolarModFlux(mgr->GetFlux(8, 16), 16, 8, 0.2);
  TFile* test_out = new TFile("test_output.root", "recreate");

  // TGraph* b_flux = new TGraph(*b10_lis);
  // for(int ip=0; ip<b_flux->GetN(); ip++)
  //   b_flux->GetY()[ip] += b11_lis->GetY()[ip];

  // test_out->WriteTObject(b_flux, "b_flux");
  // test_out->WriteTObject(c_flux, "c_flux");
  // test_out->WriteTObject(o_flux, "o_flux");
  test_out->WriteTObject(pbarp_00, "PbarP_00");
  test_out->WriteTObject(pbarp_01, "PbarP_01");
  test_out->Close();

}

