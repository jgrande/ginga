# -*- cmake -*-

# - Find zlib with WINAPI call method
# Find the zlib includes and library
# This module defines
#  WINZLIB_INCLUDE_DIR, where to find db.h, etc.
#  WINZLIB_LIBRARIES, the libraries needed to use zlib.
#  WINZLIB_FOUND, If false, do not try to use zlib.
# also defined, but not for general use are
#  WINZLIB_LIBRARY, where to find the zlib library.

FIND_PATH(WINZLIB_INCLUDE_DIR zlib.h
$ENV{WINZLIB_DIR}/include
/usr/include
)

SET(WINZLIB_NAMES ${WINZLIB_NAMES} zlibwapi )
FIND_LIBRARY(WINZLIB_LIBRARIES
  NAMES ${WINZLIB_NAMES}
  PATHS /usr/lib /usr/local/lib $ENV{WINZLIB_DIR}/lib
  )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set WINZLIB_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(WINZLIB DEFAULT_MSG WINZLIB_LIBRARIES WINZLIB_INCLUDE_DIR)
mark_as_advanced( WINZLIB_INCLUDE_DIR WINZLIB_LIBRARIES )
