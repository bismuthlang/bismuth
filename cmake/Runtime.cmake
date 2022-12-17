# Runtime module for linking
# The WPL runtime code will go in the ${RUNTIME_DIR}

set (RUNTIME_DIR ${CMAKE_SOURCE_DIR}/src/runtime)
#################################################
# I will supply the runtime library sources and
# the appropriate CMake files.
#################################################
set (RUNTIME_SOURCES
  ${RUNTIME_DIR}/wpl_runtime.c
)




###################################################
#
# PRISM Core Includes
#
###################################################

set (CORE_DIR ${RUNTIME_DIR}/core)
set (CORE_INCLUDE ${CORE_DIR}/include)

set (CORE_SOURCES 
  ${CORE_DIR}/IPCBuffer.cpp
)