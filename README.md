# PropManager
C++ interface to Galprop/DRAGON

## Download
You can find the interface at the github repository https://github.com/valerioformato/PropManager
You can download the project via HTTPS, SSH, or SVN (links on the webpage) or just by

```
git clone https://github.com/valerioformato/PropManager.git PropManager
```

## Prerequisites
 - CMake (at least `v2.8`)
 - ROOT (tested with ROOT `v5.26` or greater)
 - Galprop (tested with `v54_r2504` and `v55_r2713`, retrocompatibility not guaranteed in Galprop)
 - DRAGON  (tested with `v3.0.1` or greater)

#### N.B.
If you want to use Galprop version `55` you should at least have version `4.7` of gcc (or anything that ships with OpenMP version `3.1` or greater). Also the gsl library has to be at least version `1.15`.

##Installation
The installation is done using the CMake toolkit. We recommend to build the project outside the source directory (as always with CMake installations)

```
mkdir <builddir>
cd <builddir>
cmake <sourcedir> -DCMAKE_INSTALL_PREFIX=<installdir> -DCLHEP_CONFIG_EXECUTABLE=<path to your clhep-config> -DGALDEF_PATH=<path to your GALDEF directory> -DDRAGON_XML_PATH=<path to your DRAGON XML files>
make                      [or, make -j n for n core machines]
make install
```

###Build Options

The user can set any CMake variable or option that controls the build process from the cmake command line. The command using the option `-D <var>:<type>=<value>` creates an entry in the CMake cache. Here is a quick summary of the most important ones:

```
-DCMAKE_BUILD_TYPE=Release   # Other build types: Debug, RelWithDebInfo, MinSizeRe
-DCMAKE_INSTALL_PREFIX=<installdir> # installation prefix
-DCMAKE_C_COMPILER=gcc       # What C compiler to use
-DCMAKE_CXX_COMPILER=c++     # What C++ compiler to use
-DCMAKE_F_COMPILER=gfortran  # What fortran compiler to use
-DCMAKE_LINKER=ld            # What linker program to use
```

There are at least two mandatory options to compile `PropManager`, which are:
```
-DCLHEP_CONFIG_EXECUTABLE=<path to your clhep-config> 
-DDRAGON_XML_PATH=<path to your DRAGON XML files>       #If you want to use DRAGON this is the directory where you have your default XML file
```

Other options that may be needed, depending on where you installed Galprop and/or DRAGON are:
```
-DCFITSIO_ROOT_DIR=<path to your cfitsio installation> 
-DCCFITS_ROOT_DIR=<path to your CCfits installation> 
-DXERCESC_ROOT_DIR=<path to your XercesC installation> 
-DHEALPIX_PATH=<path to your Healpix installation> 
-DGALPROP_PATH=<path to your Galprop installation> 
-DGALDEF_PATH=<path to your GALDEF directory>          #If you store your GALDEF files in a custom directory
-DDRAGON_PATH=<path to your DRAGON installation>   
```
