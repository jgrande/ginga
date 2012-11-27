MACRO (CompileAndRunTests buildType)
	IF(COMPILE_TESTS)
		ADD_EXECUTABLE(${PROJECT_NAME}test ${${PROJECT_NAME}_TEST_SOURCE_FILES})
		# Link the executable to the libraries.
		IF(${buildType} STREQUAL "lib")
			ADD_LIB_DEPS(${PROJECT_NAME_UPPERCASE}_TEST_BUILD_LIBRARIES)
			
			TARGET_LINK_LIBRARIES(${PROJECT_NAME}test ${PROJECT_NAME} ${${PROJECT_NAME_UPPERCASE}_TEST_BUILD_LIBRARIES})
		ELSEIF(${buildType} STREQUAL "bin")
		
			# Compile the bin again as a static lib, to link the test binary against it.
			ADD_LIBRARY( ${PROJECT_NAME}_t STATIC ${${PROJECT_NAME}_SOURCE_FILES})
			TARGET_LINK_LIBRARIES( ${PROJECT_NAME}_t ${${PROJECT_NAME_UPPERCASE}_BUILD_LIBRARIES})
			
			TARGET_LINK_LIBRARIES( ${PROJECT_NAME}test ${PROJECT_NAME}_t ${${PROJECT_NAME_UPPERCASE}_BUILD_LIBRARIES} ${${PROJECT_NAME_UPPERCASE}_TEST_BUILD_LIBRARIES})
		ENDIF()
		IF(RUN_TESTS)
			ENABLE_TESTING()
			IF (EXISTS ${PROJECT_SOURCE_DIR}/test/test.sh)
				ADD_TEST(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test/test.sh ${CMAKE_BINARY_DIR}/${PROJECT_NAME}test ${PROJECT_SOURCE_DIR})
			ELSE (EXISTS ${PROJECT_SOURCE_DIR}/test/test.sh)
				ADD_TEST(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}test)
			ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/test/test.sh)
		ENDIF(RUN_TESTS)
	ENDIF(COMPILE_TESTS)
ENDMACRO (CompileAndRunTests)
