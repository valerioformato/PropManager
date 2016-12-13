# Find HealPix
# ~~~~~~~~
# Copyright (c) 2014, Gurprit Singh
# Redistribution and use is allowed.
#
# HEALPIX package includes following libraries:
# healpix_cxx cxxsupport sharp fftpack c_utils  /*Order of these libraries is very important to resolve dependencies*/
#
# Once run this will define:
#
# HEALPIX_FOUND:	    healpixsystem has HEALPIX lib
# HEALPIX_LIBRARIES:	    full path to the HEALPIX package libraries
# HEALPIX_INCLUDE_DIR:	    where to find headers
#


if(NOT DEFINED HEALPIX_PATH)
SET(HEALPIX_INCLUDEPATH $ENV{AMSVERYBASE}/galprop/Healpix/src/cxx/generic_gcc/include)
SET(HEALPIX_LIBPATH     $ENV{AMSVERYBASE}/galprop/Healpix/src/cxx/generic_gcc/lib)
else()
SET(HEALPIX_INCLUDEPATH ${HEALPIX_PATH}/include)
SET(HEALPIX_LIBPATH     ${HEALPIX_PATH}/lib)
endif()

FIND_PATH(HEALPIX_INCLUDE_DIR
NAMES
        healpix_base.h
PATHS
        /usr/include
        /usr/local/include
        ${HEALPIX_INCLUDEPATH}
)

FIND_LIBRARY(HEALPIX_LIBRARIES
NAMES
        healpix_cxx
PATHS
        /usr/lib
        /usr/local/lib
        ${HEALPIX_LIBPATH}
)
FIND_LIBRARY(HEALPIX_CXXSUPPORT_LIBRARIES
NAMES
        cxxsupport
PATHS
        /usr/lib
        /usr/local/lib
        ${HEALPIX_LIBPATH}
)
FIND_LIBRARY(HEALPIX_SHARP_LIBRARIES
NAMES
        sharp
PATHS
        /usr/lib
        /usr/local/lib
        ${HEALPIX_LIBPATH}
)
FIND_LIBRARY(HEALPIX_FFTPACK_LIBRARIES
NAMES
        fftpack
PATHS
        /usr/lib
        /usr/local/lib
        ${HEALPIX_LIBPATH}
)
FIND_LIBRARY(HEALPIX_CUTILS_LIBRARIES
NAMES
        c_utils
PATHS
        /usr/lib
        /usr/local/lib
        ${HEALPIX_LIBPATH}
)

SET(HEALPIX_FOUND FALSE)
IF(HEALPIX_INCLUDE_DIR AND HEALPIX_LIBRARIES AND HEALPIX_CXXSUPPORT_LIBRARIES AND HEALPIX_FFTPACK_LIBRARIES AND HEALPIX_CUTILS_LIBRARIES)
SET(HEALPIX_LIBRARIES ${HEALPIX_LIBRARIES}
${HEALPIX_CXXSUPPORT_LIBRARIES}
${HEALPIX_FFTPACK_LIBRARIES}
${HEALPIX_CUTILS_LIBRARIES}
)
if(HEALPIX_SHARP_LIBRARIES)
SET(HEALPIX_LIBRARIES ${HEALPIX_LIBRARIES}
${HEALPIX_SHARP_LIBRARIES}
)
endif()
SET(HEALPIX_FOUND TRUE)
MESSAGE(STATUS "HealPix Found!")
MESSAGE(STATUS "HEALPIX_INCLUDE_DIR=${HEALPIX_INCLUDE_DIR}")
MESSAGE(STATUS "HEALPIX_LIBRARIES=${HEALPIX_LIBRARIES}")
ENDIF()


MARK_AS_ADVANCED(
HEALPIX_INCLUDE_DIR
HEALPIX_LIBRARIES
HEALPIX_FOUND
)