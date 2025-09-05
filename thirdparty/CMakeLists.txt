INCLUDE(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.10.0)

FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
  FakeIt
  GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
  GIT_TAG        2.4.1)

FetchContent_MakeAvailable(FakeIt)

FetchContent_Declare(
  Sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG        v3.5.0)

FetchContent_MakeAvailable(Sol2)

FetchContent_Declare(
  Lua
  GIT_REPOSITORY https://gitlab.com/codelibre/lua/lua-cmake.git
  GIT_TAG        lua-cmake/v5.4.8.0)

FetchContent_MakeAvailable(Lua)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

# https://www.reddit.com/r/cmake/comments/13ljuzq/how_to_have_fetchcontent_declare_use_a_src_dir/