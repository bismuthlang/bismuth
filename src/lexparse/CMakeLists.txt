# lexparse listfile
#
# Create the lexer and parser sources and the lexparse_lib and parser_lib
# targets.
include(ANTLR)

add_custom_command(
  OUTPUT(
    ${CMAKE_CURRENT_SOURCE_DIR}/parser_sources.h
    # ${ANTLR_SOURCES} # Uncomment if the build fails, then put back
  )
  BYPRODUCTS ${ANTLR_SOURCES}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND /bin/sh  generate.sh WPL  # Change this if you have a different script
)

add_custom_target(generate_parser ALL
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser_sources.h
)

add_library(parser_lib OBJECT
  ${CMAKE_CURRENT_SOURCE_DIR}/parser_sources.h
  ${ANTLR_SOURCES}
)
target_include_directories(parser_lib PUBLIC ${ANTLR_INCLUDE})

add_library(lexparse_lib
  ${ANTLR_SOURCES}
)
add_dependencies(lexparse_lib parser_lib)
target_include_directories(lexparse_lib PUBLIC ${ANTLR_INCLUDE})