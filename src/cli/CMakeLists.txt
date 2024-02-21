# CLI CMakeLists file 

include(CLI)


include (ANTLR)
include (Utility)
include(Semantic)
include(Symbol)
include(Codegen)
include(LLVM)
include(Runtime)

add_library(cli_lib OBJECT
    ${CLI_SOURCES}
)

include_directories(cli_lib
    ${CLI_INCLUDE}
    ${ANTLR_INCLUDE}
    ${ANTLR_GENERATED_DIR}
    ${SYMBOL_INCLUDE}
    ${SEMANTIC_INCLUDE}
    ${CODEGEN_INCLUDE}
    ${UTILITY_INCLUDE}
    ${LLVM_BINARY_DIR}/include
    ${LLVM_INCLUDE_DIR}
)