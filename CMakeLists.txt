CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(tokyo CXX)

SET(TOKYO_CXX_STANDARD 23)

SET(CMAKE_CXX_STANDARD ${TOKYO_CXX_STANDARD})
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
OPTION(CMAKE_COMPILE_WARNING_AS_ERROR "Compile warnings as errors" ON)
OPTION(TOKYO_STRICT "Enable strict compile options" ON)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

SET(CMAKE_DEBUG_POSTFIX "-d")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DTOKYO_DEBUG)
endif()

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
  CMAKE_POLICY(SET CMP0110 NEW)
endif()

ADD_SUBDIRECTORY(thirdparty)
ADD_SUBDIRECTORY(lib)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # We're in the root, define additional targets for developers.
    option(TOKYO_BUILD_APPS     "whether or not apps should be built" ON)
    option(TOKYO_BUILD_TESTS    "whether or not tests should be built" ON)

    if(TOKYO_BUILD_APPS)
        ADD_SUBDIRECTORY(app)
    endif()
    if(TOKYO_BUILD_TESTS)
        ENABLE_TESTING()
        ADD_SUBDIRECTORY(test)
    endif()
endif()
