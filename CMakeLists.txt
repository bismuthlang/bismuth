# Top-level CMake file for Bismiuth

cmake_minimum_required(VERSION 3.20.0)
project(BISMUTH_COMPILER 
  LANGUAGES CXX C
  VERSION 0.1
  DESCRIPTION   "Bismuth Compiler"
)

option(BUILD_COVERAGE "Build coverage for test programs" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(NoInSourceBuilds)

if(BUILD_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
endif(BUILD_COVERAGE)

include(ProjectGlobals)         # Platform independent variables
include(platform_settings)      # Platform specific variables

add_subdirectory(src bin)

set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
# install(
#   TARGETS 
#     calculator
#   DESTINATION install
# )
# include(Install)

### Testing with CTEST
enable_testing()

add_subdirectory(test)


