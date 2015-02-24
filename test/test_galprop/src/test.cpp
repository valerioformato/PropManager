#include <TFile.h>

#include <GalpropManager.h>

int main(){

  GalpropManager* mgr = new GalpropManager("test");
  mgr->Print();
  mgr->Run();

  TGraph* prot_lis = mgr->GetFlux(1, 1);
  TFile* test_out = new TFile("test_output.root", "recreate");
  test_out->WriteTObject(prot_lis, "p_flux");
  test_out->Close();

}

