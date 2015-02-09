# - Try to find CLHEP.
# Once executed, this module will define:
# Variables defined by this module:
#  CLHEP_FOUND        - system has CLHEP
#  CLHEP_INCLUDE_DIR  - the CLHEP include directory (cached)
#  CLHEP_INCLUDE_DIRS - the CLHEP include directories
#                         (identical to CLHEP_INCLUDE_DIR)
#  CLHEP_LIBRARY      - the CLHEP library (cached)
#  CLHEP_LIBRARIES    - the CLHEP libraries
#                         (identical to CLHEP_LIBRARY)
# 
# This module will use the following enviornmental variable
# when searching for CLHEP:
#  CLHEP_ROOT_DIR     - CLHEP root directory
#

if(NOT CLHEP_FOUND)

    if(DEFINED CLHEP_CONFIG_EXECUTABLE)
        execute_process(COMMAND ${CLHEP_CONFIG_EXECUTABLE} --prefix OUTPUT_VARIABLE CLHEP_ROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif()

    string(REPLACE \" "" CLHEP_ROOT_DIR  ${CLHEP_ROOT} )

    set(CLHEP_INCLUDE_DIR ${CLHEP_ROOT_DIR}/include)
    set(CLHEP_LIBRARY ${CLHEP_ROOT_DIR}/lib/libCLHEP.so)
message(WARNING "${CLHEP_INCLUDE_DIR}")

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(CLHEP DEFAULT_MSG
        CLHEP_LIBRARY CLHEP_INCLUDE_DIR)

    set(CLHEP_INCLUDE_DIRS ${CLHEP_INCLUDE_DIR})
    set(CLHEP_LIBRARIES ${CLHEP_LIBRARY})

    mark_as_advanced(CLHEP_INCLUDE_DIR CLHEP_LIBRARY)

endif(NOT CLHEP_FOUND)