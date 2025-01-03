# README

Implementation of the [bismuth](https://bismuth-lang.org) programming language. 


## Step 1: Setup

Most dependencies for compiling and running Bismuth are automatically handled via the 
CMake build process; however, there are a few steps that need to be taken manually to 
get up and running so that CMake can handle the rest. Currently, the options are:
1. (Recommended) The project's [docker image](https://github.com/bismuthlang/bismuth-dev-docker) 
2. The project's nix flake (limited support for testing + debugging)
3. An equivalent llvm-19 environment (not recommended)

### Docker Setup
The instructions for getting started with the Bismuth development image can be found in 
[DockerSetup.md](./DockerSetup.md)

### Nix Setup
A development shell for Bismuth can be created using Nix. This has been 
tested with both Nix package manager standalone (v2.23.3+) and NixOS (v24.05+).
Running `nix develop` in the top level directory of this project will automatically setup everything 
for you and leave your shell in an environment where Bismuth can be compiled.

### Manual Setup 
Manually setting up your computer's environment to compile Bismuth is not recommended. 
The main challenge with such an approach is that various different C/C++ compilers are
not easily interchangeable (i.e., if you use one compiler for one component of a project, 
you tend to need to use the same compiler for all other portions of the project). 
For Bismuth, this means that the LLVM IR dev library, ANTLR library, and the Bismuth source code
all need to be compiled with the same compiler. The challenge, however, is that LLVM is typically pre-packaged and 
installed system-wide. As such, you'll need to use the same compiler for Bismuth as whatever was used to pre-package
LLVM. For systems using `apt` (Debian, Ubuntu, etc), this means that you'll typically need to use Clang despite 
the OS defaulting your C and C++ compiler to GCC (hence, the docker image and nix flake to help 
ensure no environment conflicts). If you do wish to proceed with a manual setup, the Docker file and nix flake 
should be a great starting place for seeing what dependencies you'll need and how to configure your environment. 



## Step 2: Build the code
Running `./makeBuild.sh` will build the codebase. In very rare circumstances (ie, a change to the docker image's libraries) you may have to delete previously built files (`rm -rf ./build`) prior to running `./makeBuild.sh`

## Step 3. Running tests

Running `./runTests.sh` will run all the test cases and print a report of the successes and failures.

## Step 4. Compiling a Bismuth program

Running `./tester.sh <.bismuth file without extension>` will compile the program and run it (if compiling was successful). 

For example, to run `./programs/example.bismuth`, one could run the command `./tester.sh ./programs/example`.

To compile a program with the Bismuth standard library, use `./compileBSL.sh` instead of `./tester.sh`.

## Step 5. Generating code coverage
*Note: This process may take a while to run*

Running `./coverage.sh` will: 
1. Delete the `./cov` folder
2. Build the code into the `./cov` folder
3. Run all tests *(Note: all tests must pass for coverage to generate!)*
4. Output html files displaying code coverage to `./cov/coverage` *(Note: you may have to run `sudo chown -R $USER ./cov` from a terminal on your host to be able to view the files in a browser)*




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