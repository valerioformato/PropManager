#include <stdlib.h>
#include <DragonManager.h>

#ifndef DEBUG
#define DEBUG 0
#endif

using namespace std;

DragonManager::DragonManager( TString defxml ) : _defxml(defxml){

  fInput = new Input();

  if( InitDefault() )
    cerr << ">>>> ERROR in DragonManager::DragonManager(): Initialization failed! <<<<" << endl;

  fDragon = NULL;

}


DragonManager::~DragonManager(){
  
  system("rm -f ./data");

}


Int_t DragonManager::InitDefault(){

  TString _infile = (TString) DRAGON_XML_PATH + (TString) "/";
  _infile += _defxml;
  _infile += ".xml";

  TString _sourcedata = DRAGON_CONF_PATH;
  _sourcedata += "template.source.param";

  TString _ln_command = Form("ln -s %s .", DRAGON_DATA_PATH);
  system(_ln_command.Data());

  Int_t status = 0;  

  status = fInput->LoadFile( _infile.Data() );
  fInput->sourcedata = _sourcedata.Data();

  fInput->fullstore = false;
  fInput->partialstore = false;

  return status;

}


Int_t DragonManager::Reset(){

  if( InitDefault() )
    cerr << ">>>> ERROR in DragonManager::Reset(): Initialization failed! <<<<" << endl;

  return 0;

}


void DragonManager::Print(){

  fInput->Print();

}


Int_t DragonManager::Run(){

  if( fDragon )
    delete fDragon;

  fDragon = new MyDRAGON( fInput );

  if( DEBUG )
    cout << "DRAGON object constructed" << endl;

  fDragon->Run();

}

TGraph* DragonManager::GetFlux( Int_t Z, Int_t A ){

  if( !Z ) return NULL;
  TList* _flist = new TList();

  TParticle* protons = fDragon->FindParticle(1001, false) ;
  TParticle* electrons = fDragon->FindParticle( -1000, false);
  double pnorm = protons->FindNormalization(fInput->sp_ref_rig_norm, fInput->spect_norm);
  double enorm = electrons->FindNormalization(fInput->sp_ref_rig_el, fInput->spect_norm_el);

  int pid = 1000*Z + A;
  std::cout << "Retrieving particle flux: Z=" << Z << " A=" << A << " Uid=" << pid << std::endl; 
  //  TParticle* thisparticle = fDragon->FindParticle( pid, false);

  vector<double> eKin = fDragon->GetEnergyGrid();
  int n_points = eKin.size();

  vector<TParticle*> particles = fDragon->GetParticles();
  int i=0;
  for(int ipart=0; ipart<particles.size(); ipart++){

    if(particles[ipart]->GetUid() != pid) continue;
    
    // if(DEBUG)
    //   cout << " -- DragonManager::GetFlux() :  Found flux for (" << Z << "," << A << ") at index " << ipart << endl;

    TGraph* temp_graph = new TGraph( n_points );

    double flux=0;
    for(int ip=0; ip<eKin.size(); ip++){
      if(A)
	flux = pnorm * particles[ipart]->GetFluxAtSunPosition(ip);
      else
	flux = enorm * particles[ipart]->GetFluxAtSunPosition(ip);
      
      temp_graph->SetPoint(ip, eKin[ip], flux);
    }

    _flist->Add(temp_graph); 

  }


  //All fluxes added to the list now sum them up!
  TGraph* tot_flux = new TGraph( n_points );
  for(Int_t ipt=0; ipt<n_points; ipt++){
    tot_flux->GetX()[ipt] = ((TGraph*) _flist->At(0))->GetX()[ipt];  //1e-3 = conversion factor between MeV and GeV

    for(Int_t ngraph=0; ngraph<_flist->GetEntries(); ngraph++)
      tot_flux->GetY()[ipt] += ((TGraph*) _flist->At(ngraph))->GetY()[ipt];  //1e7 = conversion factor between (MeV/n cm^2 s sr)^-1 and (GeV/n m^2 s sr)^-1

  }

  delete _flist;
  return tot_flux;

}
