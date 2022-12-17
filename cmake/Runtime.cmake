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