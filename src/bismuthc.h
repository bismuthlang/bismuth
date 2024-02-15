#pragma once

#include <iostream>
#include <fstream>
#include <memory> // Smart pointers 
#include <filesystem> // Current path 

#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"

#include "TypedAST.h"

// #include "BismuthErrorHandler.h"
#include "SemanticVisitor.h"
#include "CodegenVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/IR/LegacyPassManager.h"

#include "ExecUtils.h"
#include <sstream> //String stream

// https://stackoverflow.com/questions/1435953/how-can-i-pass-git-sha1-to-compiler-as-definition-using-cmake
#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "0000000" // 0000000 means uninitialized
#endif

using std::unique_ptr; 
using std::shared_ptr; 
using std::fstream; 


std::filesystem::path getRelativePath(std::filesystem::path& currentPath, std::filesystem::path& given)
{
    return given.string().starts_with(currentPath.string()) 
        ? std::filesystem::relative(given, currentPath)
        : given; 
}

std::vector<std::string> pathToIdentifierSteps(std::filesystem::path& relPath)//std::filesystem::path& currentPath, std::filesystem::path& given)
{
    std::vector<std::string> parts; 

    for(auto it : relPath)
    {
        parts.push_back(it);
    }

    return parts; 
} 

struct CompilerInput {
    antlr4::ANTLRInputStream * inputStream; 
    // std::string outputPath; 
    std::filesystem::path outputPath; 

    std::vector<std::string> pathSteps; 

    CompilerInput(antlr4::ANTLRInputStream * i, std::filesystem::path o, std::vector<std::string> ps)
        : inputStream(i)
        , outputPath(o)
        , pathSteps(ps)
    {}
};