cmake_minimum_required(VERSION 2.6)

project(PropManager)

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                  OUTPUT_VARIABLE GCC_VERSION)
  if( NOT (GCC_VERSION VERSION_GREATER 4.4.7 OR GCC_VERSION VERSION_EQUAL 4.4.7) )
    message( FATAL_ERROR "This version of gcc doen't support OpenMP. gcc 4.4.7 or greater is needed" )
  endif()	
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  message( FATAL_ERROR "Clang full support for OpenMP is still not available. Please switch to gcc." )
endif()

set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeFiles )
find_package(ROOT)
find_package(Galprop)
find_package(HealPix)
find_package(CCFits)

include_directories( ${CMAKE_SOURCE_DIR}/include 
		     /storage/gpfs_ams/ams/users/vformato/devel/PropManager/include
		     ${GALPROP_INCLUDE_DIR}
		     ${HEALPIX_INCLUDE_DIR}
		     ${CCFITS_INCLUDE_DIR}
		     ${CFITSIO_INCLUDE_DIR}
		     ${ROOT_INCLUDE_DIR} )



set( SOURCES 
     src/test.cpp 
     )

set( CMAKE_C_FLAGS "-g -Wall -fno-common -pthread -fopenmp" )
set( CMAKE_CXX_FLAGS "-g -Wall -fno-common -pthread -fopenmp" )

add_definitions( ${GALPROP_DEFINITIONS} 
		 -DGALDEF_PATH=\"${GALDEF_PATH}\")

add_executable( test ${SOURCES} )
target_link_libraries( test 
		       /storage/gpfs_ams/ams/users/vformato/devel/PropManager/build/libPropManager.so
		       /storage/gpfs_ams/ams/users/vformato/devel/PropManager/build/source/GalpropManager/libGalpropManager.so
		       gfortran
		       gfortranbegin
		       gsl
		       gslcblas
		       ${ROOT_LIBRARIES} )
