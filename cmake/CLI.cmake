#########################################################
#
# CLI CMake file
#
# These components are called by the compiler's entrypoint to 
# handle its functionality. 
#
#########################################################

set (CLI_DIR ${CMAKE_SOURCE_DIR}/src/cli)
set (CLI_INCLUDE 
    ${CLI_DIR}
    ${CLI_DIR}/include
)

set (CLI_SOURCES
  ${CLI_DIR}/Compile.cpp
)