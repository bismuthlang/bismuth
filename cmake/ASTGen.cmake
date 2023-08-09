###########################################################
#
# AST Generator Phase Makefile 
# Alex Friedman 
# Copyright (c) 2023
#
###########################################################

include(LLVM)

set (ASTGEN_DIR ${CMAKE_SOURCE_DIR}/src/astgen)
set (ASTGEN_INCLUDE 
  ${ASTGEN_DIR}/include
  ${LLVM_INCLUDE_DIR}
)

set (ASTGEN_SOURCES
  ${ASTGEN_DIR}/ASTGenVisitor.cpp
)