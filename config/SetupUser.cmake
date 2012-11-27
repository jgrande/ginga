# Build shared file
set(BUILD_SHARED 0)

set(CMAKE_INSTALL_PREFIX $ENV{DEPOT}/install.${PLATFORM})
set(CMAKE_CONFIG_INSTALL_PREFIX $ENV{DEPOT}/install.${PLATFORM})

LIST(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_INSTALL_PREFIX} )

# Override build type,  Release, Debug, RelWithDebInfo
set(CMAKE_BUILD_TYPE "Release")

set(SILENT 1)

# Set compile tests in true
set(COMPILE_TESTS 1)
# Set run tests in false
set(RUN_TESTS 0)

# Ginga
set(SYS_PLAYER_USE_VLC 1)
if(WIN32)
set(SYS_HTML_USE_CEF 1)
else()
set(SYS_HTML_USE_GTK 1)
endif(WIN32)
