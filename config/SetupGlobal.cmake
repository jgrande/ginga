# Set install, and config install PREFIX
set(CMAKE_INSTALL_PREFIX        $ENV{DEPOT}/install/${PLATFORM})
set(CMAKE_CONFIG_INSTALL_PREFIX $ENV{DEPOT}/install/${PLATFORM})
# setear la variable de entorno DESTDIR antes de construir para guardarlo en un directorio intermedio


# Set build type Release, Debug, RelWithDebInfo if wasnt setted before, you use this to override build_type param 
#   set(CMAKE_BUILD_TYPE "Release")
#   set(CMAKE_BUILD_TYPE "Debug")
#   set(CMAKE_BUILD_TYPE "RelWithDebInfo")
#   set(CMAKE_BUILD_TYPE "MinSizeRel")

IF(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_definitions(/D_DEBUG)
ELSE()
	add_definitions(/DNDEBUG)
	IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
		SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
		SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
	ENDIF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
ENDIF()

## Set warning level 
#set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Set debug flags
#set(CMAKE_CXX_FLAGS_DEBUG "-rdynamic")

# Set compile tests in true
set(COMPILE_TESTS 1)
# Set run tests in false
set(RUN_TESTS 0)
# Set info mode to off 
set(SILENT 1)

# Set lib prefix to tvd
set(LIB_PREFIX dtv)

#destination to lib install
set(LIB_DESTINATION "lib/lifia")

#dir to include files
set(INCLUDE_DIR "include/lifia")

# set to 0 when not a release candidate, non zero means that any generated 
# svn tags will be treated as release candidates of given number
SET(PROJECT_RELEASE_CANDIDATE 0)


OPTION_IF_EMPTY(BUILD_SHARED "Build the library shared." OFF)
