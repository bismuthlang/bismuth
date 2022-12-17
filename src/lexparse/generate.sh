#! /usr/bin/env bash

if [ ! -f ../generated/$1Parser.cpp ] || [ "$1.g4" -nt "../generated/$1Parser.cpp" ]; 
then 
  echo ">>> Generating <<<"
  pwd
  java -jar ../../antlr/antlr4.jar -Dlanguage=Cpp -visitor -listener -o ../generated $1.g4 
  touch parser_sources.h
fi