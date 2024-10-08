# src listfile

include (ANTLR)
include (Utility)
include(Semantic)
include(Symbol)
include(Codegen)
include(LLVM)
include(Runtime)
include(CLI)

####################################################################
# See: https://cmake.org/cmake/help/latest/command/find_package.html
####################################################################
find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
include(AddLLVM)
include(HandleLLVMOptions)

add_subdirectory(lexparse)
add_subdirectory(symbol)
add_subdirectory(semantic)
add_subdirectory(utility)
add_subdirectory(codegen)
add_subdirectory(runtime)
add_subdirectory(cli)



add_executable(bismuthc bismuthc.cpp)

llvm_map_components_to_libnames(LLVM_LIBS ${LLVM_TARGETS_TO_BUILD} support core irreader codegen mc mcparser option)

add_dependencies(bismuthc 
    parser_lib 
    sym_lib 
    semantic_lib
    utility_lib
    codegen_lib
    bismuth_runtime
)

target_include_directories(bismuthc PUBLIC 
    ${ANTLR_INCLUDE} 
    ${ANTLR_GENERATED_DIR}
    ${SYMBOL_INCLUDE}
    ${SEMANTIC_INCLUDE}
    ${UTILITY_INCLUDE}
    ${CODEGEN_INCLUDE}
    ${LLVM_BINARY_DIR}/include
    ${LLVM_INCLUDE_DIR}
    ${LLVM_TARGETS_TO_BUILD}
    ${CLI_INCLUDE}
)

target_link_libraries(bismuthc 
    PRIVATE
    ${ANTLR_RUNTIME_LIB}
    parser_lib
    lexparse_lib
    sym_lib
    semantic_lib
    utility_lib
    codegen_lib
    ${LLVM_LIBS}
)

# git commit hash macro from https://stackoverflow.com/questions/1435953/how-can-i-pass-git-sha1-to-compiler-as-definition-using-cmake
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
add_definitions("-DGIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"")
