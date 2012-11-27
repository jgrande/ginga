set(PLATFORM LINUX)

# This one is important
set(CMAKE_SYSTEM_NAME Linux)
# This one not so much
set(CMAKE_SYSTEM_VERSION 1)

#Set optimization level for release build
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
#Set optimization level for release build
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# TODO: ADD_PLATFORM_LIBRARIES("-lrt")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lrt")

# specify the strip tool
SET(STRIP_TOOL strip )
