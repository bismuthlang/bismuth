# symbol listfile
#
##############################################
# Modify for your implementation.
##############################################
include(Symbol)

add_library(sym_lib OBJECT
  ${SYMBOL_SOURCES}
)
include_directories(sym_lib
  ${SYMBOL_INCLUDE}
  ${LLVM_INCLUDE_DIR}
  ${UTILITY_INCLUDE} # TODO: DOES THIS MEAN WE ARE INCLUDING ALL THE OTHER UTILS THAT ARE ONLY USEFUL FOR TESTING?
  ${ANTLR_INCLUDE} # Just for token in TypedAST & RawAST
  ${ANTLR_GENERATED_DIR}  # Just for RawAST
)
