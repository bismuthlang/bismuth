# Settings for the ANTLR components

set(ANTLR ${CMAKE_SOURCE_DIR}/antlr/antlr4.jar)
set(ANTLR_INCLUDE ${CMAKE_SOURCE_DIR}/antlr/include)
set(ANTLR_LIB ${CMAKE_SOURCE_DIR}/antlr/lib)
set(ANTLR_GENERATED_DIR ${CMAKE_SOURCE_DIR}/src/generated)

# Add all generated ANTLR sources we care about here
SET(ANTLR_SOURCES
  ${ANTLR_GENERATED_DIR}/WPLLexer.cpp
  ${ANTLR_GENERATED_DIR}/WPLParser.cpp 
  ${ANTLR_GENERATED_DIR}/WPLBaseListener.cpp
  ${ANTLR_GENERATED_DIR}/WPLBaseVisitor.cpp
  ${ANTLR_GENERATED_DIR}/WPLListener.cpp
  ${ANTLR_GENERATED_DIR}/WPLVisitor.cpp
)

#########################################################################################
# Modify the next line if your static ANTLR C++ runtime is not named libantlr4-runtime.a
#########################################################################################
set(ANTLR_RUNTIME_LIB ${ANTLR_LIB}/libantlr4-runtime.a)