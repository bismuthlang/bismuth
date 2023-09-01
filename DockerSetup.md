# About

This document describes how to get this repository up and running in docker. This is based on the [docker image](https://github.com/ahfriedman/cs544-cs4533-docker) for the C/C++ version CS544/CS4533 at WPI---which was initially created by [Jack Sullivan](https://github.com/jhsul), and later extended by myself. 

# Instructions 

## Pre-requisites

* Docker (CLI) 
  * For Ubuntu, this can be done via running `sudo snap install docker`
* This repository downloaded locally (ie. `git clone https://github.com/ahfriedman/bismuth.git`)

## Step 1. Download the Docker Image

This takes a long time but you only need to do it once:

```sh
docker pull ahfriedman/cs544-cs4533-docker
```

## Step 2. Running the Docker Image 


```sh
docker run -it -v <location of repository>:/home/shared ahfriedman/cs544-cs4533-docker
```

Once you have run the docker image with the shared folder, you should be prompted with a terminal. The terminal will start in the working directory of /home/. The project files (the shared folder) is located at /home/shared. 

The first time you open the project in the docker image, you'll want to do is copy the antlr runtime into the project's files as shown below *(Note: this should only need to be done once. Afterwards, the files should stay updated across runs of the docker image)*.

```sh
cd /home
cp libantlr4-runtime.a shared/antlr/lib/
cd shared
```

## Step 3. Build the code

Once in the `/home/shared` directory (assuming that it is also the top-level directory of your project), running `./makeBuild.sh` will build the codebase. In very rare circumstances (ie, a change to the docker image's libraries) you may have to delete previously built files (`rm -rf ./build`) prior to running `./makeBuild.sh`


## Step 3. Running tests

From the `/home/shared` directory, running `./runTests.sh` will run all the test cases. 

## Step 4. Generating code coverage
*Note: This process may take a while to run*

From the `/home/shared` directory, running `./coverage.sh` will: 
1. Delete the `./cov` folder
2. Build the code into the `./cov` folder
3. Run all tests *(Note: all tests must pass for coverage to generate!)*
4. Output html files displaying code coverage to `./cov/coverage` *(Note: you may have to run `sudo chown -R $USER ./cov` from a terminal on your host to be able to view the files in a browser)*



# Common Issues

This section describes a few common issues you may encounter when using this container
to run the sample code. 

**NOTE: Whenever making changes to the files related to the project's build process (basically anything aside from your code) it is a good idea to remove the existing build folder and rebuild the entire project as this is sometimes required for these kinds of changes to take effect.**

## LLVM Not Linking/LLVM Not Found

In the starter code, LLVM defaults to the path `/usr/local/opt/llvm`; however, in this container, 
LLVM usually ends up in `/usr/lib/llvm-14` (the last number, in this case 14, may change depending on llvm version).
To fix this, update the `cmake/LLVM.cmake` file to correctly reference your LLVM installation. 

## ANTLR Not Linking/ANTLR Not Found

This issue can sometimes be resolved by editing the 
`target_link_libraries` command in *both* 
`src/CMakeLists.txt` and `src/test/CMakeLists.txt` to 
include `parser_lib`. For example, the corrected command 
may appear as: 

```
target_link_libraries(tests 
  PRIVATE
  ${ANTLR_RUNTIME_LIB}
  parser_lib
  lexparse_lib
  sym_lib
  semantic_lib
  utility_lib
  codegen_lib
  ${LLVM_LIBS}
  Catch2::Catch2WithMain
)
```

## ANTLR/LLVM Linked, but functions undefined

This project can be sensitive to which compiler you use--in particular, clang seems to work better than gcc (which would make sense given that we are working with llvm); however, on Linux, the default compiler tends to be `gcc`. While this docker container attempts to set `clang` and `clang++` to be used as your default compiler, if you are still running into issues, it may be worthwhile to rebuild your project (and your ANTLR library) with `CC=clang CXX=clang++` prefixed to all cmake commands. For example, 
`cmake -S . -B build` becomes `CC=clang CXX=clang++ cmake -S . -B build` and `cmake --build build` becomes `CC=clang CXX=clang++ cmake --build build`. 
