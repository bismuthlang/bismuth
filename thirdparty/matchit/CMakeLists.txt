# Matchit listfile
# (Note: this is to make matchit integrate with Bismuth and is not part of the original matchit src)
# Use this if it fits your design.

include(Matchit)

add_library(matchit_lib OBJECT
  ${MATCHIT_SOURCES}
)
include_directories(matchit_lib
  ${MATCHIT_INCLUDE}
)