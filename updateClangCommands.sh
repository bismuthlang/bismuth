#!/bin/bash
# Utility script for updating the build commands. This is useful for clang LSPs
# Based on:
#  - https://gist.github.com/Strus/042a92a00070a943053006bf46912ae9
# 
# If issues persist with LSP after re-building, see: 
#  - https://github.com/clangd/clangd/issues/617

cmake -S . -G "Unix Makefiles" -B cmake
# ln -s cmake/compile_commands.json .
