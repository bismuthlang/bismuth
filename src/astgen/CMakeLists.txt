###########################################################
#
# AST Generator Phase Makefile 
# Alex Friedman 
# Copyright (c) 2023
#
###########################################################

include(ASTGen)
include(Symbol)
include(ANTLR)
include(Utility)
include(LLVM)

add_library(astgen_lib OBJECT
  ${ASTGEN_SOURCES}
)

add_dependencies(astgen_lib 
  lexparse_lib
  utility_lib
  )

include_directories(astgen_lib
  ${ANTLR_INCLUDE}
  ${ANTLR_GENERATED_DIR}
  ${SYMBOL_INCLUDE}
  ${ASTGEN_INCLUDE}
  ${UTILITY_INCLUDE}
  ${LLVM_BINARY_DIR}/include
  ${LLVM_INCLUDE_DIR}
)
