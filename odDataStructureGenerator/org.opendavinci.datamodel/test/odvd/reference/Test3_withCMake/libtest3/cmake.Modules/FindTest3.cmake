# Test3 - Data structure library generated by DataStructureGenerator.
###########################################################################
# Try to find Test3 library.
# The user can specify an additional search path using the CMake variable
# TEST3_DIR
# First, search at the specific user path setting.
IF(NOT ("${TEST3_DIR}" STREQUAL ""))
    FIND_PATH(TEST3_INCLUDE_DIR test3/GeneratedHeaders_Test3.h
                 NAMES test3
                 PATHS ${TEST3_DIR}/include
                 NO_DEFAULT_PATH)
    FIND_LIBRARY(TEST3_LIBRARY
                 NAMES test3 test3-static
                 PATHS ${TEST3_DIR}/lib
                 NO_DEFAULT_PATH)
ENDIF()
IF(   ("${TEST3_INCLUDE_DIR}" STREQUAL "TEST3_INCLUDE_DIR-NOTFOUND")
   OR ("${TEST3_DIR}" STREQUAL "") )
    MESSAGE(STATUS "Trying to find Test3 in default paths.")
    # If not found, use the system's search paths.
    FIND_PATH(TEST3_INCLUDE_DIR test3/GeneratedHeaders_Test3.h
                 NAMES test3
                 PATHS /usr/include
                       /usr/local/include)
    FIND_LIBRARY(TEST3_LIBRARY
                 NAMES test3 test3-static
                 PATHS /usr/lib
                       /usr/lib64
                       /usr/local/lib
                       /usr/local/lib64)
ENDIF()
IF("${TEST3_INCLUDE_DIR}" STREQUAL "")
    MESSAGE(FATAL_ERROR "Could not find Test3 library.")
ENDIF()
###########################################################################
# Set linking libraries.
SET(TEST3_LIBRARIES ${TEST3_LIBRARY})
SET(TEST3_INCLUDE_DIRS ${TEST3_INCLUDE_DIR})
###########################################################################
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibTest3 DEFAULT_MSG
                                  TEST3_LIBRARY TEST3_INCLUDE_DIR)
MARK_AS_ADVANCED(TEST3_INCLUDE_DIR TEST3_LIBRARY)
