# symbol listfile
#
##############################################
# Modify for your implementation.
##############################################
include(Symbol)
include(Matchit)

add_library(sym_lib OBJECT
  ${SYMBOL_SOURCES}
  ${MATCHIT_SOURCES}
)
include_directories(sym_lib
  ${SYMBOL_INCLUDE}
  ${LLVM_BINARY_DIR}/include
  ${LLVM_INCLUDE_DIR}
  ${UTILITY_INCLUDE} # TODO: DOES THIS MEAN WE ARE INCLUDING ALL THE OTHER UTILS THAT ARE ONLY USEFUL FOR TESTING?
  ${ANTLR_INCLUDE} # Just for token in TypedAST & RawAST
  ${ANTLR_SOURCES}
  ${ANTLR_GENERATED_DIR}  # Just for RawAST
  ${MATCHIT_INCLUDE}
)
