# semantic listfile
#
include(Semantic)
include(Symbol)
include(ANTLR)
include(Utility)
include(FunctionalPlus)

add_library(semantic_lib OBJECT
  ${SEMANTIC_SOURCES}
)

add_dependencies(semantic_lib 
  lexparse_lib
  utility_lib
)

include_directories(semantic_lib
  ${ANTLR_INCLUDE}
  ${ANTLR_GENERATED_DIR}
  ${SYMBOL_INCLUDE}
  ${SEMANTIC_INCLUDE}
  ${UTILITY_INCLUDE}
)


target_link_libraries(semantic_lib
    PRIVATE
    FunctionalPlus::fplus
)