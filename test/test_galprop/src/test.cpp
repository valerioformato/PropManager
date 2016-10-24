#include <TFile.h>

#include <AnalysisTools.h>

#include <GalpropManager.h>

int main(){

  GalpropManager* mgr = new GalpropManager("test");
  mgr->Run();

  TGraph* he3_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(2, 3) , 3, 2, 0.4);
  TGraph* he4_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(2, 4) , 4, 2, 0.4);
  TGraph* li6_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(3, 6) , 6, 3, 0.4);
  TGraph* li7_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(3, 7) , 7, 3, 0.4);
  TGraph* be7_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(4, 7) , 7, 4, 0.4);
  TGraph* be9_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(4, 9) , 9, 4, 0.4);
  TGraph* be10_lis = AnalysisTools::GetSolarModFlux(mgr->GetFlux(4, 10), 10, 4, 0.4);
  TGraph* b11_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(5, 11), 11, 5, 0.4);
  TGraph* b10_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(5, 10), 10, 5, 0.4);
  TGraph* c_flux   = AnalysisTools::GetSolarModFlux(mgr->GetFlux(6, 12), 12, 6, 0.4);
  TGraph* n14_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(7, 14), 14, 7, 0.4);
  TGraph* n15_lis  = AnalysisTools::GetSolarModFlux(mgr->GetFlux(7, 15), 15, 7, 0.4);
  TGraph* o_flux   = AnalysisTools::GetSolarModFlux(mgr->GetFlux(8, 16), 16, 8, 0.4);
  TFile* test_out = new TFile("test_output.root", "recreate");

  TGraph* he_flux = new TGraph(*he3_lis);
  for(int ip=0; ip<he_flux->GetN(); ip++)
    he_flux->GetY()[ip] += he4_lis->GetY()[ip];

  TGraph* li_flux = new TGraph(*li6_lis);
  for(int ip=0; ip<li_flux->GetN(); ip++)
    li_flux->GetY()[ip] += li7_lis->GetY()[ip];

  TGraph* be_flux = new TGraph(*be7_lis);
  for(int ip=0; ip<be_flux->GetN(); ip++){
    be_flux->GetY()[ip] += be9_lis->GetY()[ip];
    be_flux->GetY()[ip] += be10_lis->GetY()[ip];
  }

  TGraph* b_flux = new TGraph(*b10_lis);
  for(int ip=0; ip<b_flux->GetN(); ip++)
    b_flux->GetY()[ip] += b11_lis->GetY()[ip];

  TGraph* n_flux = new TGraph(*n14_lis);
  for(int ip=0; ip<n_flux->GetN(); ip++)
    n_flux->GetY()[ip] += n15_lis->GetY()[ip];

  test_out->WriteTObject(he_flux, "he_flux");
  test_out->WriteTObject(li_flux, "li_flux");
  test_out->WriteTObject(be_flux, "be_flux");
  test_out->WriteTObject(b_flux , "b_flux");
  test_out->WriteTObject(c_flux , "c_flux");
  test_out->WriteTObject(n_flux , "n_flux");
  test_out->WriteTObject(o_flux , "o_flux");
  // test_out->WriteTObject(pbarp_00, "PbarP_00");
  // test_out->WriteTObject(pbarp_01, "PbarP_01");
  test_out->Close();

}

