# Common values 
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "OFF")
SET(CPACK_BINARY_STGZ "OFF")
SET(CPACK_BINARY_TZ "OFF")
SET(CPACK_BINARY_ZIP "OFF")
SET(CPACK_COMPONENTS_ALL "")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Humanity")

#Set Cpack Configs by System
INCLUDE(CPackConfig_${CMAKE_SYSTEM_NAME})

#Set Cpack Configs by Platform depends the project.
INCLUDE_IF_EXIST("${PROJECT_SOURCE_DIR}/CPackExtraConfig_${PLATFORM}.cmake")

# cmake templates
IF(PRE_BUILD_LICENSE_FILE)
	Set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/${PRE_BUILD_LICENSE_FILE}")
else()
	Set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_ROOT}/Templates/CPack.GenericLicense.txt")
ENDIF()

SET(CPACK_RESOURCE_FILE_README "${CMAKE_ROOT}/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_ROOT}/Templates/CPack.GenericWelcome.txt")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_ROOT}/Templates/CPack.GenericDescription.txt")
