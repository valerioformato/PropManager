if( NOT DEFINED GALPROP_PATH )
    find_path( GALPROP_PATH
    	       NAMES include/Galprop.h
    	       PATHS $ENV{AMSVERYBASE} $ENV{AMSVERYBASE}/galprop
	       DOC "Galprop base directory" )
endif()

execute_process( COMMAND ${GALPROP_PATH}/bin/galprop-config --version
		 OUTPUT_VARIABLE GALPROP_VERSION 
		 OUTPUT_STRIP_TRAILING_WHITESPACE )
string(REPLACE "." ";" VERSION_LIST ${GALPROP_VERSION})
list(GET VERSION_LIST 0 GALPROP_VERSION_MAJOR)


find_path( GALPROP_INCLUDE_DIR
	   NAMES Galprop.h
	   PATHS ${GALPROP_PATH}/include
	   DOC "Galprop include directory" )

find_library( GALPROP_LIBRARY
	      NAMES libgalprop.a
	      PATHS ${GALPROP_PATH}/lib
	      DOC "Galprop library" )

find_library( SKYMAP_LIBRARY
	      NAMES libskymap.a
	      PATHS ${GALPROP_PATH}/lib
	      DOC "Skymap library" )

if( GALPROP_VERSION VERSION_GREATER 55 )
    find_library( NUCLEI_LIBRARY
    		  NAMES libnuclei.a	
		  PATHS ${GALPROP_PATH}/lib
		  DOC "Nuclei library" )

    find_library( PROC_LIBRARY
    		  NAMES libprocesses.a	
		  PATHS ${GALPROP_PATH}/lib
		  DOC "Processes library" )
endif()

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args( GALPROP FOUND_VAR GALPROP_FOUND
			           REQUIRED_VARS GALPROP_PATH 
 				   VERSION_VAR   GALPROP_VERSION )

message(STATUS "Found GALPROP headers: ${GALPROP_INCLUDE_DIR}")
message(STATUS "Found GALPROP libraries: ${GALPROP_LIBRARY} ${SKYMAP_LIBRARY}")

if(GALPROP_FOUND)
    set(GALPROP_LIBRARIES ${GALPROP_LIBRARY} ${SKYMAP_LIBRARY})
    if( GALPROP_VERSION VERSION_GREATER 55 )
    	set(GALPROP_LIBRARIES ${GALPROP_LIBRARIES} ${NUCLEI_LIBRARY} ${PROC_LIBRARY})
    endif()
    set(GALPROP_INCLUDE_DIRS ${GALPROP_INCLUDE_DIR} )
    set(GALPROP_DEFINITIONS 
        -DGALPROP_MAIN_V=${GALPROP_VERSION_MAJOR}
        -DGALPROP_DATA_PATH=\"${GALPROP_PATH}/DATA/\"
        -DFITS_PATH=\"${GALPROP_PATH}/FITS/\")

    if(NOT DEFINED GALDEF_PATH)
        set(GALDEF_PATH ${GALPROP_PATH}/GALDEF) 
	message(WARNING " GALDEF_PATH not defined. Using the default path ${GALDEF_PATH} \n For a user-defined path please specify the  path to your GALDEF directory with -DGALDEF_PATH=/pathtodir" )
    endif()
endif()


# Tell cmake GUIs to ignore the "local" variables.
mark_as_advanced(GALPROP_INCLUDE_DIR GALPROP_LIBRARY)
