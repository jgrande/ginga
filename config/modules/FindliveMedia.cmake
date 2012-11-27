# -*- cmake -*-

# - Find liveMedia
# Find the liveMedia includes and library
# This module defines
#  LIVEMEDIA_INCLUDE_DIRS, where to find liveMedia.hh, etc.
#  LIVEMEDIA_LIBRARIES, the libraries needed to use liveMedia.
# also defined, but not for general use are
#  LIVEMEDIA_LIBRARY, where to find the liveMedia library.

# Find liveMedia
FIND_PATH(LIVEMEDIA_INCLUDE_DIR liveMedia.hh
$ENV{LIVEMEDIA_DIR}/include
/usr/local/include/liveMedia
/usr/local/include
/usr/include/liveMedia
/usr/include
)

# Find UsageEnvironment
FIND_PATH(USAGEENVIRONMENT_INCLUDE_DIR UsageEnvironment.hh
$ENV{USAGEENVIRONMENT_DIR}/include
/usr/local/include/UsageEnvironment
/usr/local/include
/usr/include/UsageEnvironment
/usr/include
)

# Find BasicUsageEnvironment
FIND_PATH(BASICUSAGEENVIRONMENT_INCLUDE_DIR BasicUsageEnvironment.hh
$ENV{BASICUSAGEENVIRONMENT_DIR}/include
/usr/local/include/BasicUsageEnvironment
/usr/local/include
/usr/include/BasicUsageEnvironment
/usr/include
)

# Find groupsock
FIND_PATH(GROUPSOCK_INCLUDE_DIR GroupsockHelper.hh
$ENV{GROUPSOCK_DIR}/include
/usr/local/include/groupsock
/usr/local/include
/usr/include/groupsock
/usr/include
)

set ( LIVEMEDIA_INCLUDE_DIRS
	${LIVEMEDIA_INCLUDE_DIR}
	${GROUPSOCK_INCLUDE_DIR}
	${BASICUSAGEENVIRONMENT_INCLUDE_DIR}
	${USAGEENVIRONMENT_INCLUDE_DIR}
)

FIND_LIBRARY(LIVEMEDIA_LIBRARY
  liveMedia
  /usr/lib /usr/local/lib $ENV{LIVEMEDIA_DIR}/lib
)

FIND_LIBRARY(USAGEENVIRONMENT_LIBRARY
  UsageEnvironment
  /usr/lib /usr/local/lib $ENV{USAGEENVIRONMENT_DIR}/lib
)

FIND_LIBRARY(BASICUSAGEENVIRONMENT_LIBRARY
  BasicUsageEnvironment
  /usr/lib /usr/local/lib $ENV{BASICUSAGEENVIRONMENT_DIR}/lib
)

FIND_LIBRARY(GROUPSOCK_LIBRARY
  groupsock
  /usr/lib /usr/local/lib $ENV{GROUPSOCK_DIR}/lib
)

set ( LIVEMEDIA_LIBRARIES
	${LIVEMEDIA_LIBRARY}
	${GROUPSOCK_LIBRARY}
	${BASICUSAGEENVIRONMENT_LIBRARY}
	${USAGEENVIRONMENT_LIBRARY}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(liveMedia DEFAULT_MSG LIVEMEDIA_LIBRARIES LIVEMEDIA_INCLUDE_DIRS)
mark_as_advanced( LIVEMEDIA_INCLUDE_DIRS LIVEMEDIA_LIBRARIES )
