# PropManager
C++ interface to Galprop/DRAGON

## Download
You can find the interface at the github repository https://github.com/valerioformato/PropManager
You can download the priject via HTTPS, SSH, or SVN (links on the webpage) or just by

```
git clone https://github.com/valerioformato/PropManager.git PropManager
```

## Prerequisites
 - CMake (at least v2.6)
 - ROOT (tested with ROOT v5.26 or greater)
 - Galprop (tested with v54_r2504, retrocompatibility not guaranteed in Galprop)
 - DRAGON  (tested with v3.0.1 or greater)

##Installation
The installation is done using the CMake toolkit. We recommend to build the project outside the source directory (as always with CMake installations)

```
mkdir <builddir>
cd <builddir>
cmake <sourcedir> -DCMAKE_INSTALL_PREFIX=<installdir> -DCLHEP_CONFIG_EXECUTABLE=<path to your clhep-config> -DGALPROP_PATH=<path to your galprop installation> -DGALDEF_PATH=<path to your GALDEF directory>  -DDRAGON_PATH=<path to your DRAGON installation> -DDRAGON_XML_PATH=<path to your DRAGON XML files>
make                      [or, make -j n for n core machines]
make install
```