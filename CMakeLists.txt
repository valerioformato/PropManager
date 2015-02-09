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
if(NOT DEFINED CLHEP_CONFIG_EXECUTABLE)
       message(FATAL_ERROR "CHLEP config executable not defined. Use -DCMAKE_CLHEP_EXECUTABLE flag to specify path")
endif()
set(CLHEP_CONFIG_EXECUTABLE ${CLHEP_CONFIG_EXECUTABLE} CACHE FILEPATH "Path to chlep-config")
find_package(CLHEP)

include_directories( ${CMAKE_SOURCE_DIR}/include 
		     ${ROOT_INCLUDE_DIR} )

set( CMAKE_C_FLAGS "-g -fPIC -Wall -fno-common -pthread -fopenmp" )
set( CMAKE_CXX_FLAGS "-g -fPIC -Wall -fno-common -pthread -fopenmp" )

if( GALPROP_FOUND AND HEALPIX_FOUND AND CCFITS_FOUND )
  message(STATUS "Enabling GalpropManager package")

  if(NOT DEFINED GALDEF_PATH)
    message( FATAL_ERROR "GALDEF_PATH not defined. Please specify path to your GALDEF directory with -DGALDEF_PATH=/pathtodir" )
  endif()	    

  set( USER_GALDEF_PATH ${GALDEF_PATH}/ CACHE PATH "Path to your GALDEF directory" )

  add_subdirectory( source/GalpropManager )

endif()

if( DEFINED DRAGON_DIR )
  add_subdirectory( source/DragonManager )
endif()

set( SOURCES src/PropManager.cpp )

add_library( PropManager SHARED ${SOURCES} )

target_link_libraries( PropManager
		       GalpropManager
		       )


