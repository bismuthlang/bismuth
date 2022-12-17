# utility listfile
#
# Use this if it fits your design.

include(Utility)

add_library(utility_lib OBJECT
  ${UTILITY_SOURCES}
)
include_directories(utility_lib
  ${UTILITY_INCLUDE}
  ${ANTLR_INCLUDE}
)