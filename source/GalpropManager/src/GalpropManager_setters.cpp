#include <GalpropManager.h>

//Setters

void GalpropManager::SetVerbose( Int_t verbose ){
  fGaldef->verbose = verbose;
};

// -- Galaxy Parameters
void GalpropManager::SetNDimensions( Int_t ndim ){
  fGaldef->n_spatial_dimensions = ndim;
};

void GalpropManager::SetGalaxyXdim( Double_t x_min, Double_t x_max, Double_t dx ){ //only 3D case
  if(x_min)
    fGaldef->x_min = x_min;
  if(x_max)
    fGaldef->x_max = x_max;
  if(dx)
    fGaldef->dx = dx;
};

void GalpropManager::SetGalaxyYdim( Double_t y_min, Double_t y_max, Double_t dy ){ //only 3D case
  if(y_min)
    fGaldef->y_min = y_min;
  if(y_max)
    fGaldef->y_max = y_max;
  if(dy)
    fGaldef->dy = dy;
};

void GalpropManager::SetGalaxyZdim( Double_t z_min, Double_t z_max, Double_t dz ){
  if(z_min)
    fGaldef->z_min = z_min;
  if(z_max)
    fGaldef->z_max = z_max;
  if(dz)
    fGaldef->dz = dz;
};

void GalpropManager::SetGalaxyRdim( Double_t r_min, Double_t r_max, Double_t dr ){ //only 2D case
  if(r_min)
    fGaldef->r_min = r_min;
  if(r_max)
    fGaldef->r_max = r_max;
  if(dr)
    fGaldef->dr = dr;
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

// -- Solution Parameters
void GalpropManager::SetMomentumGrid( Double_t p_min, Double_t p_max, Double_t p_factor ){
  if(p_min)
    fGaldef->p_min = p_min;
  if(p_max)
    fGaldef->p_max = p_max;
  if(p_factor)
    fGaldef->p_factor = p_factor;
};

void GalpropManager::SetEnergyGrid( Double_t E_min, Double_t E_max, Double_t E_factor ){
  if(E_min)
    fGaldef->Ekin_min = E_min;
  if(E_max)
    fGaldef->Ekin_max = E_max;
  if(E_factor)
    fGaldef->Ekin_factor = E_factor;
};

void GalpropManager::SwitchToEnergyGrid(){
#if GALPROP_MAIN_V < 55
  strncpy(fGaldef->p_Ekin_grid, "Ekin ", 5);
#else
  fGaldef->p_Ekin_grid = "Ekin";
#endif
};

void GalpropManager::SwitchToMomentumGrid(){
#if GALPROP_MAIN_V < 55
  strncpy(fGaldef->p_Ekin_grid, "p    ", 5);
#else
  fGaldef->p_Ekin_grid = "p";
#endif
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

  // -- Propagation Parameters
void GalpropManager::SetDiffusionCoefficient( Double_t D0_xx, Double_t D_g_1, Double_t D_rigid_br, Double_t D_g_2){

    if(D0_xx)
      fGaldef->D0_xx = D0_xx;
    if(D_rigid_br)
      fGaldef->D_rigid_br = D_rigid_br;
    if(D_g_1)
      fGaldef->D_g_1 = D_g_1;
    if(D_g_2)
      fGaldef->D_g_2 = D_g_2;

};

void GalpropManager::SetDiffusiveReacceleration( Int_t diff_reacc ){
  fGaldef->diff_reacc = diff_reacc;
};

void GalpropManager::SetAlfvenSpeed( Double_t v_Alfven ){
  fGaldef->v_Alfven = v_Alfven;
};

void GalpropManager::SetNucleiSourceSpectrum( Double_t nuc_g_0,	
					      Double_t nuc_rigid_br0,	
					      Double_t nuc_g_1, 
					      Double_t nuc_rigid_br, 
					      Double_t nuc_g_2
#if GALPROP_MAIN_V < 55
					      ,Double_t nuc_rigid_br2, 
					      Double_t nuc_g_3
#endif
					      ){

  if(nuc_g_0)
    fGaldef->nuc_g_0 = nuc_g_0;
  if(nuc_rigid_br0)
    fGaldef->nuc_rigid_br0 = nuc_rigid_br0;
  if(nuc_g_1)
    fGaldef->nuc_g_1 = nuc_g_1;
  if(nuc_rigid_br)
    fGaldef->nuc_rigid_br = nuc_rigid_br;
  if(nuc_g_2)
    fGaldef->nuc_g_2 = nuc_g_2;
#if GALPROP_MAIN_V < 55
  if(nuc_rigid_br2)
    fGaldef->nuc_rigid_br2 = nuc_rigid_br2;
  if(nuc_g_3)
    fGaldef->nuc_g_3 = nuc_g_3;
#endif

};


#if GALPROP_MAIN_V > 54
void GalpropManager::SetNucleiSourceSpectrum( Int_t Z, 
					      Int_t A, 
					      Double_t nuc_g_0,	
					      Double_t nuc_rigid_br0,	
					      Double_t nuc_g_1, 
					      Double_t nuc_rigid_br, 
					      Double_t nuc_g_2
					      ){

  if( A==0 ){
    for ( A=Z; A<Z*3; A++ ) {
      SetNucleiSourceSpectrum( Z, A, nuc_g_0, nuc_rigid_br0, nuc_g_1, nuc_rigid_br, nuc_g_2 ); //Just beacuse I can. I know, I'm evil...
    }
    return;
  }

  std::pair<int, int> indx(Z, A);
  Galdef::specProperties &prop = fGaldef->iso_inj_spectra[std::pair<int,int> (Z, A)];
    
  if(nuc_g_0)
    prop.g_0 = nuc_g_0;
  if(nuc_rigid_br0)
    prop.rigid_br0 = nuc_rigid_br0;
  if(nuc_g_1)
    prop.g_1 = nuc_g_1;
  if(nuc_rigid_br)
    prop.rigid_br = nuc_rigid_br;
  if(nuc_g_2)
    prop.g_2 = nuc_g_2;

  return;

};
#endif



void GalpropManager::SetElectronSourceSpectrum( Double_t electron_g_0,                  // index below electron_rigid_br0            IMOS20031012
						Double_t electron_rigid_br0,            // break rigidity0 for electron injection in MV
						Double_t electron_g_1,                  // spectral index between breaks
						Double_t electron_rigid_br,             // break rigidity1 for electron injection in MV
						Double_t electron_g_2                  // spectral index above electron_rigid_br
#if GALPROP_MAIN_V < 55
						,Double_t electron_rigid_br2,            // break rigidity1 for electron injection in MV
						Double_t electron_g_3                   // spectral index above electron_rigid_br
#endif
						){

  if(electron_g_0)
    fGaldef->electron_g_0 = electron_g_0;
  if(electron_rigid_br0)
    fGaldef->electron_rigid_br0 = electron_rigid_br0;
  if(electron_g_1)
    fGaldef->electron_g_1 = electron_g_1;
  if(electron_rigid_br)
    fGaldef->electron_rigid_br = electron_rigid_br;
  if(electron_g_2)
    fGaldef->electron_g_2 = electron_g_2;
#if GALPROP_MAIN_V < 55
  if(electron_rigid_br2)
    fGaldef->electron_rigid_br2 = electron_rigid_br2;
  if(electron_g_3)
    fGaldef->electron_g_3 = electron_g_3;
#endif

};



void GalpropManager::SetProtonAbundance( Double_t prot_ab ){

  fGaldef->isotopic_abundance[1][1] = prot_ab;

};
