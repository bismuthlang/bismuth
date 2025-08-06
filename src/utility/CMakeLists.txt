# utility listfile
#
# Use this if it fits your design.

include(Utility)
include(FunctionalPlus)

add_library(utility_lib OBJECT
  ${UTILITY_SOURCES}
)
include_directories(utility_lib
  ${UTILITY_INCLUDE}
  ${ANTLR_INCLUDE}
)

target_link_libraries(utility_lib
    PRIVATE
    FunctionalPlus::fplus
)