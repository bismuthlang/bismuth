# Test CMakeLists.txt file
#
include(CPM)
include(Testing)
include(ANTLR)
include(Symbol)
include(Semantic)
include(Utility)
include(Codegen)
include(LLVM)
include(CLI)

find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include(AddLLVM)
include(HandleLLVMOptions)

include(cmake/SymbolTests.cmake)
include(cmake/SemanticTests.cmake)
include(cmake/CodegenTests.cmake)
include(cmake/CliTests.cmake)

### Set up all tests to be run
add_executable(
  tests
  ${LEXPARSE_TESTS}
  # ${SYMBOL_TESTS} # FIXME: ENABLE SYMBOL TESTS!
  ${SEMANTIC_TESTS}
  ${CODEGEN_TESTS}
  ${CLI_TESTS}
)

add_dependencies(tests 
  parser_lib 
  sym_lib 
  semantic_lib
  utility_lib
  codegen_lib
  cli_lib
)

llvm_map_components_to_libnames(LLVM_LIBS ${LLVM_TARGETS_TO_BUILD} support core irreader codegen mc mcparser option)

target_include_directories(tests PUBLIC 
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

target_link_libraries(tests 
  PRIVATE
  ${ANTLR_RUNTIME_LIB}
  parser_lib
  lexparse_lib
  sym_lib
  semantic_lib
  utility_lib
  codegen_lib
  cli_lib
  ${LLVM_LIBS}
  Catch2::Catch2WithMain
)

# Get the tests registered with CTest
catch_discover_tests(tests)


if(BUILD_COVERAGE)
  setup_target_for_coverage_lcov(NAME coverage 
                              EXECUTABLE tests
                              EXCLUDE "/home/shared/cov/_deps/*" "/home/shared/antlr/*" "/usr/*" "11/*")
endif(BUILD_COVERAGE)