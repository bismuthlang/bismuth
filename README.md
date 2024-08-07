# README

Implementation of the [bismuth](https://bismuth-lang.org) programming language. 


## Prerequisites

* The project's [docker image](https://github.com/ahfriedman/cs544-cs4533-docker) 
* OR an equivalent llvm-12 environment (not recommended)


## Setting up, Running Code, Tests, & Coverage

Instructions for how to set up the repository using docker can be found in [DockerSetup.md](./DockerSetup.md). While it is possible to get the code running without docker, the process is much more involved and fairly system dependent. In addition,  without docker, test cases may fail to run as they expect the `/programs` directory to be located in `/home/shared/`.



## Structure

- `/antlr` - Contains the relevant ANTLR library.
- `/build` - Automatically generated output files of the project.
- `./coverage.sh` - Runs coverage based on the test cases
- `./cov` - Automatically generated folder containing coverage information
- `/cmake` - Contains the cmake files required to setup the project's dependencies. Each file corresponds to a separate part of the project.
- `/programs` - Contains sample programs used for testing the compiler. ***Many test cases rely on calculating the sha256 hash of these programs. Editing them may cause test cases to break!***
- `/src` - Contains the main project files--including bismuthc.cpp which is the main entry point for the compiler
- `/src/codegen` - Code generation phase of the compiler
- `/src/generated` - Automatically generated ANTLR files based on the language's grammar
- `/src/lexparse` - The language's grammar 
- `/src/runtime` - The language's runtime library
- `/src/semantic` - The language's semantic analysis phase (type checking, type inference, etc).
- `/src/symbol` - Files related to the symbol table and type definitions
- `/src/utility` - Misc. files required for the compiler--primarily relating to test cases and error handling
- `./tester.sh` - Compiles and runs a given file
- `/test` - Compiler test cases primarily broken down based on corresponding file in `/src`.
- `./makeBuild.sh` - Makes a build of the project
- `./runTests.sh` - Runs the project's test cases