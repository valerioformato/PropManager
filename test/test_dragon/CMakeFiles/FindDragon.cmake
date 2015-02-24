if( NOT DEFINED DRAGON_PATH )
    find_path( DRAGON_PATH
    	       NAMES include/input.h
    	       PATHS $ENV{AMSVERYBASE} $ENV{AMSVERYBASE}/Dragon/MultiThreaded $ENV{AMSVERYBASE}/Dragon/SingleThreaded
	       DOC "Dragon base directory" )
endif()

find_path( DRAGON_INCLUDE_DIR
	   NAMES input.h
	   PATHS ${DRAGON_PATH}/include
	   DOC "Dragon include directory" )

find_library( DRAGON_LIBRARY
	      NAMES libDRAGON.a
	      PATHS ${DRAGON_PATH}/lib
	      DOC "Dragon library" )

find_library( TIXML_LIBRARY
	      NAMES libTiXML.a
	      PATHS ${DRAGON_PATH}/lib
	      DOC "TiXML library" )

find_library( CPARAM_LIBRARY
	      NAMES libcparamlib.a
	      PATHS ${DRAGON_PATH}/lib
	      DOC "cparamlib library" )


include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(DRAGON DEFAULT_MSG DRAGON_PATH)

message(STATUS "Found DRAGON headers: ${DRAGON_INCLUDE_DIR}")
message(STATUS "Found DRAGON libraries: ${DRAGON_LIBRARY} ${TIXML_LIBRARY} ${CPARAM_LIBRARY}")

if(DRAGON_FOUND)
    set(DRAGON_LIBRARIES ${DRAGON_LIBRARY} ${TIXML_LIBRARY} ${CPARAM_LIBRARY})
    set(DRAGON_INCLUDE_DIRS ${DRAGON_INCLUDE_DIR})
    set(DRAGON_DEFINITIONS 
        -DDRAGON_DATA_PATH=\"${DRAGON_PATH}/config_files/\")
endif()


# Tell cmake GUIs to ignore the "local" variables.
mark_as_advanced(DRAGON_INCLUDE_DIR DRAGON_LIBRARY)
