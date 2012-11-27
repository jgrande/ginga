#Save the name of the current project to prefix of the lists of dependents of this project.
macro(SET_CURRENT_PROJECT current_project)
  set(list_prefix ${current_project})
endmacro(SET_CURRENT_PROJECT current_project)

#Make the prebuild for each project of the lib/tool compilation.
MACRO (Pre_Build)
	PROJECT(${PRE_BUILD_PROJECT_NAME})
	
	STRING(TOUPPER ${PRE_BUILD_PROJECT_NAME} PROJECT_NAME_UPPERCASE )
	
	# To avoid problems when using the name in #define
	STRING(REPLACE "-" "_" PROJECT_NAME_UPPERCASE_ESCAPED ${PROJECT_NAME_UPPERCASE} ) 
	LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
	
	SET_CURRENT_PROJECT(${PROJECT_NAME_UPPERCASE})
	
	PROCESS_PROJECT( ${PROJECT_SOURCE_DIR} )
	LIST(APPEND ${PROJECT_NAME_UPPERCASE}_LIBRARIES ${${PLATFORM}_LIBRARIES})	
	LIST(APPEND ${PROJECT_NAME_UPPERCASE}_LIBRARIES ${${CMAKE_SYSTEM_NAME}_LIBRARIES})
	LIST(APPEND ${PROJECT_NAME_UPPERCASE}_OPTIONS_NAMES ${OPTIONS_NAMES} )
	LIST(APPEND ${PROJECT_NAME_UPPERCASE}_ALL_OPTIONS_NAMES ${OPTIONS_NAMES} )
	INCLUDE_DEPS(${PROJECT_NAME_UPPERCASE})	
	
	INCLUDE_SOURCES(${PROJECT_SOURCE_DIR})

	INCLUDE_INSTALL(${PROJECT_SOURCE_DIR})
	
	IF(COMPILE_TESTS)
		INCLUDE_TEST_SOURCES(${PROJECT_SOURCE_DIR})
	ENDIF()
	
	SET(VERSION ${PRE_BUILD_PROJECT_VERSION})
	
	# Cleanup todas las variables include, libsdirectory libraries
	set( ${PROJECT_NAME_UPPERCASE}_BUILD_LIBRARIES "" )
	set( ${PROJECT_NAME_UPPERCASE}_INCLUDE_DIRECTORIES "" )
	set( ${PROJECT_NAME_UPPERCASE}_LINK_DIRECTORIES "" )
	set( ${PROJECT_NAME_UPPERCASE}_DEFINITIONS "-DPROJECT_NAME=${PROJECT_NAME}" )

	IF(COMPILE_TESTS)
		set( ${PROJECT_NAME_UPPERCASE}_TEST_INCLUDE_DIRECTORIES "" )
		set( ${PROJECT_NAME_UPPERCASE}_TEST_LINK_DIRECTORIES "" )
	
		find_package(GTest REQUIRED)
		LIST(APPEND ${PROJECT_NAME_UPPERCASE}_TEST_COMPONENTS GTEST)
	ENDIF(COMPILE_TESTS)
	
	IF(BUILD_SHARED)
        	SET(LIBRARY_TYPE SHARED)
	ELSE(BUILD_SHARED)
	        SET(LIBRARY_TYPE STATIC)
	ENDIF(BUILD_SHARED)	
ENDMACRO (Pre_Build)

MACRO (Post_Build)
	add_dependents_list(${PROJECT_NAME_UPPERCASE})
	add_definitions(${${PROJECT_NAME_UPPERCASE}_DEFINITIONS})
	
	LIST( APPEND ${PROJECT_NAME_UPPERCASE}_INCLUDE_DIRECTORIES ${PROJECT_BINARY_DIR} )
	
	INCLUDE_DIRECTORIES( ${${PROJECT_NAME_UPPERCASE}_INCLUDE_DIRECTORIES} )
	get_directory_property( ${PROJECT_NAME_UPPERCASE}_INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES )
	
	link_directories( ${${PROJECT_NAME_UPPERCASE}_LINK_DIRECTORIES} )
	get_directory_property( ${PROJECT_NAME_UPPERCASE}_LINK_DIRECTORIES LINK_DIRECTORIES )
	
	TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${${PROJECT_NAME_UPPERCASE}_BUILD_LIBRARIES} )
 
	IF(COMPILE_TESTS)
	  add_dependents_list( ${PROJECT_NAME_UPPERCASE}_TEST )
	  add_definitions(${${PROJECT_NAME_UPPERCASE}_TEST_DEFINITIONS})
	  get_directory_property( ${PROJECT_NAME_UPPERCASE}_TEST_INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES )
	  get_directory_property( ${PROJECT_NAME_UPPERCASE}_TEST_LINK_DIRECTORIES LINK_DIRECTORIES )
	ENDIF(COMPILE_TESTS)
	
	SHOW_STATUS()
ENDMACRO (Post_Build)

#Strip binary to discards all symbols from the current compilation.
macro (stripBinary PROJECT_NAME STRIP_TOOL STRIP_PARAM)
	IF(${CMAKE_BUILD_TYPE} STREQUAL "Release" AND STRIP_TOOL)
		ADD_CUSTOM_COMMAND( TARGET ${PROJECT_NAME}
				    POST_BUILD
				    COMMAND  ${STRIP_TOOL} ${STRIP_PARAM})
	ENDIF()
endmacro(stripBinary)

#Install the project into its corresponding directory
MACRO(installProject PROJECT_NAME DESTINATION)
	INSTALL( TARGETS ${PROJECT_NAME} 
		 DESTINATION ${DESTINATION}
		 CONFIGURATIONS ${CMAKE_BUILD_TYPE}
		 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE 
			     GROUP_READ 	    GROUP_EXECUTE 
			     WORLD_READ 	    WORLD_EXECUTE )
ENDMACRO(installProject)

#Install optional files and directories from diferents opts
macro(POST_BUILD_INSTALL_DIRECTORY dest)
	LIST(APPEND PBI_DIRS "DIR" ${dest})
		
	LIST(APPEND PBI_DIRS ${ARGN})
	MARK_AS_ADVANCED(FORCE PBI_DIRS)
endmacro(POST_BUILD_INSTALL_DIRECTORY)

macro(POST_BUILD_INSTALL_FILES dest)
	LIST(APPEND PBI_FILES "DIR" ${dest})
	LIST(APPEND PBI_FILES ${ARGN})
	MARK_AS_ADVANCED(FORCE PBI_FILES)
endmacro(POST_BUILD_INSTALL_FILES)

macro(INSTALL_COLLECTED installVar installParam )
	FOREACH(h ${${installVar}})
		if(${h} STREQUAL "DIR")
			set(NEXT_IS_INSTALLDIR 1)
		else()
			if(${NEXT_IS_INSTALLDIR})
				set(INSTALL_DESTINATION ${h})
				set(NEXT_IS_INSTALLDIR 0)
			else()
				INSTALL( ${installParam} ${h} DESTINATION ${INSTALL_DESTINATION})
			endif(${NEXT_IS_INSTALLDIR})
		endif(${h} STREQUAL "DIR")
	ENDFOREACH(h ${${installVar}})
endmacro(INSTALL_COLLECTED installVar installParam)

#Set _include_dirs, _link_dirs, _build_libs, for the current project with the dependents data.
macro(add_dependents_list prefix)
	FOREACH(DEPENDENT ${${prefix}_COMPONENTS} )
		LIST( APPEND ${prefix}_INCLUDE_DIRECTORIES ${${DEPENDENT}_INCLUDE_DIRS} ${${DEPENDENT}_INCLUDE_DIR})
		LIST( APPEND ${prefix}_LINK_DIRECTORIES ${${DEPENDENT}_LIBRARY_DIRS} )
		EXTRACT_LIBS( ${prefix}_BUILD_LIBRARIES ${DEPENDENT} )
		LIST( APPEND ${prefix}_DEFINITIONS ${${DEPENDENT}_CFLAGS})
	ENDFOREACH(DEPENDENT )
	LIST( APPEND ${prefix}_BUILD_LIBRARIES ${${prefix}_LINK_LIBRARIES})
endmacro(add_dependents_list)

# Append elements to a list and show what was inserted into it.
# VISIBILITY; PRIVATE
macro(APPEND_ELEMENTS list)
  IF(NOT DEFINED ${COLLECTING})
    LIST(APPEND ${list} ${ARGN})
    if(${VERBOSITY} GREATER 0)
      message(STATUS "Appended [${${list}}] into ${list}")
    endif(${VERBOSITY} GREATER 0)
  ENDIF(NOT DEFINED ${COLLECTING})
endmacro(APPEND_ELEMENTS list)

#Show log of the compiled project.
macro(SHOW_STATUS)
	# display status message for important variables
	MESSAGE( STATUS )
	MESSAGE( STATUS "-------------------------------------------------------------------------------" )
	MESSAGE( STATUS "PROJECT_NAME = ${PROJECT_NAME}" )
	MESSAGE( STATUS "PROJECT_DESCRIPTION = ${PRE_BUILD_PROJECT_DESCRIPTION}" )
	MESSAGE( STATUS "PROJECT_VERSION = ${PRE_BUILD_PROJECT_VERSION}" )
	MESSAGE( STATUS "PLATFORM = ${PLATFORM}" )
	if(${VERBOSITY} GREATER 0)
		MESSAGE( STATUS "PLATFORM_FILE = ${CMAKE_TOOLCHAIN_FILE}" )
	endif(${VERBOSITY} GREATER 0)
	MESSAGE( STATUS "BUILD_SHARED = ${BUILD_SHARED}" )
	MESSAGE( STATUS "BUILD_TYPE = ${CMAKE_BUILD_TYPE}" )
	MESSAGE( STATUS "DEPENDENCIES = ${${PROJECT_NAME_UPPERCASE}_COMPONENTS}")
	MESSAGE( STATUS "OPTIONS = ${${PROJECT_NAME_UPPERCASE}_OPTIONS_NAMES}")
	MESSAGE( STATUS "INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}" )
	if(${VERBOSITY} GREATER 0)	
		MESSAGE( STATUS "${PROJECT_NAME_UPPERCASE}_DEFINITIONS = ${${PROJECT_NAME_UPPERCASE}_DEFINITIONS}" )
		MESSAGE( STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )
		MESSAGE( STATUS "CMAKE_FIND_ROOT_PATH = ${CMAKE_FIND_ROOT_PATH}" )
	endif(${VERBOSITY} GREATER 0)
	MESSAGE( STATUS "-------------------------------------------------------------------------------" )
	IF(NOT SILENT OR ${VERBOSITY} GREATER 0)
		MESSAGE( STATUS "HEADER FILES = ${${PROJECT_NAME}_HEADER_FILES}" )
		MESSAGE( STATUS "SOURCE FILES = ${${PROJECT_NAME}_SOURCE_FILES}" )
		IF(COMPILE_TESTS)
			MESSAGE( STATUS "TEST DEPENDENCIES = ${${PROJECT_NAME_UPPERCASE}_TEST_COMPONENTS}")
			MESSAGE( STATUS "TEST HEADER FILES = ${${PROJECT_NAME}_TEST_HEADER_FILES}" )
			MESSAGE( STATUS "TEST SOURCE FILES = ${${PROJECT_NAME}_TEST_SOURCE_FILES}" )
		ENDIF(COMPILE_TESTS)
		MESSAGE( STATUS "-------------------------------------------------------------------------------" )     
	  MESSAGE( STATUS "${PROJECT_NAME_UPPERCASE}_INCLUDE_DIRECTORIES = ${${PROJECT_NAME_UPPERCASE}_INCLUDE_DIRECTORIES}" )
	  MESSAGE( STATUS "${PROJECT_NAME_UPPERCASE}_LINK_DIRECTORIES = ${${PROJECT_NAME_UPPERCASE}_LINK_DIRECTORIES}" )
	  MESSAGE( STATUS "${PROJECT_NAME_UPPERCASE}_LINK_LIBRARIES = ${${PROJECT_NAME_UPPERCASE}_BUILD_LIBRARIES}")
	MESSAGE( STATUS "-------------------------------------------------------------------------------" )
	IF(COMPILE_TESTS)
		MESSAGE( STATUS "${PROJECT_NAME_UPPERCASE}_TEST_INCLUDE_DIRECTORIES = ${${PROJECT_NAME_UPPERCASE}_TEST_INCLUDE_DIRECTORIES}" )
		MESSAGE( STATUS "${PROJECT_NAME_UPPERCASE}_TEST_LINK_DIRECTORIES = ${${PROJECT_NAME_UPPERCASE}_TEST_LINK_DIRECTORIES}" )
		MESSAGE( STATUS "${PROJECT_NAME_UPPERCASE}_TEST_LINK_LIBRARIES = ${${PROJECT_NAME_UPPERCASE}_TEST_BUILD_LIBRARIES}")
	ENDIF(COMPILE_TESTS)
	MESSAGE( STATUS "-------------------------------------------------------------------------------" )
	ENDIF(NOT SILENT OR ${VERBOSITY} GREATER 0)	
endmacro(SHOW_STATUS)

#Save all configs from the current lib/tool compilation into a config.h for the compiled project.
MACRO (Write_Config buildType)
	FOREACH(group ${${PROJECT_NAME_UPPERCASE}_ALL_OPTIONS_NAMES})
		LIST(APPEND BUILD_OPTS "${group}=${${group}}")
	ENDFOREACH(group)

	SET ( OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CMakeFiles/CMakeTmp/${PROJECT_NAME}_config.h.cin" )
	if(EXISTS ${PROJECT_SOURCE_DIR}/config.h.cin)
		FILE(READ ${PROJECT_SOURCE_DIR}/config.h.cin CONFIG_PROJECT )
		FILE( WRITE ${OUTPUT_CONFIG_FILE} "${CONFIG_PROJECT}" )
	endif(EXISTS ${PROJECT_SOURCE_DIR}/config.h.cin)
	
	# Define macros foreach values are appended into tmp config of current project.
	if(${buildType} STREQUAL "bin")
		WRITE_TOOL_VARS("${OUTPUT_CONFIG_FILE}")
	endif(${buildType} STREQUAL "bin")

	WRITE_OPTIONS_USED("${OUTPUT_CONFIG_FILE}")
	
	CONFIGURE_FILE(${OUTPUT_CONFIG_FILE}
	${PROJECT_BINARY_DIR}/generated/config.h
	)
ENDMACRO (Write_Config)

macro(WRITE_TOOL_VARS OUTPUT_CONFIG_FILE)
	FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n#define ${PROJECT_NAME_UPPERCASE_ESCAPED}_NAME " "\"${PROJECT_NAME}\"")
	FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n#define ${PROJECT_NAME_UPPERCASE_ESCAPED}_DESCRIPTION " "\"${PRE_BUILD_PROJECT_DESCRIPTION}\"")
	FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n#define ${PROJECT_NAME_UPPERCASE_ESCAPED}_TAG_VERSION " "\"${TAG_VERSION}\"")
	FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n#define ${PROJECT_NAME_UPPERCASE_ESCAPED}_BUILD_OPTS " "\"TYPE=${CMAKE_BUILD_TYPE};SHARED=${BUILD_SHARED};${BUILD_OPTS}\"")
	FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n#define ${PROJECT_NAME_UPPERCASE_ESCAPED}_BUILD_VERSION " "\"${BUILD_VERSION}\"")
endmacro(WRITE_TOOL_VARS OUTPUT_CONFIG_FILE)

macro(WRITE_OPTIONS_USED OUTPUT_CONFIG_FILE)
  FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n\n// Autogenerated OPTIONS")
  FOREACH(group ${${PROJECT_NAME_UPPERCASE}_OPTIONS_NAMES})
	FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n// ${group} OPTIONS")
	#define all groups options with their values
	FOREACH(opt ${${group}_OPTIONS})
	  FILE(APPEND ${OUTPUT_CONFIG_FILE}"\n#define ${group}_USE_${opt} ${${group}_USE_${opt}}")
	  ENDFOREACH(opt ${${group}_OPTIONS})
	  FILE(APPEND ${OUTPUT_CONFIG_FILE} "\n")
	ENDFOREACH(group ${${PROJECT_NAME_UPPERCASE}_OPTIONS_NAMES})
endmacro(WRITE_OPTIONS_USED OUTPUT_CONFIG_FILE)

# Sets the variable used by the deps.cmake files
MACRO(SET_LIB_VARS)
	SET(     INTERNAL_LIBS "")
	SET(     EXTERNAL_LIBS "")
	SET(         LINK_LIBS "")
	SET(TEST_INTERNAL_LIBS "")
	SET(TEST_EXTERNAL_LIBS "")
	SET(    TEST_LINK_LIBS "")
	SET(    INTERNAL_NAMES "")
	SET(     OPTIONS_NAMES "")
ENDMACRO(SET_LIB_VARS)

# Collect the dependencies of the library
MACRO(INCLUDE_DEPS lib_name)
	STRING(TOUPPER ${lib_name} output_base)
	
	CLEANUP_COMPONENTS( ${output_base}_COMPONENTS "" INTERNAL_LIBS EXTERNAL_LIBS )	
	LIST(APPEND ${output_base}_LINK_LIBRARIES 	${LINK_LIBS})
	
	CLEANUP_COMPONENTS( ${output_base}_TEST_COMPONENTS "TEST_" TEST_INTERNAL_LIBS TEST_EXTERNAL_LIBS )	
	LIST(APPEND ${output_base}_TEST_LINK_LIBRARIES 	${TEST_LINK_LIBS})
ENDMACRO(INCLUDE_DEPS)

MACRO( CLEANUP_COMPONENTS outputvar prefix int_comps ext_comps )
	if(${int_comps})
		LIST(REMOVE_DUPLICATES ${int_comps})
	endif(${int_comps})
	if(${ext_comps})
		LIST(REMOVE_DUPLICATES ${ext_comps})
	endif(${ext_comps})	
	LIST(APPEND ${outputvar} ${${int_comps}} ${${ext_comps}})		

	LIST(REMOVE_DUPLICATES ${prefix}LINK_LIBS)
ENDMACRO (CLEANUP_COMPONENTS)

MACRO( PROCESS_PROJECT project_dir )
	SET_LIB_VARS()
	INCLUDE_IF_EXIST(${project_dir}/platform_${PLATFORM}.cmake)
	INCLUDE_IF_EXIST(${project_dir}/os_${CMAKE_SYSTEM_NAME}.cmake)
	INCLUDE_PROJECT_COMPONENTS( ${project_dir} "deps")
ENDMACRO( PROCESS_PROJECT )

#include components (deps/sources) and optional files of the current project compilation.
MACRO(INCLUDE_PROJECT_COMPONENTS path includePrefix)
	INCLUDE_IF_EXIST(${path}/${includePrefix}.cmake)
	INCLUDE_IF_EXIST(${path}/${includePrefix}_${PLATFORM}.cmake)
	INCLUDE_IF_EXIST(${path}/${includePrefix}_${CMAKE_SYSTEM_NAME}.cmake)
	
	if(NOT OPTIONS_ONLY)
		# Process options
		FOREACH(group ${OPTIONS_NAMES})
			FOREACH(opt ${${group}_OPTIONS})
				IF(${group}_USE_${opt})
					STRING(TOUPPER ${opt} OPT_UPPER)
					SET(CURRENT_FLAG ${group}_USE_${opt})
					INCLUDE_IF_EXIST(${path}/${includePrefix}.${group}_${OPT_UPPER}.cmake)
					UNSET(CURRENT_FLAG)
				ENDIF()
			ENDFOREACH(opt)
		ENDFOREACH(group)
	endif(NOT OPTIONS_ONLY)
ENDMACRO(INCLUDE_PROJECT_COMPONENTS path includePrefix)

#Include the sources of the current project compilation.
MACRO(INCLUDE_SOURCES SOURCE_DIR)
    INCLUDE_PROJECT_COMPONENTS(${SOURCE_DIR} "sources")
	define_source_groups(${${PROJECT_NAME}_SOURCE_FILES})
ENDMACRO(INCLUDE_SOURCES)

#Include the install of the current project compilation.
MACRO(INCLUDE_INSTALL SOURCE_DIR)
	SetIfEmpty(PBI_DIRS "")
	SetIfEmpty(PBI_FILES "")
	INCLUDE_PROJECT_COMPONENTS(${SOURCE_DIR} "install")
ENDMACRO(INCLUDE_INSTALL)

#Include the tests of the current project compilation.
MACRO(INCLUDE_TEST_SOURCES SOURCE_DIR)
	IF(EXISTS ${SOURCE_DIR}/sources.test.cmake)
		INCLUDE_PROJECT_COMPONENTS(${SOURCE_DIR} "sources.test")
		define_source_groups(${${PROJECT_NAME}_TEST_SOURCE_FILES})
	ELSE()
		SET(COMPILE_TESTS 0)
	ENDIF()
ENDMACRO(INCLUDE_TEST_SOURCES)

# Gather the dependencies of a lib.
MACRO(ADD_LIB_DEPS outputvar)
	SET(which "all")
	IF(${ARGC} GREATER 1)
		STRING(TOLOWER ${ARGV1} which)
	ENDIF()
	_add_deps("lib" ${PROJECT_NAME} ${outputvar} ${which})
ENDMACRO(ADD_LIB_DEPS)

# Gather the dependencies of a tool.
MACRO(ADD_TOOL_DEPS outputvar)
	SET(which "all")
	IF(${ARGC} GREATER 1)
		STRING(TOLOWER ${ARGV1} which)
	ENDIF()
	_add_deps("tool" ${PROJECT_NAME} ${outputvar} ${which})
ENDMACRO(ADD_TOOL_DEPS)

macro(_add_deps _type project outputvar which)
	_get_parts(${_type} ${project} ${project}_libnames )
	
	LIST(REVERSE ${project}_libnames)
	set(${project}_INT_LIBS ${INTERNAL_LIBS})
	set(${project}_EXT_LIBS ${EXTERNAL_LIBS})
	
	IF(NOT ${BUILD_SHARED})
		process_parts_iteratively(${project}_libnames ${project}_INT_LIBS ${project}_EXT_LIBS)
	ENDIF(NOT ${BUILD_SHARED})

	EXTRACT_BIN_LIBRARIES("" ${outputvar} ${project}_INT_LIBS ${project}_EXT_LIBS)
endmacro(_add_deps)

macro(process_parts_iteratively libnames int_libs ext_libs)
	LIST(LENGTH ${libnames} total)
	SET( FINAL ${${libnames}} )

	set(processed "")
	while(${total} GREATER 0)
		LIST(GET ${libnames} 0 lib)
		_get_parts("lib" ${lib} tmp_libnames)
		LIST(REVERSE tmp_libnames)
		
		LIST(LENGTH tmp_libnames tmp_total)
		if(${tmp_total} GREATER 0)
			MATH(EXPR tmp_total "${tmp_total}-1")
			set(index 0)
			
			foreach(index RANGE ${tmp_total})
				LIST(GET tmp_libnames ${index} lib_deps)
				LIST(FIND ${libnames} ${lib_deps} pos)
				if(${pos} GREATER -1)
					LIST(REMOVE_ITEM ${libnames} ${lib_deps})
					LIST(REMOVE_ITEM FINAL ${lib_deps})
					LIST(GET INTERNAL_LIBS ${index} internal_lib)
					LIST(REMOVE_ITEM ${int_libs} ${internal_lib})
				else()
					MATH(EXPR total "${total}+1")
				endif(${pos} GREATER -1)
				
				LIST(APPEND ${libnames} ${lib_deps})
				LIST(APPEND FINAL ${lib_deps})
				
				LIST(GET INTERNAL_LIBS ${index} iLib)
				LIST(APPEND ${int_libs} ${iLib})
				
				LIST(FIND processed ${lib_deps} pos_in_processed)
				if(${pos_in_processed} GREATER -1)
					LIST(REVERSE ${int_libs})
					LIST(REMOVE_DUPLICATES ${int_libs})
					LIST(REVERSE ${int_libs})
					
					LIST(REVERSE FINAL)
					LIST(REMOVE_DUPLICATES FINAL)
					LIST(REVERSE FINAL)
				endif(${pos_in_processed} GREATER -1)
			endforeach(index RANGE tmp_total)
		endif(${tmp_total} GREATER 0)
		
		LIST(APPEND ${ext_libs} ${EXTERNAL_LIBS})
		
		MATH(EXPR total "${total}-1")
		LIST(APPEND processed ${lib})
		LIST(REMOVE_AT ${libnames} 0)
	endwhile()
	unset(processed)
	unset(total)
	set(${libnames} ${FINAL})
endmacro(process_parts_iteratively libnames int_libs ext_comps)

macro(EXTRACT_BIN_LIBRARIES prefix outputvar int_comps ext_comps)
	SET(comps "")
	CLEANUP_COMPONENTS( comps "${prefix}" ${int_comps} ${ext_comps} )
	
	FOREACH(DEPENDENT ${comps})
		EXTRACT_LIBS( ${outputvar} ${DEPENDENT} )
	ENDFOREACH(DEPENDENT)
	LIST(APPEND ${outputvar} ${${prefix}LINK_LIBS} )
endmacro(EXTRACT_BIN_LIBRARIES prefix outputvar int_comps ext_comps)

# Get the library file referenced by each member of the list
MACRO(EXTRACT_LIBS outputvar component)
	set(tmp_list_DEBUG "")
	Set(tmp_list_RELEASE "")
	Set(tmp_list_GENERAL "")
	
	SET(_list_suffix _GENERAL)
	FOREACH(lib ${${component}_LIBRARIES})
		IF("${lib}" STREQUAL "optimized")
				SET(_list_suffix _RELEASE)
		ELSE("${lib}" STREQUAL "optimized")
			IF("${lib}" STREQUAL "debug")
				SET(_list_suffix _DEBUG)
			ELSE("${lib}" STREQUAL "debug")
				IF("${lib}" STREQUAL "general")
					SET(_list_suffix _GENERAL)
				ELSE("${lib}" STREQUAL "general")
					LIST(APPEND tmp_list${_list_suffix} ${lib})
				ENDIF("${lib}" STREQUAL "general")
			ENDIF("${lib}" STREQUAL "debug")
		ENDIF("${lib}" STREQUAL "optimized")
	ENDFOREACH(lib ${${component}_LIBRARIES}})
	
	LIST(APPEND ${outputvar} ${tmp_list_GENERAL} )	
	if(${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel" )
		LIST(APPEND ${outputvar} ${tmp_list_GENERAL} ${tmp_list_RELEASE} )
	else()
		LIST(APPEND ${outputvar} ${tmp_list_GENERAL} ${tmp_list_DEBUG} )	
	endif(${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel" )
	LIST( REMOVE_DUPLICATES ${outputvar} )
ENDMACRO(EXTRACT_LIBS outputvar component)

#Set the internal deps of the project_name into libnames
MACRO(_get_parts _type project_name libnames)
	IF(${VERBOSITY} GREATER 0)
		message("")
		message("Scanning dependencies of ${project_name}")
		message(STATUS "-------------------------------------------------------------------------------" )
	ENDIF(${VERBOSITY} GREATER 0)

	IF(${_type} STREQUAL "lib")
	  IF (EXISTS "${DEPOT}/lib/${LIB_PREFIX}-${project_name}")
	    set( project_dir "${DEPOT}/lib/${LIB_PREFIX}-${project_name}" )
	  else()
	    set( project_dir "${DEPOT}/lib/${project_name}" )
	  ENDIF (EXISTS "${DEPOT}/lib/${LIB_PREFIX}-${project_name}")
	ELSE()
		set( project_dir "${DEPOT}/tool/${project_name}" )
	ENDIF()
	
	PROCESS_PROJECT( ${project_dir} )
	LIST(APPEND ${PROJECT_NAME_UPPERCASE}_ALL_OPTIONS_NAMES ${OPTIONS_NAMES} )
	IF (${PROJECT_NAME_UPPERCASE}_ALL_OPTIONS_NAMES)
		LIST(REMOVE_DUPLICATES ${PROJECT_NAME_UPPERCASE}_ALL_OPTIONS_NAMES)
	ENDIF (${PROJECT_NAME_UPPERCASE}_ALL_OPTIONS_NAMES)	

	SET(${libnames} "")
	FOREACH(libname ${INTERNAL_NAMES})
		IF (EXISTS "${DEPOT}/lib/${LIB_PREFIX}-${libname}")
			LIST(APPEND ${libnames} "${LIB_PREFIX}-${libname}")
		ELSE()
			LIST(APPEND ${libnames} "${libname}")
		ENDIF()
	ENDFOREACH(libname)

	LIST(REVERSE ${libnames})

	IF(COLLECTING)
		SET(INTERNAL_LIBS ${${libnames}})
	ENDIF(COLLECTING)
ENDMACRO(_get_parts)

#Check if all dependencies of any TOOL are satisfied.
MACRO(CHECK_PROJECT_DEPS type project output)
	set(COLLECTING 1)
	_get_parts("${type}" ${project} ${output})
	set(project_libs ${${output}})
	if(project_libs)
		LIST(REVERSE project_libs)
		set(project_ilibs ${project_libs})
		process_parts_iteratively(project_libs project_ilibs EXTERNAL_LIBS)
		LIST(REVERSE project_libs)
	endif(project_libs)
	set(${output} ${project_libs})
	unset(COLLECTING)
ENDMACRO(CHECK_PROJECT_DEPS)

#check if boost was included into dependents list.
MACRO(IS_BOOST_INCLUDED _found libs)
	SET(${_found} 0)
	FOREACH(x ${${libs}})
		IF("${x}" STREQUAL "Boost")
			SET(${_found} 1)
		ENDIF()
	ENDFOREACH()
ENDMACRO(IS_BOOST_INCLUDED)

# Add packages from the Boost libraries, returning their names in "where"
# This macro is used to avoid calling find_package for packages that are already added
MACRO(ADD_BOOST_COMPONENTS_IMPL prefix )
	SET(components "")
	SET(components_length 0)

	FOREACH(component ${ARGN})
		STRING(TOUPPER ${component} COMP)
		STRING(COMPARE EQUAL "${Boost_${COMP}_LIBRARIES}" "" not_added)
		IF (not_added)
			LIST(APPEND components ${component})
			MATH(EXPR components_length "${components_length}+1")
		ENDIF()
	ENDFOREACH()

	IF(components_length)
	  find_package( Boost 1.46.0 REQUIRED ${components})
	  IF(NOT DEFINED ${COLLECTING})
		LIST(APPEND ${prefix}EXTERNAL_LIBS Boost)
	  ENDIF(NOT DEFINED ${COLLECTING})
	ENDIF()
	UNSET(components)
ENDMACRO(ADD_BOOST_COMPONENTS_IMPL)

MACRO(ADD_INTERNAL_COMPONENTS_IMPL prefix)
	IF(${COLLECTING})
		LIST(APPEND ${prefix}INTERNAL_NAMES ${ARGN})
	ELSE()
		find_package( GingaLib 0.11.0 REQUIRED ${ARGN} )
		LIST(APPEND ${prefix}INTERNAL_LIBS ${GINGALIB_FOUND_NAMES})
		LIST(APPEND ${prefix}INTERNAL_NAMES ${GINGALIB_NAMES_COMPONENTS})
	ENDIF()
ENDMACRO(ADD_INTERNAL_COMPONENTS_IMPL)

#macro that adds the dependents packages of the current project. 
macro(ADD_DEPENDENTS_IMPL)
	APPEND_ELEMENTS(EXTERNAL_LIBS ${ARGN})
endmacro(ADD_DEPENDENTS_IMPL)

macro(define_source_groups )
	set(CURRENT_GROUP "")
	set(CURRENT_GROUP_FILES "")
	foreach(file ${ARGN})
		#Get, by regex, the substring between the first "/" and the last "/" to define a source group
		#Ex: src/impl/.../aFile.h, with regex, obtains "/impl/.../" 
		STRING(REGEX MATCH "[/\\](.*)[/\\]" SOURCE_GROUP_NAME ${file})
		string(LENGTH "${SOURCE_GROUP_NAME}" length )
		
		if(${length} GREATER 0)
			#If SOURCE_GROUP_NAME is a valid string, that needs remove the first "/" and the last "/" to define a valid source group. 
			#Ex: regex obtains "/impl/.../", now remove the first "/" and the last "/" => "impl/..."
			MATH(EXPR length "${length}-2" )
			string(SUBSTRING ${SOURCE_GROUP_NAME} 1 ${length} SOURCE_GROUP_NAME)
			IF ( WIN32 )
				STRING( REGEX REPLACE "/" "\\\\" SOURCE_GROUP_NAME ${SOURCE_GROUP_NAME} )
			ENDIF ( WIN32 )
		endif(${length} GREATER 0)
		
		if("${SOURCE_GROUP_NAME}" EQUAL "${CURRENT_GROUP}")
			LIST(APPEND CURRENT_GROUP_FILES ${file})
		else("${SOURCE_GROUP_NAME}" EQUAL "${CURRENT_GROUP}")
			source_group("${CURRENT_GROUP}" FILES ${CURRENT_GROUP_FILES})
			set(CURRENT_GROUP ${SOURCE_GROUP_NAME})
			set(CURRENT_GROUP_FILES "")
			LIST(APPEND CURRENT_GROUP_FILES ${file})
		endif("${SOURCE_GROUP_NAME}" EQUAL "${CURRENT_GROUP}")
	endforeach(file ${PROJECT_NAME}_SOURCE_FILES)
endmacro(define_source_groups )
