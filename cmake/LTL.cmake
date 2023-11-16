# LTL Monitoring component module

set (LTL_DIR ${CMAKE_SOURCE_DIR}/src/ltl)
set (LTL_INCLUDE 
  ${LTL_DIR}/include
)
#################################################
# Set the names that you use.
#################################################
set (LTL_SOURCES
  ${LTL_DIR}/LTLMonitor.cpp
  ${LTL_DIR}/LTLMonitorDef.cpp
)