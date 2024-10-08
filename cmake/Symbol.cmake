###############################################
#
# Symbol CMake file
#
# This component handles functionality related 
# to the symbol table. 
#
###############################################
include(LLVM)
set (SYMBOL_DIR ${CMAKE_SOURCE_DIR}/src/symbol)
set (SYMBOL_INCLUDE 
  ${SYMBOL_DIR}
  ${SYMBOL_DIR}/include
  ${LLVM_INCLUDE_DIR}
)

set (SYMBOL_SOURCES
  ${SYMBOL_DIR}/Symbol.cpp
  ${SYMBOL_DIR}/FQN.cpp
  ${SYMBOL_DIR}/Scope.cpp
  ${SYMBOL_DIR}/STManager.cpp
  ${SYMBOL_DIR}/Type.cpp
  ${SYMBOL_DIR}/Protocol.cpp
  ${SYMBOL_DIR}/Context.cpp
  ${SYMBOL_DIR}/TypedAST.cpp
  ${SYMBOL_DIR}/SymbolUtils.cpp
)