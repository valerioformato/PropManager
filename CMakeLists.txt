cmake_minimum_required(VERSION 2.6)

project(PropManager)

# -------------------------------------------------------------------
# ----------- Checking compiler compatibility with OpenMP -----------
# -------------------------------------------------------------------
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                  OUTPUT_VARIABLE GCC_VERSION)
  if( NOT (GCC_VERSION VERSION_GREATER 4.4.7 OR GCC_VERSION VERSION_EQUAL 4.4.7) )
    message( FATAL_ERROR "This version of gcc doen't support OpenMP. gcc 4.4.7 or greater is needed" )
  endif()	
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  message( FATAL_ERROR "Clang full support for OpenMP is still not available. Please switch to gcc." )
endif()

# -------------------------------------------------------------------
# ----------------- Searching for required packages -----------------
# -------------------------------------------------------------------
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeFiles )
find_package(ROOT)
find_package(Galprop)
find_package(Dragon)
find_package(HealPix)
find_package(CCFits)
if(NOT DEFINED CLHEP_CONFIG_EXECUTABLE)
       message(FATAL_ERROR "CHLEP config executable not defined. Use -DCMAKE_CLHEP_EXECUTABLE option to specify path")
endif()
set(CLHEP_CONFIG_EXECUTABLE ${CLHEP_CONFIG_EXECUTABLE} CACHE FILEPATH "Path to chlep-config")
find_package(CLHEP)

# -------------------------------------------------------------------
# ---------------------- Preparing compilation ----------------------
# -------------------------------------------------------------------
include_directories( ${CMAKE_SOURCE_DIR}/include 
		     ${ROOT_INCLUDE_DIR} )

set( CMAKE_C_FLAGS "-g -fPIC -Wall -fno-common -pthread -fopenmp" )
set( CMAKE_CXX_FLAGS "-g -fPIC -Wall -fno-common -pthread -fopenmp" )

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

# -------------------------------------------------------------------
# ------------------ Enable managers only if found ------------------
# -------------------------------------------------------------------
if( GALPROP_FOUND AND HEALPIX_FOUND AND CCFITS_FOUND )

  message(STATUS "Enabling GalpropManager package")

  set( USER_GALDEF_PATH ${GALDEF_PATH}/ CACHE PATH "Path to your GALDEF directory" )

  add_subdirectory( source/GalpropManager )

endif()


if( DRAGON_FOUND AND CFITSIO_FOUND )

  message(STATUS "Enabling DragonManager package")

  if(NOT DEFINED DRAGON_XML_PATH)
    message( FATAL_ERROR "DRAGON_XML_PATH not defined. Please specify path to your DRAGON XML directory with -DDRAGON_XML_PATH=/pathtodir" )
  endif()	    

  set( USER_DRAGON_XML_PATH ${DRAGON_XML_PATH}/ CACHE PATH "Path to your DRAGON XML directory" )

  add_subdirectory( source/DragonManager )

endif()


# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)


set( SOURCES src/PropManager.cpp )

add_library( PropManager SHARED ${SOURCES} )

target_link_libraries( PropManager
		       GalpropManager
		       DragonManager
		       )

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}
           FILES_MATCHING PATTERN "*.h" 
           PATTERN ".git" EXCLUDE
           PATTERN "build" EXCLUDE
          )
install(TARGETS PropManager DESTINATION lib)
