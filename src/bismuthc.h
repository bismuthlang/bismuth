#pragma once

#include "Compile.cpp"

#include <fstream>
#include <memory> // Smart pointers 


// https://stackoverflow.com/questions/1435953/how-can-i-pass-git-sha1-to-compiler-as-definition-using-cmake
#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "0000000" // 0000000 means uninitialized
#endif

using std::unique_ptr; 
using std::shared_ptr; 
using std::fstream; 
