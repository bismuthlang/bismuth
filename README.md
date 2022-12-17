# README

This Alex Friedman's implementation of the Worcester Polytechnic Instutite, WPI, Programming Language (WPL). 


## Prerequisites

* The project's [docker image](https://github.com/ahfriedman/cs544-cs4533-docker) 
* OR an equivalent llvm-12 environment


## Setting up

### With Docker

With docker, most of the project setup should be automatic. Please see the the [common issues](https://github.com/ahfriedman/cs544-cs4533-docker#common-issues)
section of that repository for any debugging steps. 


### Without Docker

***NOTE: without docker, test cases may fail to run as they expect the `/programs` directory to be located in `/home/shared/`!***

Assuming that you have all of the required programs at the correct versions, the only thing 
that you should have to do after cloning this repository is to build and copy and `antlr4-runtime.a` library for your system, and then 
copy it into the `/antlr/lib` directory. 

If you made changes for your platform to any of the .cmake files or CMakeLists.txt files, you will probably need to make them in this project as well.

## Structure

- `/antlr` - Contains the relevant ANTLR library.
- `/build` - Automatically generated output files of the project.
- `/cmake` - Contains the cmake files required to setup the project's depedencies. Each file corresponds to a separate part of the project.
- `/programs` - Contains sample WPL programs used for testing the compiler. ***Many test cases rely on calculating the sha256 hash of these programs. Editing them may cause test cases to break!***
- `/src` - Contains the main project files--including wplc.cpp which is the main entry point for the compiler
- `/src/codegen` - Code generation phase of the compiler
- `/src/generated` - Automatically generated ANTLR files based on the language's grammmar
- `/src/lexparse` - The language's grammar 
- `/src/runtime` - The language's runtime library
- `/src/semantic` - The language's semantic analysis phase (type checking, type inference, etc).
- `/src/symbol` - Files related to the symbol table and type definitions
- `/src/utility` - Misc. files required for the compiler--primarily relating to test cases and error handling
- `/test` - Compiler test cases primarily broken down based on corresponding file in `/src`.
- `./makeBuild.sh` - Makes a build of the project
- `./runTests.sh` - Runs the project's test cases