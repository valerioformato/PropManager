include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include 
		     ${GALPROP_INCLUDE_DIR}
		     ${HEALPIX_INCLUDE_DIR}
		     ${CCFITS_INCLUDE_DIR}
		     ${CFITSIO_INCLUDE_DIR}
		     ${CLHEP_INCLUDE_DIR}
		     ${ROOT_INCLUDE_DIR}
		     )

if( GALPROP_VERSION VERSION_GREATER 55 )
    find_package(XercesC)
endif()

set( GALPROP_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/GalpropManager.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/GalpropManager_setters.cpp )

add_definitions( ${GALPROP_DEFINITIONS} 
		 -DGALDEF_PATH=\"${USER_GALDEF_PATH}\")


add_library(GalpropManagerStatic STATIC ${GALPROP_SOURCES})
set_target_properties(GalpropManagerStatic PROPERTIES OUTPUT_NAME GalpropManager)

add_library(GalpropManager SHARED ${GALPROP_SOURCES})

target_link_libraries( GalpropManager
		       gfortran
		       gsl
		       gslcblas
                      ${ROOT_LIBRARIES}
		      ${XERCESC_LIBRARIES}
		       "-Wl,--whole-archive" 
                      ${GALPROP_LIBRARIES} 
                      ${HEALPIX_LIBRARIES} 
                      ${CCFITS_LIBRARIES} 
#                      ${CFITSIO_LIBRARIES} 
		      ${CLHEP_LIBRARIES}
		       "-Wl,--no-whole-archive" 
		       )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}
           FILES_MATCHING PATTERN "*.h" 
           PATTERN ".git" EXCLUDE
           PATTERN "build" EXCLUDE
          )
install(TARGETS GalpropManager DESTINATION lib)
