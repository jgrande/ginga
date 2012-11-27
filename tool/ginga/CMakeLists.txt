CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE($ENV{DEPOT}/config/Tvd.cmake)

# Workaround, to eliminate -rdynamic from the linker
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

GET_GIT_REVISION (TAG_VERSION BUILD_VERSION )

Add_Bin (
	PROJECT_NAME "ginga"
	PROJECT_VERSION 2.0.0
	PROJECT_DESCRIPTION "Lifia implementation of Ginga reference specification for south american digital TV"
	PACKAGE_NAME "ginga.ar"
	SUBSYSTEM Windows
	BIN_DESTINATION bin
	ICON_NAME "ginga.rc"
	LICENSE_FILE "COPYING"
)

INSTALL( DIRECTORY examples/
	DESTINATION share/ginga/examples
	FILES_MATCHING PATTERN "*.*"
)
INSTALL( DIRECTORY fonts/
	DESTINATION share/ginga/font
	FILES_MATCHING PATTERN "*.ttf"
		PATTERN "*svn*" EXCLUDE
)

CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/ginga.version.cin
	${PROJECT_BINARY_DIR}/ginga.version
)

INSTALL( FILES ${PROJECT_BINARY_DIR}/ginga.version
	DESTINATION etc
)
