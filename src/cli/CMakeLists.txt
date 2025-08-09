# CLI CMakeLists file

include(CLI)


include (ANTLR)
include (Utility)
include(Semantic)
include(Symbol)
include(Codegen)
include(LLVM)
include(Runtime)
include(Matchit)
include(FunctionalPlus)

add_library(cli_lib OBJECT
    ${CLI_SOURCES}
    ${MATCHIT_SOURCES}
)

include_directories(cli_lib
    ${CLI_INCLUDE}
    ${ANTLR_INCLUDE}
    ${ANTLR_GENERATED_DIR}
    ${ANTLR_SOURCES}
    ${SYMBOL_INCLUDE}
    ${SEMANTIC_INCLUDE}
    ${CODEGEN_INCLUDE}
    ${UTILITY_INCLUDE}
    ${LLVM_BINARY_DIR}/include
    ${LLVM_INCLUDE_DIR}
    ${MATCHIT_INCLUDE}
)

target_link_libraries(cli_lib
    PRIVATE
    FunctionalPlus::fplus
)