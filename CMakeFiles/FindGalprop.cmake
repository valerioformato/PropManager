if( NOT DEFINED GALPROP_PATH )
    find_path( GALPROP_PATH
    	       NAMES include/Galprop.h
    	       PATHS $ENV{AMSVERYBASE} $ENV{AMSVERYBASE}/galprop
	       DOC "Galprop base directory" )
endif()

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


include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(GALPROP DEFAULT_MSG GALPROP_PATH)

message(STATUS "Found GALPROP: ${GALPROP_INCLUDE_DIR}")
message(STATUS "Found GALPROP: ${GALPROP_LIBRARY} ${SKYMAP_LIBRARY}")

if(GALPROP_FOUND)
    set(GALPROP_LIBRARIES ${GALPROP_LIBRARY} ${SKYMAP_LIBRARY})
    set(GALPROP_INCLUDE_DIRS ${GALPROP_INCLUDE_DIR} )
    set(GALPROP_DEFINITIONS 
        -DGALPROP_DATA_PATH=\"${GALPROP_PATH}/DATA/\"
        -DFITS_PATH=\"${GALPROP_PATH}/FITS/\")
endif()


# Tell cmake GUIs to ignore the "local" variables.
mark_as_advanced(GALPROP_INCLUDE_DIR GALPROP_LIBRARY)
