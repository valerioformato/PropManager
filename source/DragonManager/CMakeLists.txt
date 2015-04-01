include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include 
		     ${DRAGON_INCLUDE_DIR}
#		     ${HEALPIX_INCLUDE_DIR}
#		     ${CCFITS_INCLUDE_DIR}
		     ${CFITSIO_INCLUDE_DIR}
#		     ${CLHEP_INCLUDE_DIR}
		     ${ROOT_INCLUDE_DIR}
		     )

set( DRAGON_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/DragonInterfaces.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/DragonManager.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/DragonManager_setters.cpp )

add_definitions( ${DRAGON_DEFINITIONS}
		 -DDRAGON_XML_PATH=\"${USER_DRAGON_XML_PATH}\")


add_library(DragonManagerStatic STATIC ${DRAGON_SOURCES})
set_target_properties(DragonManagerStatic PROPERTIES OUTPUT_NAME DragonManager)

add_library(DragonManager SHARED ${DRAGON_SOURCES})

target_link_libraries( DragonManager
		       gfortran
		       gsl
		       gslcblas
                      ${ROOT_LIBRARIES}
		       "-Wl,--whole-archive" 
                      ${DRAGON_LIBRARIES} 
#                     ${HEALPIX_LIBRARIES} 
#                     ${CCFITS_LIBRARIES} 
                      ${CFITSIO_LIBRARIES} 
#		      ${CLHEP_LIBRARIES}
		       "-Wl,--no-whole-archive" 
		       )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}
           FILES_MATCHING PATTERN "*.h" 
           PATTERN ".git" EXCLUDE
           PATTERN "build" EXCLUDE
          )
install(TARGETS DragonManager DESTINATION lib)
