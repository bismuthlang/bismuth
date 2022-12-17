# Semantic analysis component module
include(LLVM)

set (SEMANTIC_DIR ${CMAKE_SOURCE_DIR}/src/semantic)
set (SEMANTIC_INCLUDE 
  ${SEMANTIC_DIR}/include
  ${LLVM_INCLUDE_DIR}
)
#################################################
# Set the names that you use.
#################################################
set (SEMANTIC_SOURCES
  ${SEMANTIC_DIR}/SemanticVisitor.cpp
  ${SEMANTIC_DIR}/PropertyManager.cpp
)