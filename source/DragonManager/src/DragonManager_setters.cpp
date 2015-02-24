#include <TMath.h>
#include <DragonManager.h>

void DragonManager::SetVerbose( Int_t verbose ){};

// -- Galaxy Parameters
void DragonManager::SetNDimensions( Int_t ndim ){

  switch(ndim){
  case 2:
    fInput->gridtype = "2D";
    break;
  case 3:
    fInput->gridtype = "3D";
    break;
  }

}

void DragonManager::SetGalaxyXdim( Double_t x_min, Double_t x_max, Double_t dx ){

  //Dragon only uses the galactocentric radius for distance...
  if(x_min)
    fInput->Rmin = x_min;
  if(x_max)
    fInput->Rmax = x_max;
  if(dx)
    fInput->numx = TMath::Nint( (x_max-x_min)/dx );

}


void DragonManager::SetGalaxyYdim( Double_t y_min, Double_t y_max, Double_t dy ){

  //Dragon only uses the galactocentric radius for distance...
  if(y_min)
    fInput->Rmin = y_min;
  if(y_max)
    fInput->Rmax = y_max;
  if(dy)
    fInput->numy = TMath::Nint( (y_max-y_min)/dy );

}


void DragonManager::SetGalaxyZdim( Double_t z_min, Double_t z_max, Double_t dz ){

  //Galprop allows for a z_min value, for cases like z in (-4, 4)
  //Dragon only uses the half-height of the galaxy, we take the max between z_min and z_max

  Double_t galz = TMath::Max( z_min, z_max );

  if(galz)
    fInput->zmax = galz;
  if(dz)
    fInput->numr = TMath::Nint( galz/dz );

}


void DragonManager::SetGalaxyRdim( Double_t r_min, Double_t r_max, Double_t dr ){

  if(r_max)
    fInput->Rmin = r_min;
  if(r_max)
    fInput->Rmax = r_max;
  if(dr)
    fInput->numr = TMath::Nint( (r_max-r_min)/dr );

}


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

// -- Solution Parameters
void DragonManager::SetMomentumGrid( Double_t p_min, Double_t p_max, Double_t p_factor ){

  //Dragon only uses energy...
  std::cerr << " --- Warning in DragonManager::SetMomentumGrid " << std::endl;
  std::cerr << "       DRAGON only allows for an energy grid " << std::endl;
  std::cerr << "       please use SetEnergyGrid instead " << std::endl;

}


void DragonManager::SetEnergyGrid( Double_t E_min, Double_t E_max, Double_t E_factor ){

  std::cout << "djsadja" << std::endl;

  if(E_min)
    fInput->Ekmin = E_min;
  if(E_max)
    fInput->Ekmax = E_max;
  if(E_factor)
    fInput->Ekfact = E_factor;

}


void DragonManager::SwitchToEnergyGrid(){}

void DragonManager::SwitchToMomentumGrid(){}


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

// -- Propagation Parameters
void DragonManager::SetDiffusionCoefficient( Double_t D0_xx, Double_t D_g_1, Double_t D_rigid_br, Double_t D_g_2){
  
    if(D0_xx)
      fInput->D0 = D0_xx;
    if(D_g_1)
      fInput->delta = D_g_1;
    if(D_rigid_br)
      fInput->rho_b = D_rigid_br;
    if(D_g_2)
      fInput->delta_h = D_g_2;

};


void DragonManager::SetDiffusiveReacceleration( Int_t diff_reacc ){
  fInput->REACC = true;
  switch(diff_reacc){
  case 1:
    fInput->diff_reacc = Ptuskin94;
    break;
  case 2:
    fInput->diff_reacc = Ptuskin03;
    break;
  default:
    fInput->diff_reacc = Ptuskin03;
    break;
  }
};


void DragonManager::SetAlfvenSpeed( Double_t v_Alfven ){
  fInput->REACC = true;
  fInput->vAlfven = v_Alfven * km * Myr /kpc;
  if( ! fInput->diff_reacc )
    SetDiffusiveReacceleration( 2 );
};


void DragonManager::SetNucleiSourceSpectrum( Double_t nuc_g_0,                       // spectral index before the first break      // AV2011
					     Double_t nuc_rigid_br0,                 // break rigidity for nuclei injection  in MV // AV2011
					     Double_t nuc_g_1,                       // spectral index below the second break      // AV2011
					     Double_t nuc_rigid_br1,                 // break rigidity for nuclei injection  in MV // AV2011
					     Double_t nuc_g_2,                       // spectral index above the second break      // AV2011
					     Double_t nuc_rigid_br2,                 // break rigidity for nuclei injection  in MV // AV2011
					     Double_t nuc_g_3                        // spectral index above the second break      // AV2011
					     ){

  if(nuc_g_0 && fInput->inp_inj_indexes.size() > 0)
    fInput->inp_inj_indexes[0] = nuc_g_0;
  else if(nuc_g_0)
    fInput->inp_inj_indexes.push_back( nuc_g_0 );

  if(nuc_g_1 && fInput->inp_inj_indexes.size() > 1)
    fInput->inp_inj_indexes[1] = nuc_g_1;
  else if(nuc_g_1)
    fInput->inp_inj_indexes.push_back( nuc_g_1 );

  if(nuc_g_2 && fInput->inp_inj_indexes.size() > 2)
    fInput->inp_inj_indexes[2] = nuc_g_2;
  else if(nuc_g_2)
    fInput->inp_inj_indexes.push_back( nuc_g_2 );

  if(nuc_g_3 && fInput->inp_inj_indexes.size() > 3)
    fInput->inp_inj_indexes[3] = nuc_g_3;
  else if(nuc_g_3)
    fInput->inp_inj_indexes.push_back( nuc_g_3 );


  if(nuc_rigid_br0 && fInput->inp_break_positions.size() > 0)
    fInput->inp_break_positions[0] = nuc_rigid_br0;
  else if(nuc_rigid_br0)
    fInput->inp_break_positions.push_back( nuc_rigid_br0 );

  if(nuc_rigid_br1 && fInput->inp_break_positions.size() > 1)
    fInput->inp_break_positions[1] = nuc_rigid_br1;
  else if(nuc_rigid_br1)
    fInput->inp_break_positions.push_back( nuc_rigid_br1 );

  if(nuc_rigid_br2 && fInput->inp_break_positions.size() > 2)
    fInput->inp_break_positions[2] = nuc_rigid_br1;
  else if(nuc_rigid_br2)
    fInput->inp_break_positions.push_back( nuc_rigid_br2 );


  if(fInput->inp_inj_indexes.size() > 3){
    (fInput->inp_inj_indexes).resize(3);
  }

  if(fInput->inp_break_positions.size() > 2){
    (fInput->inp_break_positions).resize(2);
  }

};


void DragonManager::SetDeltaPHe( Double_t delta_p_he ){

  //Do nothing, there is no delta_p_he in DRAGON

};


void DragonManager::SetElectronSourceSpectrum( Double_t electron_g_0,                  // index below electron_rigid_br0            IMOS20031012
					       Double_t electron_rigid_br0,            // break rigidity0 for electron injection in MV
					       Double_t electron_g_1,                  // spectral index between breaks
					       Double_t electron_rigid_br1,            // break rigidity1 for electron injection in MV
					       Double_t electron_g_2,                  // spectral index above electron_rigid_br
					       Double_t electron_rigid_br2,            // break rigidity1 for electron injection in MV
					       Double_t electron_g_3                   // spectral index above electron_rigid_br
					       ){


  if(electron_g_0 && fInput->inp_inj_el_indexes.size() > 0)
    fInput->inp_inj_el_indexes[0] = electron_g_0;
  else if(electron_g_0)
    fInput->inp_inj_el_indexes.push_back( electron_g_0 );

  if(electron_g_1 && fInput->inp_inj_el_indexes.size() > 1)
    fInput->inp_inj_el_indexes[1] = electron_g_1;
  else if(electron_g_1)
    fInput->inp_inj_el_indexes.push_back( electron_g_1 );

  if(electron_g_2 && fInput->inp_inj_el_indexes.size() > 2)
    fInput->inp_inj_el_indexes[2] = electron_g_2;
  else if(electron_g_2)
    fInput->inp_inj_el_indexes.push_back( electron_g_2 );

  if(electron_g_3 && fInput->inp_inj_el_indexes.size() > 3)
    fInput->inp_inj_el_indexes[3] = electron_g_3;
  else if(electron_g_3)
    fInput->inp_inj_el_indexes.push_back( electron_g_3 );


  if(electron_rigid_br0 && fInput->inp_break_el_positions.size() > 0)
    fInput->inp_break_el_positions[0] = electron_rigid_br0;
  else if(electron_rigid_br0)
    fInput->inp_break_el_positions.push_back( electron_rigid_br0 );

  if(electron_rigid_br1 && fInput->inp_break_el_positions.size() > 1)
    fInput->inp_break_el_positions[1] = electron_rigid_br1;
  else if(electron_rigid_br1)
    fInput->inp_break_el_positions.push_back( electron_rigid_br1 );

  if(electron_rigid_br2 && fInput->inp_break_el_positions.size() > 2)
    fInput->inp_break_el_positions[2] = electron_rigid_br2;
  else if(electron_rigid_br2)
    fInput->inp_break_el_positions.push_back( electron_rigid_br2 );


  if(fInput->inp_inj_indexes.size() > 4){
    for(int i=4; i<fInput->inp_inj_indexes.size(); i++)
      fInput->inp_inj_indexes[i] = 0;
  }

  if(fInput->inp_break_positions.size() > 3){
    for(int i=3; i<fInput->inp_break_positions.size(); i++)
      fInput->inp_break_positions[i] = 0;
  }

};

