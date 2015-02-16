#include </storage/gpfs_ams/ams/users/vformato/devel/PropManager/source/GalpropManager/include/GalpropManager.h>

Interface* obj = NULL;

int main(){

  GalpropManager* mgr = new GalpropManager();
  mgr->Print();
  mgr->Run();

  obj = new Interface();


}

Double_t ModelFlux( Double_t x, Double_t delta ){

  if( obj->GetDelta() != delta )
    obj->Run();

  return obj->GetFlux(1, 1)->Eval(;

}
