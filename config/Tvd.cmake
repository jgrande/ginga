FILE(TO_CMAKE_PATH $ENV{DEPOT} DEPOT)
SET (CONFIG_PATH ${DEPOT}/config)
SET (FIND_PATH ${CONFIG_PATH}/modules )

LIST(APPEND CMAKE_MODULE_PATH ${CONFIG_PATH} ${FIND_PATH})
  
INCLUDE(Utils)
INCLUDE(SetupGlobal)
INCLUDE(Test)
include(internal_utils_macros) 	#include the Tvd.cmake own macros 

# Setup user config
SET(SETUP_USER $ENV{USER_CONFIG_FILE})
IF(NOT SETUP_USER)
	SET(SETUP_USER ${CONFIG_PATH}/SetupUser.cmake)
ENDIF(NOT SETUP_USER)

INCLUDE_IF_EXIST(${SETUP_USER})
IF(FILE_INCLUDED)
	MESSAGE( STATUS "USER CONFIG FILE: ${SETUP_USER}" )
ENDIF()
INCLUDE(${CMAKE_TOOLCHAIN_FILE})
SET(CMAKE_FIND_ROOT_PATH $ENV{DESTDIR}${CMAKE_INSTALL_PREFIX} ${PLATFORM_FIND_ROOT_PATH})
INCLUDE_IF_EXIST(${CONFIG_PATH}/SetupGlobal_${CMAKE_SYSTEM_NAME}.cmake)
LIST(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_INSTALL_PREFIX} )

#List of required variables for the parse_arguments()
SET(PRE_BUILD_VARIABLES "PROJECT_NAME;PROJECT_DESCRIPTION;PROJECT_VERSION;PACKAGE_NAME;PACKAGE_MAINTAINER")

MACRO (Add_Lib)
	parse_arguments(PRE_BUILD
		"${PRE_BUILD_VARIABLES}"
		""
		${ARGN}
	)
	
	Pre_Build()
	ADD_LIBRARY( ${PROJECT_NAME} ${LIBRARY_TYPE} ${${PROJECT_NAME}_SOURCE_FILES})
	Post_Build()	
	Write_Config("lib")
	
	CompileAndRunTests("lib")
	
	INSTALL_HEADERS_WITH_DIRECTORY( ${INCLUDE_DIR}/${PRE_BUILD_PROJECT_NAME} "src/|include/" ${PROJECT_NAME}_HEADER_FILES )
	IF(${BUILD_SHARED})
	    stripBinary(${PROJECT_NAME} "${STRIP_TOOL}" ${CMAKE_BINARY_DIR}/lib${LIB_PREFIX}${PROJECT_NAME}.so)
	ENDIF()

	#Set a suffix in name if build_type are debug (only for WIN32)
	IF(COMMAND SET_OUTPUT_NAME)
		SET_OUTPUT_NAME(OUTPUTNAME ${PROJECT_NAME})
	else()
		SET(OUTPUTNAME ${LIB_PREFIX}${PROJECT_NAME})
	ENDIF(COMMAND SET_OUTPUT_NAME)
	
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUTNAME})
	
	installProject(${PROJECT_NAME} ${LIB_DESTINATION})	
	
	INSTALL_COLLECTED( PBI_DIRS DIRECTORY )
	INSTALL_COLLECTED( PBI_FILES FILES )
ENDMACRO (Add_Lib)

MACRO (Add_Bin)
	set(PRE_BUILD_BIN_PARAMS "${PRE_BUILD_VARIABLES};SUBSYSTEM;BIN_DESTINATION;ICON_NAME;LICENSE_FILE")

	parse_arguments(PRE_BUILD
		"${PRE_BUILD_BIN_PARAMS}"
		""
		${ARGN}
	)
	
	Pre_Build()
	
	ADD_TOOL_DEPS(${PROJECT_NAME_UPPERCASE}_BUILD_LIBRARIES)

	add_system_executable(${PROJECT_NAME} ${PROJECT_NAME}_SOURCE_FILES)
	Post_Build()
	Write_Config("bin")	

	CompileAndRunTests("bin")
	
	#strip binary	
	stripBinary(${PROJECT_NAME} "${STRIP_TOOL}" ${PROJECT_NAME})

	# install binary
	installProject(${PROJECT_NAME} ${PRE_BUILD_BIN_DESTINATION})

	# install external dlls  
	#  macro que solo aplica en Platform_VS.cmake
	if(COMMAND install_external_dlls)
		install_external_dlls(${PRE_BUILD_BIN_DESTINATION})
	endif()
	
	# Generate the targets to build packages later
	SET(PACKAGE_DESCRIPTION ${PRE_BUILD_PROJECT_DESCRIPTION})
	SET(PACKAGE_VERSION     ${PRE_BUILD_PROJECT_VERSION})
	SET(PACKAGE_MAINTAINER  ${PRE_BUILD_PACKAGE_MAINTAINER})
	SET(PACKAGE_NAME        ${PRE_BUILD_PACKAGE_NAME})
	IF("${PACKAGE_MAINTAINER}" STREQUAL "")
		SET(PACKAGE_MAINTAINER  "ginga@lifia.info.unlp.edu.ar")
	ENDIF()
	IF("${PACKAGE_NAME}" STREQUAL "")
		# Use the project name if no package name is supplied
		SET(PACKAGE_NAME    ${PRE_BUILD_PROJECT_NAME})
	ENDIF()
	INCLUDE(CPackConfigBin)
	INCLUDE(CPack)
ENDMACRO (Add_Bin)

# #macro that adds the dependents include directories of the current project. 
# macro(ADD_DEPENDENTS_INCLUDE )
#   APPEND_ELEMENTS(${list_prefix}_INCLUDE_DIRECTORIES ${ARGN})
# endmacro(ADD_DEPENDENTS_INCLUDE )

# #macro that adds the dependents libraries of the current project. 
# macro(ADD_DEPENDENTS_LIB )
#   APPEND_ELEMENTS(${list_prefix}_LIBRARIES ${ARGN})
# endmacro(ADD_DEPENDENTS_LIB )

# #macro that adds the dependents static libraries of the current project. 
# macro(ADD_DEPENDENTS_LINK_LIB )
#   APPEND_ELEMENTS(${list_prefix}_LINK_LIBRARIES ${ARGN})
# endmacro(ADD_DEPENDENTS_LINK_LIB )

# #macro that adds the dependents link directories of the current project. 
# macro(ADD_DEPENDENTS_LINK_DIRS )
#   APPEND_ELEMENTS(${list_prefix}_LINK_DIRECTORIES ${ARGN})
# endmacro(ADD_DEPENDENTS_LINK_DIRS )

# #macro that adds the dependents link directories to the tests of the current project. 
# macro(ADD_DEPENDENTS_TEST_LINK_LIB)
#   APPEND_ELEMENTS(${list_prefix}_TEST_LINK_LIBRARIES ${ARGN})
# endmacro(ADD_DEPENDENTS_TEST_LINK_LIB)

# #macro that adds the dependents link directories to the tests of the current project. 
# macro(ADD_DEPENDENTS_TEST)
#   APPEND_ELEMENTS(TEST_EXTERNAL_LIBS ${ARGN})
# endmacro(ADD_DEPENDENTS_TEST)

macro(ADD_DEPENDENTS)
	SET(flag ${CURRENT_FLAG})
	if(DEFINED ${flag})
		set(tmpflag 1) # used to check if all dependents was founded in AUTO mode, if one not founded, none will appended. 
		foreach(dep ${ARGN})
			IF(NOT ${dep}_FOUND)
				if("${${flag}}" STREQUAL "AUTO")
					math(EXPR tmpflag "${tmpflag} & 0")
				ELSE()
					message(FATAL_ERROR "NOT FOUNDED PACKAGE: ${dep}")
				endif("${${flag}}" STREQUAL "AUTO")
			ELSE(NOT ${dep}_FOUND)
				math(EXPR tmpflag "${tmpflag} & 1")
			ENDIF(NOT ${dep}_FOUND)
		endforeach(dep ${ARGN})
		
		if(tmpflag)
			set(${flag} 1)
			ADD_DEPENDENTS_IMPL(${ARGN})
		else()
			#HERE THE FLAG IS AUTO.
			set(${flag} 0)
		endif(tmpflag)
	else()
		ADD_DEPENDENTS_IMPL(${ARGN})
	endif(DEFINED ${flag})
endmacro(ADD_DEPENDENTS)

MACRO(ADD_BOOST_COMPONENTS )
	ADD_BOOST_COMPONENTS_IMPL("" ${ARGN})
ENDMACRO(ADD_BOOST_COMPONENTS )

MACRO(ADD_BOOST_TEST_COMPONENTS )
	ADD_BOOST_COMPONENTS_IMPL("TEST_" ${ARGN})
ENDMACRO(ADD_BOOST_TEST_COMPONENTS )

# Add internal components. Return the list of the found libraries in "where".
# If the global variable "COLLECTING" is set, it just returns the list of requested components, without trying to find them
MACRO(ADD_INTERNAL_COMPONENTS)
	ADD_INTERNAL_COMPONENTS_IMPL("" ${ARGN})
ENDMACRO(ADD_INTERNAL_COMPONENTS)

MACRO(ADD_INTERNAL_TEST_COMPONENTS)
	ADD_INTERNAL_COMPONENTS_IMPL("TEST_" ${ARGN})
ENDMACRO(ADD_INTERNAL_TEST_COMPONENTS)

macro(CHECK_OPTION opt val)
	if(NOT (${${opt}} EQUAL ${val}))
		message(FATAL_ERROR "\n -- \t ERROR: ${opt} is not defined with ${val}.\n")
	endif(NOT (${${opt}} EQUAL ${val}))
endmacro(CHECK_OPTION opt val)

macro(SHOW_OPTIONS)
	FOREACH(group ${${PROJECT_NAME_UPPERCASE}_ALL_OPTIONS_NAMES})
	message( "" )
		message("\t ${group}: Change default value in SetupUser.cmake with \"set(${group}_USE_{OPT} [1|0])\" ")
		FOREACH(opt ${${group}_OPTIONS})
			message("\t \t${opt} ${${group}_USE_${opt}}")
		ENDFOREACH(opt)
	ENDFOREACH(group)
	message( "" )
endmacro(SHOW_OPTIONS)

macro(DEF_OPTIONS group)
	STRING(TOUPPER ${group} _GROUP)
	SET(${_GROUP}_OPTIONS "")
	#collecting args. Stop at "DEFAULT" value.
	#collecting arg_values. Iterate in ${ARGN} once. 
	set(args "")
	set(args_values "")

	set(collector_list args)
	foreach(opt ${ARGN})
		STRING(TOUPPER ${opt} arg)
		if(${arg} STREQUAL "DEFAULT")
			set(collector_list args_values)
		else()
			list(APPEND ${collector_list} ${arg})
		endif(${arg} STREQUAL "DEFAULT")
	endforeach(opt ${ARGN})

	PARSE_ARGUMENTS(${_GROUP} "${args}" "" ${args_values}) 

	#check values of args. 
	foreach(arg ${args})
		SetIfEmpty(${_GROUP}_${arg} OFF) #aca todas los ARGS van a tener definido un valor=(ON,AUTO,OFF).
		SetIfEmpty(${_GROUP}_USE_${arg} "${${_GROUP}_${arg}}" )

		if(${_GROUP}_USE_${arg})
			LIST(APPEND ${_GROUP} ${arg} )
			IF("${${_GROUP}_USE_${arg}}" STREQUAL "ON")
				set( ${_GROUP}_USE_${arg} 1)
				set( ${arg}_REQUIRED 1 )
			ELSE("${${_GROUP}_USE_${arg}}" STREQUAL "ON")
				set( ${arg}_REQUIRED 0 )
			ENDIF("${${_GROUP}_USE_${arg}}" STREQUAL "ON")
		else(${_GROUP}_USE_${arg})
			set( ${_GROUP}_USE_${arg} 0)
		endif(${_GROUP}_USE_${arg})
	endforeach(arg ${args})

	SET( ${_GROUP}_OPTIONS ${args})	

	IF (${_GROUP})
	  LIST(REMOVE_DUPLICATES ${_GROUP})
	  LIST(APPEND OPTIONS_NAMES ${_GROUP})
	ENDIF (${_GROUP})	
endmacro(DEF_OPTIONS group)
