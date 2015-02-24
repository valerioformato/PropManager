#include <TFile.h>

#include <DragonManager.h>

int main(){

  DragonManager* mgr = new DragonManager();
  mgr->Print();
  mgr->Run();

  TGraph* prot_lis = mgr->GetFlux(1, 1);
  TFile* test_out = new TFile("test_output.root", "recreate");
  test_out->WriteTObject(prot_lis, "p_flux");
  test_out->Close();

}

