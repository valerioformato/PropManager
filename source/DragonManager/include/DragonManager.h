#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>

#include <TROOT.h>
/* #include <TH1F.h> */
/* #include <TH2F.h> */
/* #include <TH1D.h> */
/* #include <TH2D.h> */
/* #include <TVectorT.h> */
/* #include <TFile.h> */
/* #include <TList.h> */
/* #include <TString.h> */
/* #include <TLine.h> */
#include <TGraph.h>
/* #include <TGraphAsymmErrors.h> */
/* #include <TGraphErrors.h> */
/* #include <TChain.h> */
/* #include <TCutG.h> */
/* #include <TF1.h> */
/* #include <TCanvas.h> */
/* #include <TObjString.h> */
/* #include <TMath.h> */

#include <input.h>
#include <particle.h>
#include <grid.h>
#include <galaxy.h>
#include <dragon.h>

#include <PropManager.h>


#ifndef DRAGONMGR_H
#define DRAGONMGR_H

class MyDRAGON : public DRAGON{

 public:
  MyDRAGON();
  MyDRAGON( Input* inp );

  vector<double> GetEnergyGrid();
  vector<TParticle*> GetParticles();

};


//enum SourceType_t {kRigidity, kBetaRigidity, kEtot, nSourceTypes};

class DragonManager : public PropManager {
 public:
  DragonManager( TString defxml="run_2D" );
  ~DragonManager();

  Int_t InitDefault();
  Int_t Run();

  Int_t Reset();
  void Print();

  //Setters
  void SetVerbose( Int_t verbose );

  /* // -- Galaxy Parameters */
  void SetNDimensions( Int_t ndim );
  void SetGalaxyXdim( Double_t x_min, Double_t x_max, Double_t dx ); //only 3D case
  void SetGalaxyYdim( Double_t y_min, Double_t y_max, Double_t dy ); //only 3D case
  void SetGalaxyZdim( Double_t z_min, Double_t z_max, Double_t dz );
  void SetGalaxyRdim( Double_t r_min, Double_t r_max, Double_t dr ); //only 2D case

  /* // -- Solution Parameters */
  void SetMomentumGrid( Double_t p_min, Double_t p_max, Double_t p_factor );
  void SetEnergyGrid( Double_t E_min, Double_t E_max, Double_t E_factor );
  void SwitchToEnergyGrid();
  void SwitchToMomentumGrid();

  // -- Propagation Parameters
  void SetDiffusionCoefficient( Double_t D0_xx,                         // diffusion coefficient at break  rigidity
  				Double_t D_g_1,                         // diffusion coefficient index between low-E and high-E breaks
  				Double_t D_rigid_br,                   // break     rigidity for diffusion coefficient in MV
  				Double_t D_g_2                          // diffusion coefficient index above break  rigidity
  				);

  void SetDiffusiveReacceleration( Int_t diff_reacc );
  void SetAlfvenSpeed( Double_t v_Alfven );
  void SetNucleiSourceSpectrum( Double_t nuc_g_0,                       // spectral index before the first break      // AV2011
  				Double_t nuc_rigid_br0,                 // break rigidity for nuclei injection  in MV // AV2011
  				Double_t nuc_g_1,                       // spectral index below the second break      // AV2011
  				Double_t nuc_rigid_br1,                 // break rigidity for nuclei injection  in MV // AV2011
  				Double_t nuc_g_2,                       // spectral index above the second break      // AV2011
  				Double_t nuc_rigid_br3,                 // break rigidity for nuclei injection  in MV // AV2011
  				Double_t nuc_g_3                        // spectral index above the second break      // AV2011
  				);
  void SetDeltaPHe( Double_t delta_p_he );        // AV2011: Difference between proton and >= helium spectral index at all energies.
                                                  // Positive values make >= helium spectrum harder than that of protons.
                                                  // E.g., nuc_g_1=1.8 and delta_p_he=0.2 makes proton spectrum have
                                                  // an index of -1.8 and helium spectrum -- -1.6.

  void SetElectronSourceSpectrum( Double_t electron_g_0,                  // index below electron_rigid_br0            IMOS20031012
  				  Double_t electron_rigid_br0,            // break rigidity0 for electron injection in MV
  				  Double_t electron_g_1,                  // spectral index between breaks
  				  Double_t electron_rigid_br1,            // break rigidity1 for electron injection in MV
  				  Double_t electron_g_2,                  // spectral index above electron_rigid_br
  				  Double_t electron_rigid_br2,            // break rigidity1 for electron injection in MV
  				  Double_t electron_g_3                   // spectral index above electron_rigid_br
  				  );

  /* void SetProtonAbundance( Double_t prot_ab );   */



  /* //Getters */
  /* // -- Galaxy Parameters */
  Int_t GetNDimensions(){ return _ndim; };
  Double_t GetGalaxyZdim(){ return fInput->zmax; };

  // -- Propagation Parameters
  Double_t GetD0_xx(){ return fInput->D0; };
  Double_t GetD_g_1(){ return fInput->delta; };
  Double_t GetD_rigid_br(){ return fInput->rho_b; };
  Double_t GetD_g_2(){ return fInput->delta_h; }; 

  Double_t GetAlfvenSpeed(){ return fInput->vAlfven * kpc / Myr / km; };

  Double_t GetNuc_g_0(){ 
    if( fInput->inp_inj_indexes.size() > 0 )
      return fInput->inp_inj_indexes[0]; 
    else 
      return 0;
  };
  Double_t GetNuc_rigid_br0(){ 
    if( fInput->inp_break_positions.size() > 0 )
      return fInput->inp_break_positions[0]; 
    else
      return 0;
  };
  Double_t GetNuc_g_1(){ 
    if( fInput->inp_inj_indexes.size() > 1 )
      return fInput->inp_inj_indexes[1]; 
    else 
      return 0;
  };
  Double_t GetNuc_rigid_br(){ 
    if( fInput->inp_break_positions.size() > 1 )
      return fInput->inp_break_positions[1]; 
    else
      return 0;
  };
  Double_t GetNuc_g_2(){ 
    if( fInput->inp_inj_indexes.size() > 2 )
      return fInput->inp_inj_indexes[2]; 
    else 
      return 0;
  };
  Double_t GetNuc_rigid_br2(){ 
    if( fInput->inp_break_positions.size() > 2 )
      return fInput->inp_break_positions[2]; 
    else
      return 0;
  };
  Double_t GetNuc_g_3(){ 
    if( fInput->inp_inj_indexes.size() > 3 )
      return fInput->inp_inj_indexes[3]; 
    else 
      return 0;
  };

  Double_t GetDeltaPHe(){ return 0; };

  Double_t GetElectron_g_0(){ 
    if( fInput->inp_inj_el_indexes.size() > 0 )
      return fInput->inp_inj_el_indexes[0]; 
    else 
      return 0;
  };
  Double_t GetElectron_rigid_br0(){ 
    if( fInput->inp_break_el_positions.size() > 0 )
      return fInput->inp_break_el_positions[0]; 
    else
      return 0;
  };
  Double_t GetElectron_g_1(){ 
    if( fInput->inp_inj_el_indexes.size() > 1 )
      return fInput->inp_inj_el_indexes[1]; 
    else 
      return 0;
  };
  Double_t GetElectron_rigid_br(){ 
    if( fInput->inp_break_el_positions.size() > 1 )
      return fInput->inp_break_el_positions[1]; 
    else
      return 0;
  };
  Double_t GetElectron_g_2(){ 
    if( fInput->inp_inj_el_indexes.size() > 2 )
      return fInput->inp_inj_el_indexes[2]; 
    else 
      return 0;
  };
  Double_t GetElectron_rigid_br2(){ 
    if( fInput->inp_break_el_positions.size() > 2 )
      return fInput->inp_break_el_positions[2]; 
    else
      return 0;
  };
  Double_t GetElectron_g_3(){ 
    if( fInput->inp_inj_el_indexes.size() > 3 )
      return fInput->inp_inj_el_indexes[3]; 
    else 
      return 0;
  };

  /* Double_t GetProtonAbundance(){ return fInput->isotopic_abundance[1][1]; };   */

  TGraph* GetFlux(Int_t Z, Int_t A);

 private:
  TString _defxml;
  Int_t _ndim;

  Bool_t  firstrun;
  Input*  fInput;
  MyDRAGON* fDragon;
};


#endif


