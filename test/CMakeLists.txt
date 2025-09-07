function(testsubmodule MODULE_NAME MODULE_LIBS)
	SET(TestMain "${MODULE_NAME}-test")

	FILE(GLOB_RECURSE LIB_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

	ADD_EXECUTABLE(${TestMain} ${LIB_TEST_FILES})
	SET_PROPERTY(TARGET ${TestMain} PROPERTY CXX_STANDARD ${TOKYO_CXX_STANDARD})
	SET_PROPERTY(TARGET ${TestMain} PROPERTY CXX_STANDARD_REQUIRED ON)

	TARGET_LINK_LIBRARIES(${TestMain} PRIVATE FakeIt::FakeIt-catch)

	foreach(liblib IN LISTS MODULE_LIBS)
		TARGET_LINK_LIBRARIES(${TestMain} PRIVATE ${liblib})
	endforeach()

	include(CTest)
	include("${PROJECT_SOURCE_DIR}/cmake/ParseAndAddCatchTests.cmake")
	#ParseAndAddCatchTests(${TestMain})
	catch_discover_tests(${TestMain})
endfunction()

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(game)
