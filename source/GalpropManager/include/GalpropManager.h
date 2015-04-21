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

#include <Galprop.h>
#include <galprop_internal.h>
#include <fort_interface1.h>
#include <fort_interface2.h>
#include <healpix_base.h>

#include <PropManager.h>


#ifndef GALPROPMGR_H
#define GALPROPMGR_H

#define str2(s) #s
#define str(s) str2(s)

#if GALPROP_MAIN_V > 54
#include <Nuclei_Interface.h>
#include <Processes_Interface.h>
#endif

enum SourceType_t {kRigidity, kBetaRigidity, kEtot, nSourceTypes};

class GalpropManager : public PropManager {
 public:
  GalpropManager( TString defgal="webrun" );
  ~GalpropManager();

  Int_t InitDefault();
  Int_t Run();

  Int_t Reset();
  void Print();

  //Setters
  void SetVerbose( Int_t verbose );

  // -- Galaxy Parameters
  void SetNDimensions( Int_t ndim );
  void SetGalaxyXdim( Double_t x_min, Double_t x_max, Double_t dx ); //only 3D case
  void SetGalaxyYdim( Double_t y_min, Double_t y_max, Double_t dy ); //only 3D case
  void SetGalaxyZdim( Double_t z_min, Double_t z_max, Double_t dz );
  void SetGalaxyRdim( Double_t r_min, Double_t r_max, Double_t dr ); //only 2D case
#if GALPROP_MAIN_V > 54
  void SetBubbleDimension( Double_t r );
  void SetGasDensityFactor( Double_t factor );
#endif


  // -- Solution Parameters
  void SetMomentumGrid( Double_t p_min, Double_t p_max, Double_t p_factor );
  void SetEnergyGrid( Double_t E_min, Double_t E_max, Double_t E_factor );
  void SwitchToEnergyGrid();
  void SwitchToMomentumGrid();

  // -- Propagation Parameters
  void SetDiffusionCoefficient( Double_t D0_xx,                         
				Double_t D_g_1,                         
				Double_t D_rigid_br,                    
				Double_t D_g_2                          
				);

  void SetDiffusiveReacceleration( Int_t diff_reacc );
  void SetAlfvenSpeed( Double_t v_Alfven );
  void SetNucleiSourceSpectrum( Double_t nuc_g_0,                     
				Double_t nuc_rigid_br0,               
				Double_t nuc_g_1,                     
				Double_t nuc_rigid_br,                
				Double_t nuc_g_2,
				Double_t nuc_rigid_br2=0,               
				Double_t nuc_g_3=0
				);
#if GALPROP_MAIN_V > 54
  void SetNucleiSourceSpectrum( Int_t Z,
				Int_t A,
				Double_t nuc_g_0,                     
				Double_t nuc_rigid_br0,               
				Double_t nuc_g_1,                     
				Double_t nuc_rigid_br,                
				Double_t nuc_g_2
				);
#endif

  void SetElectronSourceSpectrum( Double_t electron_g_0,                  // index below electron_rigid_br0            IMOS20031012
				  Double_t electron_rigid_br0,            // break rigidity0 for electron injection in MV
				  Double_t electron_g_1,                  // spectral index between breaks
				  Double_t electron_rigid_br,             // break rigidity1 for electron injection in MV
				  Double_t electron_g_2,                  // spectral index above electron_rigid_br
				  Double_t electron_rigid_br2=0,          // break rigidity1 for electron injection in MV
				  Double_t electron_g_3=0                 // spectral index above electron_rigid_br
				  );

  void SetProtonAbundance( Double_t prot_ab );  


  //Getters
  // -- Galaxy Parameters
  Int_t GetNDimensions(){ return 2; };
  Double_t GetGalaxyZdim(){ return 0.5*(fGaldef->z_max - fGaldef->z_min); };

  // -- Propagation Parameters
  Double_t GetD0_xx(){ return fGaldef->D0_xx; };
  Double_t GetD_g_1(){ return fGaldef->D_g_1; };
  Double_t GetD_rigid_br(){ return fGaldef->D_rigid_br; };
  Double_t GetD_g_2(){ return fGaldef->D_g_2; };

  Double_t GetAlfvenSpeed(){ return fGaldef->v_Alfven; };

  Double_t GetNuc_g_0(){ return fGaldef->nuc_g_0; };
  Double_t GetNuc_rigid_br0(){ return fGaldef->nuc_rigid_br0; };
  Double_t GetNuc_g_1(){ return fGaldef->nuc_g_1; };
  Double_t GetNuc_rigid_br(){ return fGaldef->nuc_rigid_br; };
  Double_t GetNuc_g_2(){ return fGaldef->nuc_g_2; };
#if GALPROP_MAIN_V < 55
  Double_t GetNuc_rigid_br2(){ return fGaldef->nuc_rigid_br2; };
  Double_t GetNuc_g_3(){ return fGaldef->nuc_g_3; };
#else
  //dummy in version > 55
  Double_t GetNuc_rigid_br2(){ return 42; };
  Double_t GetNuc_g_3(){ return 42; };
#endif

  Double_t GetElectron_g_0(){ return fGaldef->electron_g_0; };
  Double_t GetElectron_rigid_br0(){ return fGaldef->electron_rigid_br0; };
  Double_t GetElectron_g_1(){ return fGaldef->electron_g_1; };
  Double_t GetElectron_rigid_br(){ return fGaldef->electron_rigid_br; };
  Double_t GetElectron_g_2(){ return fGaldef->electron_g_2; };
#if GALPROP_MAIN_V < 55
  Double_t GetElectron_rigid_br2(){ return fGaldef->electron_rigid_br2; };
  Double_t GetElectron_g_3(){ return fGaldef->electron_g_3; };
#else
  //dummy in version > 55
  Double_t GetElectron_rigid_br2(){ return 42; };
  Double_t GetElectron_g_3(){ return 42; };
#endif

  Double_t GetProtonAbundance(){ return fGaldef->isotopic_abundance[1][1]; };  

  TGraph* GetFlux(Int_t Z, Int_t A);

 private:
  TString _default_galdef;

  Bool_t firstrun;
  Galdef* fGaldef;
  Galprop* fGalprop;
};

#endif


