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


class CompilerInput {

private: 
    antlr4::ANTLRInputStream * inputStream; 
    std::vector<std::string> pathSteps; 

public: 
    CompilerInput(
        antlr4::ANTLRInputStream * i, 
        std::vector<std::string> ps)
        : inputStream(i)
        , pathSteps(ps)
    {}

    virtual ~CompilerInput() = default;

    antlr4::ANTLRInputStream * getInputStream() { return inputStream; }
    std::vector<std::string> getPathSteps() { 
        std::string ans = ""; 
        for(auto s : pathSteps)
        {
            ans += "::" + s;
        } 
        std::cout << "80 PS " << ans << std::endl; 
        return pathSteps; 
    }
    virtual std::string getSourceName() { return inputStream->getSourceName(); }

    virtual std::variant<llvm::raw_ostream *, std::error_code> getIROut() = 0;
    virtual std::variant<llvm::raw_pwrite_stream *, std::error_code> getObjectOut() = 0;
    virtual std::optional<std::filesystem::path> getOutputPath() = 0;
    

};

class FileInput : public CompilerInput {

private: 
    std::filesystem::path outputPath; 

public: 
    FileInput(
        antlr4::ANTLRInputStream * i, 
        std::vector<std::string> ps,
        std::filesystem::path o)
        : CompilerInput(i, ps)
        , outputPath(o)
    {}

    
    std::variant<llvm::raw_ostream *, std::error_code> getIROut() override
    {
        std::string irFileName = outputPath.replace_extension(".ll");
        std::error_code ec;
        llvm::raw_fd_ostream * irFileStream = new llvm::raw_fd_ostream(irFileName, ec);

        if(ec) return ec; 
        return irFileStream;
    }

    std::variant<llvm::raw_pwrite_stream *, std::error_code> getObjectOut() override
    {
        std::string filename = outputPath.replace_extension(".o");
        std::error_code ec;
        llvm::raw_fd_ostream * fileStream = new llvm::raw_fd_ostream(filename, ec, llvm::sys::fs::OF_None);;

        if(ec) return ec; 
        return fileStream;
    }

    std::optional<std::filesystem::path> getOutputPath() override { return outputPath; }
};

class VirtualInput : public CompilerInput {

private:
    std::string irStr; 
    std::string objStr; 

public: 
    VirtualInput(
        antlr4::ANTLRInputStream * i, 
        std::vector<std::string> ps)
        : CompilerInput(i, ps)
    {}

    std::string getSourceName() override 
    {
        std::string ans = "<virtual>"; 
        for(auto s : getPathSteps())
        {
            ans += "::" + s;
        } 
        return ans; 
        // return inputStream->getSourceName(); 
    }

    std::variant<llvm::raw_ostream *, std::error_code> getIROut() override 
    { 
        return new llvm::raw_string_ostream(irStr);
    }

    std::variant<llvm::raw_pwrite_stream *, std::error_code> getObjectOut() override 
    {
        return new llvm::buffer_unique_ostream(
            std::make_unique<llvm::raw_string_ostream>(objStr)
        );
    }

    std::optional<std::filesystem::path> getOutputPath() override { return std::nullopt; }

    std::string getIrStr() { return irStr; }
    std::string getObjStr() { return objStr; }
};


std::vector<CompilerInput *> getInputsFromFiles(std::string argSrcPath, std::string argBuildPath, std::string outputFileName, std::vector<std::string> inputFileName);

llvm::TargetMachine * getTargetMachine();



std::vector<std::pair<BismuthParser::CompilationUnitContext *, CompilerInput *>> Stage_lexParse(std::vector<CompilerInput *> inputs);
std::vector<std::pair<TCompilationUnitNode *, CompilerInput *>> Stage_Semantic(std::vector<std::pair<BismuthParser::CompilationUnitContext *, CompilerInput *>> inputs, bool demoMode, bool isVerbose, DisplayMode toStringMode);
void Stage_CodeGen(std::vector<std::pair<TCompilationUnitNode *, CompilerInput *>> inputs,  std::string outputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith);

int compile(std::vector<CompilerInput *> inputs, std::string outputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith);
int compileFiles(std::string argSrcPath, std::string argBuildPath, std::string outputFileName, std::vector<std::string> inputFileName, bool demoMode, bool isVerbose, DisplayMode toStringMode, bool printOutput, bool noCode, CompileType compileWith);