include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include 
		     ${GALPROP_INCLUDE_DIR}
		     ${HEALPIX_INCLUDE_DIR}
		     ${CCFITS_INCLUDE_DIR}
		     ${CFITSIO_INCLUDE_DIR}
		     ${CLHEP_INCLUDE_DIR}
		     ${ROOT_INCLUDE_DIR}
		     )

set( GALPROP_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/GalpropManager.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/GalpropManager_setters.cpp )

add_definitions( ${GALPROP_DEFINITIONS} 
		 -DGALDEF_PATH=\"${GALDEF_PATH}\")


add_library(GalpropManagerStatic STATIC ${GALPROP_SOURCES})
set_target_properties(GalpropManagerStatic PROPERTIES OUTPUT_NAME GalpropManager)

add_library(GalpropManager SHARED ${GALPROP_SOURCES})

target_link_libraries( GalpropManager
		       gfortran
		       gsl
		       gslcblas
                      ${ROOT_LIBRARIES}
		       "-WL, --whole-archive" 
                      ${GALPROP_LIBRARIES} 
                      ${HEALPIX_LIBRARIES} 
                      ${CCFITS_LIBRARIES} 
                      ${CFITSIO_LIBRARIES} 
		      ${CLHEP_LIBRARIES}
		       GalpropManagerStatic 
		       "-WL, --no-whole-archive" 
		       )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ./
           FILES_MATCHING PATTERN "*.h" 
           PATTERN ".git" EXCLUDE
           PATTERN "build" EXCLUDE
          )
install(TARGETS GalpropManager DESTINATION lib)
