# semantic listfile
#
include(Semantic)
include(Symbol)
include(ANTLR)
include(Utility)
include(LLVM)

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
  ${LLVM_BINARY_DIR}/include
  ${LLVM_INCLUDE_DIR}
)
