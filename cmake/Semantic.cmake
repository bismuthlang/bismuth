# Semantic analysis component module

set (SEMANTIC_DIR ${CMAKE_SOURCE_DIR}/src/semantic)
set (SEMANTIC_INCLUDE 
  ${SEMANTIC_DIR}/include
)
#################################################
# Set the names that you use.
#################################################
set (SEMANTIC_SOURCES
  ${SEMANTIC_DIR}/SemanticVisitor.cpp
  ${SEMANTIC_DIR}/ProtocolVisitor.cpp
  ${SEMANTIC_DIR}/PropertyManager.cpp
)