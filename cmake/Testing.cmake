include(FetchContent)
FetchContent_Declare (
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)

FetchContent_MakeAvailable(Catch2)

include(CTest)
include(Catch)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# Comment out the next line to change the command line options
# See: https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md
# Also, run ctest --extra-verbose
set(CMAKE_CTEST_ARGUMENTS "--verbose; --output-on-failure")
