# Runtime module for linking
# The language's runtime code will go in the ${RUNTIME_DIR}

set (RUNTIME_DIR ${CMAKE_SOURCE_DIR}/src/runtime)
#################################################
# 
# Runtime Entry Points (and easily accessible fns)
# 
#################################################
set (RUNTIME_SOURCES
  ${RUNTIME_DIR}/bismuth_runtime.c
)




###################################################
#
# Bismuth Core Includes # FIXME: FIND A WAY TO PREVENT THSE FROM BEING ACCESSED BY USERS DIRECTLY!
#
###################################################

set (CORE_DIR ${RUNTIME_DIR}/core)
set (CORE_INCLUDE 
  ${CORE_DIR}/include
  /home/shared/bdwgc/libgc.a 
  /home/shared/bdwgc/libgccpp.a
)

set (CORE_SOURCES 
  ${CORE_DIR}/IPCBuffer.cpp
  ${CORE_DIR}/Messages.cpp
  ${CORE_DIR}/StateManager.cpp
  ${CORE_DIR}/CloneMapWrapper.cpp
)