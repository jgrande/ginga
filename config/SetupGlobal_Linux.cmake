# Set warning level 
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread") # add "-pthread" here as a workaround for a bug in gtest (https://groups.google.com/group/googletestframework/browse_thread/thread/d00d069043a2f22b#)

# Set debug flags
#set(CMAKE_CXX_FLAGS_DEBUG "-rdynamic")

# This macro adds the executable for the System
MACRO(add_system_executable PROJECT_NAME PROJECT_NAME_SOURCE_FILES)
    	  ADD_EXECUTABLE(${PROJECT_NAME} ${${PROJECT_NAME_SOURCE_FILES}})
ENDMACRO(add_system_executable)
