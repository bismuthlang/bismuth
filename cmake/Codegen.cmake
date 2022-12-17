# CMake file for the code generation.
include(LLVM)

set (CODEGEN_DIR ${CMAKE_SOURCE_DIR}/src/codegen)
set (CODEGEN_INCLUDE ${CODEGEN_DIR}/include)

###############################################
# Modify the next if you have different names.
#
set (CODEGEN_SOURCES
  ${CODEGEN_DIR}/CodegenVisitor.cpp
)