CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(build)
FILE(TO_CMAKE_PATH $ENV{DEPOT} DEPOT)
IF(DEFINED COMPILE_PROJECT)
	IF(NOT EXISTS "${DEPOT}/tool/${COMPILE_PROJECT}")
	  IF(NOT EXISTS "${DEPOT}/lib/${COMPILE_PROJECT}")
	    IF(NOT EXISTS "${DEPOT}/lib/dtv-${COMPILE_PROJECT}")
	      MESSAGE(FATAL_ERROR "El producto especificado (${COMPILE_PROJECT}) no existe")
	    ENDIF(NOT EXISTS "${DEPOT}/lib/dtv-${COMPILE_PROJECT}")
	  ENDIF(NOT EXISTS "${DEPOT}/lib/${COMPILE_PROJECT}")
	ENDIF(NOT EXISTS "${DEPOT}/tool/${COMPILE_PROJECT}")
ELSE()
	MESSAGE(FATAL_ERROR "Falta especificar qué producto se va a construir (-DTOOL=<tool>) o (-DLIB=<lib>)")
ENDIF()
INCLUDE(${DEPOT}/config/Tvd.cmake)

SetIfEmpty(PACK 0)

#sets correctly the verbosity param for each lib/tool compile. (build/CmakeLists.txt).
macro(PARSE_VERBOSITY verb param)
  if(${verb} EQUAL 1)
    set(${param} "-DVERBOSITY=1 --debug-output")
  elseif(${verb} EQUAL 2)
    set(${param} "-DVERBOSITY=2 --trace")
  elseif(verb EQUAL 3)
    set(${param} "-DVERBOSITY=3 -DCMAKE_VERBOSE_FILE=ON")
  else(${verb} EQUAL 1)
    set(${param} "-DVERBOSITY=0")
  endif(${verb} EQUAL 1)
endmacro(PARSE_VERBOSITY verb)

macro(GET_SOURCE_DIR type name SRCDIR)
	IF(EXISTS "${DEPOT}/${type}/${name}")
		SET(${SRCDIR} "${DEPOT}/${type}/${name}")
	ELSE(EXISTS "${DEPOT}/${type}/${name}")
		IF(EXISTS "${DEPOT}/${type}/dtv-${name}")
			SET(${SRCDIR} "${DEPOT}/${type}/dtv-${name}")
		ENDIF(EXISTS "${DEPOT}/${type}/dtv-${name}")
	ENDIF(EXISTS "${DEPOT}/${type}/${name}")
endmacro(GET_SOURCE_DIR type name SRCDIR)

# Add a custom target to configure, build and install the lib or tool.
# It also set the dependencies to build everything in the right order.
# If "pack" is true, it also calls cpack to generate a package of the module.
MACRO(BUILD_MODULE type name depends pack is_default)
	GET_SOURCE_DIR(${type} ${name} SRCDIR )
	SET(BUILDDIR "${CMAKE_BINARY_DIR}/${name}")

	# change to BUILDDIR before compiling and installing
	if(COMMAND setVarsBuildPlatform)
	    setVarsBuildPlatform(${BUILDDIR})
	ELSE()
		SET(BUILD_CMD   make -C "${BUILDDIR}" $ENV{MAKE_OPTS})
		SET(INSTALL_CMD make -C "${BUILDDIR}" install)
	ENDIF()

	SET(PACK_CMD "")
	IF(${pack})
		SET(PACK_CMD cmake -E chdir "${BUILDDIR}" cpack)
	ENDIF()

	if(${is_default})
		SET(_all ALL)
	endif()
	
	# obtain the debug param passed to this cmake.
	PARSE_VERBOSITY(${VERBOSITY} CMAKE_DEBUG_PARAM)

	ADD_CUSTOM_TARGET(${name} ${_all}
		        cmake -E make_directory ${BUILDDIR}
		COMMAND cmake -E chdir "${BUILDDIR}" cmake ${CMAKE_DEBUG_PARAM} "-DOPTIONS_ONLY=${OPTIONS_ONLY}" "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}" -DCMAKE_PROJECT_NAME=${name} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} ${SRCDIR}
		COMMAND ${BUILD_CMD}                           # build
		COMMAND cmake -E chdir "${BUILDDIR}" ctest -V  # run tests
		COMMAND ${INSTALL_CMD}                         # install
		COMMAND ${PACK_CMD}                            # and pack if requested
	)
	IF(NOT "${depends}" STREQUAL "" )
		ADD_DEPENDENCIES(${name} ${depends})
	ENDIF()
ENDMACRO(BUILD_MODULE)

# Make the target necesary to generate the project files for Eclipse or Kdevelop3
MACRO(GENERATE_PROJECT type name ide_name)
	IF(${UNIX})
		SET(src_path "${DEPOT}/${type}/${name}")
		SET(build_path "${CMAKE_BINARY_DIR}/${name}")
	
		IF("${ide_name}" STREQUAL "eclipse")
			GENERATE_ECLIPSE_PROJECT(${name} ${src_path} ${build_path})
		ELSEIF("${ide}" STREQUAL "kdevelop3")
			GENERATE_KDEVELOP_PROJECT(${src_path} ${build_path})
		ENDIF()
	ELSE()
		MESSAGE(FATAL_ERROR "La generación de proyectos por el momento está implementada sólo para Linux.")
	ENDIF()
ENDMACRO(GENERATE_PROJECT)

# Make the target used to generate the Eclipse project files.
MACRO(GENERATE_ECLIPSE_PROJECT name src_path build_path)
	ADD_CUSTOM_TARGET("${name}_project"
		        cmake -E chdir "${src_path}" cmake -G "Eclipse CDT4 - Unix Makefiles"
		COMMAND sed -i -e \"\\:<key>org.eclipse.cdt.make.core.build.arguments</key>:{N\;s|.*<value></value>|<key>org.eclipse.cdt.make.core.build.arguments</key>\\n<value>-C ${build_path}</value>|}\" -e \"\\:<key>org.eclipse.cdt.make.core.build.location</key>:{N\;s|.*<value>.*</value>|<key>org.eclipse.cdt.make.core.build.location</key>\\n<value>${build_path}</value>|}\" "${src_path}/.project"
		COMMAND cmake -E remove "${src_path}/CMakeCache.txt" "${src_path}/Makefile" "${src_path}/cmake_install.cmake"
		COMMAND cmake -E remove "${src_path}/CPackConfig.cmake" "${src_path}/CPackSourceConfig.cmake"
		COMMAND cmake -E remove_directory "${src_path}/CMakeFiles/"
		COMMAND cmake -E remove_directory "${src_path}/generated/"
	)
	ADD_DEPENDENCIES( ${name} ${name}_project)

ENDMACRO(GENERATE_ECLIPSE_PROJECT)

# Make the target used to generate the KDevelop3 project files.
MACRO(GENERATE_KDEVELOP_PROJECT name src_path build_path)
	ADD_CUSTOM_TARGET("${name}_project"
		        cmake -E chdir "${src_path}" cmake -G "KDevelop3"
		COMMAND sed -i -e \"s|<buildtool>make</buildtool>|<buildtool>make -C $build_path</buildtool>|" -e \"s|<builddir>.*</builddir>|<builddir>$build_path</builddir>|" "${src_path}/*.kdevelop"
		COMMAND cmake -E remove "${src_path}/CMakeCache.txt" "${src_path}/Makefile" "${src_path}/cmake_install.cmake"
		COMMAND cmake -E remove "${src_path}/CPackConfig.cmake" "${src_path}/CPackSourceConfig.cmake"
		COMMAND cmake -E remove_directory "${src_path}/CMakeFiles/"
		COMMAND cmake -E remove_directory "${src_path}/generated/"
	)
	ADD_DEPENDENCIES( ${name} ${name}_project)

ENDMACRO(GENERATE_KDEVELOP_PROJECT)

# Get all the internal libraries required to build this project
IF(IS_TOOL)
  CHECK_PROJECT_DEPS("tool" "${COMPILE_PROJECT}" libnames)
  if(NOT OPTIONS_ONLY)
	# Build the libraries...
	SET(previous "")
	FOREACH(lib ${libnames})
		BUILD_MODULE("lib" ${lib} "${previous}" 0 0) # 0 -> dont't pack, 0 -> this is not a default target
		SET(previous "${lib}")
	ENDFOREACH(lib)
	# ... and the tool
	BUILD_MODULE("tool" ${COMPILE_PROJECT} "${previous}" ${PACK} 1) # 1 -> this is the default target

	# And finally, generate the project files, if requested
	IF(NOT "${GENERATE_PROJECTS}" STREQUAL "")
		FOREACH(lib ${libnames})
			GENERATE_PROJECT("lib" ${lib} ${GENERATE_PROJECTS})
		ENDFOREACH(lib)
		GENERATE_PROJECT("tool" ${COMPILE_PROJECT} ${GENERATE_PROJECTS})
	ENDIF()
  ELSE()
	unset(GENERATE_PROJECTS)
	unset(PACK)
	unset(VERBOSITY)
	SHOW_OPTIONS()
  endif(NOT OPTIONS_ONLY)
ELSE()
  unset(GENERATE_PROJECTS)
  unset(PACK)
  CHECK_PROJECT_DEPS("lib" "${COMPILE_PROJECT}" libnames)
  if(NOT OPTIONS_ONLY)
	# Build the libraries...
	SET(previous "")
	FOREACH(lib ${libnames})
		BUILD_MODULE("lib" ${lib} "${previous}" 0 0) # 0 -> dont't pack, 0 -> this is not a default target
		SET(previous "${lib}")
	ENDFOREACH(lib)
	# ... and the tool
	BUILD_MODULE("lib" ${COMPILE_PROJECT} "${previous}" 0 1) # 1 -> this is the default target
  ELSE()
	SHOW_OPTIONS()
  endif(NOT OPTIONS_ONLY)
ENDIF(IS_TOOL)