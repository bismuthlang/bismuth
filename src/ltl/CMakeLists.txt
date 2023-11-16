# ltl listfile
#
include(Semantic)
include(Symbol)
include(ANTLR)
include(Utility)
include(LLVM)
include(LTL)

add_library(ltl_lib OBJECT
  ${LTL_SOURCES}
)

# add_dependencies(ltl_lib 
#   lexparse_lib
#   utility_lib
# )

include_directories(ltl_lib
  ${ANTLR_INCLUDE}
  ${ANTLR_GENERATED_DIR}
  ${SYMBOL_INCLUDE}
  ${SEMANTIC_INCLUDE}
  ${LTL_INCLUDE}
  ${UTILITY_INCLUDE}
  ${LLVM_BINARY_DIR}/include
  ${LLVM_INCLUDE_DIR}
)
