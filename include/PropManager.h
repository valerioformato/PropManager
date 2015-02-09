#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>

#include <TROOT.h>
#include <TGraph.h>


#ifndef PROPMANAGER_H
#define PROPMANAGER_H

class PropManager{
 public:
  PropManager();
  ~PropManager();

  virtual Int_t InitDefault() =0;
  virtual Int_t Run() =0;

  virtual TGraph* GetFlux(Int_t Z, Int_t A) =0;

  virtual Int_t Reset() =0;
  virtual void Print() =0;

  virtual void SetVerbose( Int_t verbose ) =0;
  /* // -- Galaxy Parameters */
  virtual void SetNDimensions( Int_t ndim ) =0;
  virtual void SetGalaxyXdim( Double_t x_min, Double_t x_max, Double_t dx ) =0; //only 3D case
  virtual void SetGalaxyYdim( Double_t y_min, Double_t y_max, Double_t dy ) =0; //only 3D case
  virtual void SetGalaxyZdim( Double_t z_min, Double_t z_max, Double_t dz ) =0;
  virtual void SetGalaxyRdim( Double_t r_min, Double_t r_max, Double_t dr ) =0; //only 2D case

  /* // -- Solution Parameters */
  virtual void SetMomentumGrid( Double_t p_min, Double_t p_max, Double_t p_factor ) =0;
  virtual void SetEnergyGrid( Double_t E_min, Double_t E_max, Double_t E_factor ) =0;
  virtual void SwitchToEnergyGrid() =0;
  virtual void SwitchToMomentumGrid() =0;

  // -- Propagation Parameters
  virtual void SetDiffusionCoefficient( Double_t D0_xx,	Double_t D_g_0,	Double_t D_rigid_br, Double_t D_g_1) =0;
  virtual void SetDiffusiveReacceleration( Int_t diff_reacc ) =0;
  virtual void SetAlfvenSpeed( Double_t v_Alfven ) =0;
  virtual void SetNucleiSourceSpectrum( Double_t nuc_g_0, Double_t nuc_rigid_br0, Double_t nuc_g_1, Double_t nuc_rigid_br1, Double_t nuc_g_2, Double_t nuc_rigid_br2, Double_t nuc_g_3 ) =0;
  //  virtual void SetDeltaPHe( Double_t delta_p_he ) =0;
  virtual void SetElectronSourceSpectrum( Double_t electron_g_0, Double_t electron_rigid_br0, Double_t electron_g_1, Double_t electron_rigid_br1, Double_t electron_g_2, Double_t electron_rigid_br2, Double_t electron_g_3 ) =0;

  //Getters
  // -- Galaxy Parameters
  virtual Int_t GetNDimensions() =0;
  virtual Double_t GetGalaxyZdim() =0;

  // -- Propagation Parameters
  virtual Double_t GetD0_xx() =0;
  //  virtual Double_t GetD_g_0() =0;
  //  virtual Double_t GetD_rigid_br0() =0;
  virtual Double_t GetD_g_1() =0;
  virtual Double_t GetD_rigid_br() =0;
  virtual Double_t GetD_g_2() =0;

  virtual Double_t GetAlfvenSpeed() =0;

  virtual Double_t GetNuc_g_0() =0;
  virtual Double_t GetNuc_rigid_br0() =0;
  virtual Double_t GetNuc_g_1() =0;
  virtual Double_t GetNuc_rigid_br() =0;
  virtual Double_t GetNuc_g_2() =0;
  virtual Double_t GetNuc_rigid_br2() =0;
  virtual Double_t GetNuc_g_3() =0;

  //  virtual Double_t GetDeltaPHe() =0;

  virtual Double_t GetElectron_g_0() =0;
  virtual Double_t GetElectron_rigid_br0() =0;
  virtual Double_t GetElectron_g_1() =0;
  virtual Double_t GetElectron_rigid_br() =0;
  virtual Double_t GetElectron_g_2() =0;
  virtual Double_t GetElectron_rigid_br2() =0;
  virtual Double_t GetElectron_g_3() =0;

  enum engine_t {
    kGalprop,
    kDragon,
    NumEngines
  };


};

#endif
