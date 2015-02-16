#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>

#include <TROOT.h>
#include <TGraph.h>


#ifndef PROPMANAGER_H
#define PROPMANAGER_H


//!A template class to describe a Manager
/*!
  This class defines all the Set/Get methods for all the propagation managers (for now just Galprop/DRAGON)
 */
class PropManager{
 public:
  PropManager();
  ~PropManager();

  //!Set default values
  virtual Int_t InitDefault() =0;
  //!Run the model
  virtual Int_t Run() =0;

  //!Return desired flux in TGraph format
  /*!
    \param Z Charge
    \param A Mass number (0 for sum of all isotopes - !! Except for (1, 0) and (-1, 0) wich are positrons and electrons
    \returns Desired flux vs kinetic energy (GeV/n)
   */
  virtual TGraph* GetFlux(Int_t Z, Int_t A) =0;

  //!Reset the manager
  virtual Int_t Reset() =0;
  //!Print propagation parameters
  virtual void Print() =0;


  //!Set manager verbosity (dummy)
  virtual void SetVerbose( Int_t verbose ) =0;

  //! \name Galaxy Parameters
  //@{
  //! The number of dimensions in the model (2D or 3D)
  virtual Int_t GetNDimensions() =0;
  //!The height of the galactic halo
  virtual Double_t GetGalaxyZdim() =0;

  //! Sets the number of dimensions in the model (2D or 3D)
  virtual void SetNDimensions( Int_t ndim ) =0;
  //! Sets galaxy dimension on X axis (Only works in 3D mode)
  virtual void SetGalaxyXdim( Double_t x_min, Double_t x_max, Double_t dx ) =0; //only 3D case
  //! Sets galaxy dimension on Y axis (Only works in 3D mode)
  virtual void SetGalaxyYdim( Double_t y_min, Double_t y_max, Double_t dy ) =0; //only 3D case
  //! Sets galaxy dimension on Z axis (Works in 2D and 3D mode)
  virtual void SetGalaxyZdim( Double_t z_min, Double_t z_max, Double_t dz ) =0;
  //! Sets galaxy radial dimension (Only works in 2D mode)
  virtual void SetGalaxyRdim( Double_t r_min, Double_t r_max, Double_t dr ) =0; //only 2D case
  //@}

  /** @name Solution Parameters
      Methods controlling the model solution properties
   */
  //@{
  //! Sets the dimentions of the momentum grid
  virtual void SetMomentumGrid( Double_t p_min, Double_t p_max, Double_t p_factor ) =0;
  //! Sets the dimentions of the energy grid
  virtual void SetEnergyGrid( Double_t E_min, Double_t E_max, Double_t E_factor ) =0;
  //! Switches from momentum grid to energy grid
  virtual void SwitchToEnergyGrid() =0;
  //! Switches from energy grid to momentum grid
  virtual void SwitchToMomentumGrid() =0;
  //@}

  /** @name Propagation Parameters
      Methods managing the propagation parameters
      The diffusion coefficient is assumed with a shape \f[ D(\rho) = D_0 \rho^{\delta (\rho)} \f]
      The source for ions/leptons spectrum can be a power-law with up to three spectral breaks in rigidity
   */
  //@{

  //  virtual Double_t GetD_g_0() =0;
  //  virtual Double_t GetD_rigid_br0() =0;

  //! The value of the diffusion coefficient at reference rigidity
  /*!
    \returns The value of \f$ D_0 \f$
   */
  virtual Double_t GetD0_xx() =0;

  //! The value of the diffusion coefficient slope below reference rigidity
  /*!
    \returns The value of \f$ \delta \f$ for \f$ \rho < \rho_b \f$
   */
  virtual Double_t GetD_g_1() =0;

  //! The value of the rigidity break in the diffusion coefficient
  virtual Double_t GetD_rigid_br() =0;

  //! The value of the diffusion coefficient slope above reference rigidity
  /*!
    \returns The value of \f$ \delta \f$ for \f$ \rho > \rho_b \f$
   */
  virtual Double_t GetD_g_2() =0;

  //! The value of the Alfven speed
  /*!
    \returns The value of \f$ v_{Alf} \f$
   */
  virtual Double_t GetAlfvenSpeed() =0;

  //! The spectral index for ions below the first break
  virtual Double_t GetNuc_g_0() =0;
  //! The value of the first rigidity break for ions
  virtual Double_t GetNuc_rigid_br0() =0;
  //! The spectral index for ions between the first and second break
  virtual Double_t GetNuc_g_1() =0;
  //! The value of the second rigidity break for ions
  virtual Double_t GetNuc_rigid_br() =0;
  //! The spectral index for ions between the second and third break
  virtual Double_t GetNuc_g_2() =0;
  //! The value of the third rigidity break for ions
  virtual Double_t GetNuc_rigid_br2() =0;
  //! The spectral index for ions above the third break
  virtual Double_t GetNuc_g_3() =0;

  //! The spectral index for leptons below the first break
  virtual Double_t GetElectron_g_0() =0;
  //! The value of the first rigidity break for leptons
  virtual Double_t GetElectron_rigid_br0() =0;
  //! The spectral index for leptons between the first and second break
  virtual Double_t GetElectron_g_1() =0;
  //! The value of the second rigidity break for leptons
  virtual Double_t GetElectron_rigid_br() =0;
  //! The spectral index for leptons between the second and third break
  virtual Double_t GetElectron_g_2() =0;
  //! The value of the third rigidity break for leptons
  virtual Double_t GetElectron_rigid_br2() =0;
  //! The spectral index for leptons above the third break
  virtual Double_t GetElectron_g_3() =0;


  //! Sets the diffusion coefficient
  /*!
    Sets all values regarding the diffusion coefficient, if you don't want to change a specific parameter use 0 as a value
    \param D0_xx \f$ D_0 \f$
    \param D_g_0 \f$ \delta \f$ for \f$ \rho < \rho_b \f$
    \param D_rigid_br \f$ \rho_b \f$
    \param D_g_1 \f$ \delta \f$ for \f$ \rho > \rho_b \f$
   */
  virtual void SetDiffusionCoefficient( Double_t D0_xx,	Double_t D_g_0,	Double_t D_rigid_br, Double_t D_g_1) =0;

  //!Sets the type of diffusive reacceleration
  /*!
    \param diff_reacc 0=no reacc.; 1,2=incl.diff.reacc.; -1==beta^3 Dxx; 11=Kolmogorov+damping; 12=Kraichnan+damping
   */
  virtual void SetDiffusiveReacceleration( Int_t diff_reacc ) =0;

  //!Sets the value for the Alfven speed
  virtual void SetAlfvenSpeed( Double_t v_Alfven ) =0;

  //!Sets the source spectrum for ions
  /*!
    Sets all values regarding the source spectrum, if you don't want to change a specific parameter use 0 as a value
    \param nuc_g_0 The spectral index for ions below the first break
    \param nuc_rigid_br0 The first rigidity break
    \param nuc_g_1 The spectral index for ions between the first and second break
    \param nuc_rigid_br1 The second rigidity break
    \param nuc_g_2 The spectral index for ions between the second and third break
    \param nuc_rigid_br2 The third rigidity break
    \param nuc_g_3 The spectral index for ions above the third break
   */
  virtual void SetNucleiSourceSpectrum( Double_t nuc_g_0, Double_t nuc_rigid_br0, Double_t nuc_g_1, Double_t nuc_rigid_br1, Double_t nuc_g_2, Double_t nuc_rigid_br2, Double_t nuc_g_3 ) =0;
  //  virtual void SetDeltaPHe( Double_t delta_p_he ) =0;

  //!Sets the source spectrum for leptons
  /*!
    Sets all values regarding the source spectrum, if you don't want to change a specific parameter use 0 as a value
    \param nuc_g_0 The spectral index for ions below the first break
    \param nuc_rigid_br0 The first rigidity break
    \param nuc_g_1 The spectral index for ions between the first and second break
    \param nuc_rigid_br1 The second rigidity break
    \param nuc_g_2 The spectral index for ions between the second and third break
    \param nuc_rigid_br2 The third rigidity break
    \param nuc_g_3 The spectral index for ions above the third break
   */
  virtual void SetElectronSourceSpectrum( Double_t electron_g_0, Double_t electron_rigid_br0, Double_t electron_g_1, Double_t electron_rigid_br1, Double_t electron_g_2, Double_t electron_rigid_br2, Double_t electron_g_3 ) =0;
  //@}

  //  virtual Double_t GetDeltaPHe() =0;

  enum engine_t {
    kGalprop,
    kDragon,
    NumEngines
  };


};

#endif
