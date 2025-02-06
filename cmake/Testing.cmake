set(CPM_USE_LOCAL_PACKAGES ON)
message(STATUS "Catch2?: $ENV{Catch2_SOURCE_DIR}")
# CPMAddPackage("gh:catchorg/Catch2@3.7.1")
CPMAddPackage(
  NAME Catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 3.7.1
)
if(DEFINED ENV{Catch2_SOURCE_DIR})
  include("$ENV{Catch2_SOURCE_DIR}/extras/Catch.cmake")
  list(APPEND CMAKE_MODULE_PATH $ENV{catch2_SOURCE_DIR}/extras)
else()
  message(STATUS "Catch2?: ${Catch2_SOURCE_DIR}")
  include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")
  list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

include(CTest)
# include(Catch)


# Comment out the next line to change the command line options
# See: https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md
# Also, run ctest --extra-verbose
set(CMAKE_CTEST_ARGUMENTS "--verbose; --output-on-failure")

# FetchContent_MakeAvailable(HashMap)
# include(HashMap)
