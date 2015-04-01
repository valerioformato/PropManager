#include <GalpropManager.h>

#ifndef DEBUG
#define DEBUG 1
#endif

#define str2(s) #s
#define str(s) str2(s)

#ifndef GALPROP_MAIN_V
#ifdef VERSION
#define GALPROP_MAIN_V floor(VERSION)
#endif
#endif

GalpropManager::GalpropManager( TString defgal ){

  firstrun = kTRUE;
  _default_galdef = defgal;
  fGalprop = new Galprop();
  fGaldef = &(fGalprop->galdef);

  if(InitDefault())
    cerr << ">>>> ERROR in GalpropManager::GalpropManager(): Initialization failed! <<<<" << endl;

}

GalpropManager::~GalpropManager(){
}

Int_t GalpropManager::Reset(){
  
  if( fGalprop ){
    cerr << "Warning, deleting fGalprop" << endl;
    delete fGalprop;
  }
  cerr << "Recreating fGalprop" << endl;
  fGalprop = new Galprop();
  fGaldef = &(fGalprop->galdef);

  if(InitDefault())
    cerr << ">>>> ERROR in GalpropManager::Reset(): Initialization failed! <<<<" << endl;

  return 0;

}

void GalpropManager::Print(){
  fGaldef->print();
}

Int_t GalpropManager::InitDefault(){

  if(DEBUG){
    cout << "fGalprop object at " << fGalprop << endl;
    cout << "fGaldef object at "  << fGaldef  << endl;
    cout << "Configuring paths  "  << endl;
    cout << " -- galdef path: " << GALDEF_PATH << endl;
    cout << " -- FITS   path: " << FITS_PATH << endl;
  }

//   gp::Configure& configure = fGalprop->configure;
//   configure.fGaldefDirectory = GALDEF_PATH;
//   configure.fFITSDataDirectory = FITS_PATH;
//   fGalprop->configure = configure;
  gp::Configure* configure = &(fGalprop->configure);
  configure->fGaldefDirectory = GALDEF_PATH;
  configure->fFITSDataDirectory = FITS_PATH;

  TString galdef_path = ((TString) GALDEF_PATH) + "/";


  string ver = str(GALPROP_MAIN_V); 
  if( fGaldef->read( ver, _default_galdef.Data(), galdef_path.Data()) ){
    cerr << ">>>> ERROR in GalpropManager::InitDefault(): Initialization failed! <<<<" << endl;
    return 1;
  }

  read_nucdata( GALPROP_DATA_PATH );          //Reading nuclear data
#if GALPROP_MAIN_V > 54
  processes::sigtap_cc( -1, GALPROP_DATA_PATH );         //Initialization of the Barashenkov & Polanski cross section code
  nuclei::set_sigma_cc( GALPROP_DATA_PATH );          //initialization of the Webber's routine
#else
  sigtap_cc( -1, GALPROP_DATA_PATH );         //Initialization of the Barashenkov & Polanski cross section code
  set_sigma_cc( GALPROP_DATA_PATH );          //initialization of the Webber's routine
#endif

  return 0;

}


Int_t GalpropManager::Run(){

  if(DEBUG){
    cout << "Run(): ENTER" << endl;
  }

  //  fGalprop->galdef = *fGaldef;

  if(firstrun){
    if( fGalprop->create_galaxy() )       return 1;
    if( fGalprop->create_gcr() )          return 1;
  }
  if( fGalprop->propagate_particles() ) return 1;
#if GALPROP_MAIN_V < 55
  fGalprop->cr_luminosity();
#endif
  firstrun = kFALSE;

  if(DEBUG){
    cout << "Run(): EXIT" << endl;
  }

  return 0;

}


TGraph* GalpropManager::GetFlux(Int_t Z, Int_t A){

  if(!Z) return NULL;

  TList* _flist = new TList();

  Particle* gcr = fGalprop->gcr;                   //Galprop internal class for describing particles. gcr is an array.

  int n_points = gcr[0].n_pgrid;
  int iz1 = (int)(1.e-6 -fGaldef->z_min/fGaldef->dz);
  Double_t R = 8.5;

//   if(DEBUG){
//     cout << "Getting flux for (" << Z << "," << A << ")" << endl;
//     cout << "n_points = " << n_points << endl;
//   }

  if(gcr[0].n_spatial_dimensions==2){
    // 2D CASE ---------------------------------
    int ir  = (int) ((R - fGaldef->r_min)/fGaldef->dr);
    
    for(int isp=0; isp<fGalprop->n_species; isp++){

      if(gcr[isp].Z != Z) continue;
      if(gcr[isp].A != A) continue;
      
//       if(DEBUG)
// 	cout << " -- GalpropManager::GetFlux() :  Found flux for (" << Z << "," << A << ") at index " << isp << endl;

      TGraph* temp_graph = new TGraph( n_points );

      for(int ip=0; ip<n_points; ip++){
	
	temp_graph->GetX()[ip] = fGaldef->Ekin_min * pow(fGaldef->Ekin_factor, ip);

	if(gcr[isp].A != 0)
	  temp_graph->GetY()[ip] = gcr[isp].cr_density.d2[ir][iz1].s[ip] * gcr[isp].A;  //That's the definition of flux, look in the manual at page 7
	else
	  temp_graph->GetY()[ip] = gcr[isp].cr_density.d2[ir][iz1].s[ip];  //That's the definition of flux, look in the manual at page 7
	//	* pow(gcr[isp].Ekin[ip],2);	
      }

      _flist->Add(temp_graph); 
    }    
  } else if(gcr[0].n_spatial_dimensions==3) {
    // 3D CASE ---------------------------------
    int iy  = (int)(1.e-6 -fGaldef->y_min/fGaldef->dy);
    int ix  = (int) ((R - fGaldef->x_min)/fGaldef->dx);
    
    for(int isp=0; isp<fGalprop->n_species; isp++){
      if(gcr[isp].Z != Z) continue;
      if(gcr[isp].A != A) continue;

//       if(DEBUG)
// 	cout << " -- GalpropManager::GetFlux() :  Found flux for (" << Z << "," << A << ") at index " << isp << endl;

      TGraph* temp_graph = new TGraph( n_points );

      for(int ip=0; ip<n_points; ip++){
	
	temp_graph->GetX()[ip] = fGaldef->Ekin_min * pow(fGaldef->Ekin_factor, ip);
	if(gcr[isp].A != 0)
	  temp_graph->GetY()[ip] = gcr[isp].cr_density.d2[ix][iy].s[ip] * gcr[isp].A;  //That's the definition of flux, look in the manual at page 7
	else
	  temp_graph->GetY()[ip] = gcr[isp].cr_density.d2[ix][iy].s[ip];  //That's the definition of flux, look in the manual at page 7
	//	* pow(gcr[isp].Ekin[ip],2);	
      }

      _flist->Add(temp_graph);      
    }
  }


  //All fluxes added to the list now sum them up!
  TGraph* tot_flux = new TGraph( n_points );
  for(Int_t ipt=0; ipt<n_points; ipt++){
    tot_flux->GetX()[ipt] = ((TGraph*) _flist->At(0))->GetX()[ipt] * 1e-3;  //1e-3 = conversion factor between MeV and GeV

    for(Int_t ngraph=0; ngraph<_flist->GetEntries(); ngraph++)
      tot_flux->GetY()[ipt] += ((TGraph*) _flist->At(ngraph))->GetY()[ipt] * 1e7;  //1e7 = conversion factor between (MeV/n cm^2 s sr)^-1 and (GeV/n m^2 s sr)^-1

  }

  delete _flist;
  return tot_flux;

}
