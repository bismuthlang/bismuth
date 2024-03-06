/**
 * @file Compile.h
 * @author Alex Friedman (ahf.dev)
 * @brief Handles the functionality for running the compiler 
 * @version 0.1
 * @date 2024-02-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <iostream>
#include <fstream>
#include <memory> // Smart pointers 
#include <filesystem> // Current path 

#include "antlr4-runtime.h"
#include "BismuthLexer.h"
#include "BismuthParser.h"

#include "TypedAST.h"

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

using std::unique_ptr; 
using std::shared_ptr; 
using std::fstream; 

enum CompileType
{
    none,
    clang,
    gcc,
    clangll,
};


std::filesystem::path getRelativePath(std::filesystem::path& currentPath, std::filesystem::path& given);

std::vector<std::string> pathToIdentifierSteps(std::filesystem::path& relPath);


struct CompilerInput {
    antlr4::ANTLRInputStream * inputStream; 
    std::filesystem::path outputPath; 

    std::vector<std::string> pathSteps; 

    CompilerInput(antlr4::ANTLRInputStream * i, std::filesystem::path o, std::vector<std::string> ps)
        : inputStream(i)
        , outputPath(o)
        , pathSteps(ps)
    {}

    std::variant<llvm::raw_pwrite_stream *, std::error_code> getIROut() 
    {
        std::string irFileName = outputPath.replace_extension(".ll");
        std::error_code ec;
        llvm::raw_fd_ostream * irFileStream = new llvm::raw_fd_ostream(irFileName, ec);

        if(ec) return ec; 
        return irFileStream;
    }

    std::variant<llvm::raw_pwrite_stream *, std::error_code> getObjectOut() 
    {
        std::string filename = outputPath.replace_extension(".o");
        std::error_code ec;
        llvm::raw_fd_ostream * fileStream = new llvm::raw_fd_ostream(filename, ec, llvm::sys::fs::OF_None);;

        if(ec) return ec; 
        return fileStream;
    }

};

// struct SemanticInput {
//     BismuthParser::CompilationUnitContext * ctx; 
//     CompilerInput io;

//     SemanticInput(BismuthParser::CompilationUnitContext * c, CompilerInput i)
//         : ctx(c)
//         , io(i)
//     {}
// };

// class CodeGenInput {
//     TCompilationUnitNode * node; 
//     CompilerInput io; 

// public: 
//     CodeGenInput(TCompilationUnitNode * n, CompilerInput i)
//         : node(n)
//         , io(i)
//     {}

//     virtual llvm::raw_pwrite_stream getIROut() const = 0; 
// };

// class CodeGenFileInput : public CodeGenInput {

// public: 
//     CodeGenFileInput(TCompilationUnitNode * n, CompilerInput i)
//         : node(n)
//         , io(i)
//     {}

//     virtual llvm::raw_pwrite_stream getIROut() const = 0; 
// };

std::vector<CompilerInput> getInputsFromFiles(std::string argSrcPath, std::string argBuildPath, std::string outputFileName, std::vector<std::string> inputFileName);

llvm::TargetMachine * getTargetMachine();



std::vector<std::pair<BismuthParser::CompilationUnitContext *, CompilerInput>> Stage_lexParse(std::vector<CompilerInput> inputs);
std::vector<std::pair<TCompilationUnitNode *, CompilerInput>> Stage_Semantic(std::vector<std::pair<BismuthParser::CompilationUnitContext *, CompilerInput>> inputs, bool demoMode, bool isVerbose, DisplayMode toStringMode);
void Stage_CodeGen(std::vector<std::pair<TCompilationUnitNode *, CompilerInput>> inputs,  std::string outputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith);


int compile(std::string argSrcPath, std::string argBuildPath, std::string outputFileName, std::vector<std::string> inputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith);