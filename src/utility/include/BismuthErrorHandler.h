/**
 * @file BismuthErrorHandler.h
 * @author Alex Friedman (ahfriedman.com)
 * @brief Basic error handler for reporting during compile time. Based on example.
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "BaseErrorListener.h"
#include "Token.h"
#include <string>
#include <vector>
#include <optional>
// #include <source_location> // TODO: Upgrade to clang 15 or 16 and use https://en.cppreference.com/w/cpp/compiler_support/20#C.2B.2B20_library_features

/**
 * @brief Defines various error types the compiler can throw
 *
 */
enum ErrType
{
    SYNTAX,   // Syntactic errors         (Lexer/parser)
    SEMANTIC, // Semantic errors          (Semantic Analysis)
    CODEGEN,  // Code generation errors   (LLVM IR Codegen)
    COMBO     // Used to represent branches
};

/**
 * @brief Defines error severity levels
 *
 */
enum ErrSev
{
    ERROR = 1,            // Definitely an error, and the compiler should stop ASAP.
    CRITICAL_WARNING = 2, // Not an error per se, but need to stop compiling.
    WARNING = 4,          // Important warning message, but nothing that prevents compiling (Currently unused)
    INFO = 8,             // Informational message (currently unused)
    COMPILER = 16,        // Compiler error
};

/**
 * @brief Defines an error in the language
 *
 */
struct BismuthError
{
    // antlr4::Token *token; // Where the error occurred
    // std::string message;  // Error Message text

    BismuthError(ErrType et, ErrSev es, antlr4::Token *tok, std::string msg)
        : errorType(et)
        , errorSeverity(es)
        // , token(tok)
        // , message(msg)
    {
        addTrace(tok, msg);
    }

    void addTrace(antlr4::Token * tok, std::string msg)
    {
        trace.push_back(std::make_pair(tok, msg));
    }

    std::string toString(); 
    std::vector<std::string> asTrace(); 

    static std::string getStringForErrorType(ErrType e);
    static std::string getStringForSeverity(ErrSev e);

private: 
    ErrType errorType;
    ErrSev errorSeverity;
    std::vector<std::pair<antlr4::Token *, std::string>> trace; 
};

struct ErrorChain
{
    std::optional<BismuthError *> error; 
    std::vector<ErrorChain *> branches; 

    ErrorChain(antlr4::Token *tok, std::string msg, ErrType et, ErrSev es)
    {
        severity = es; 
        error = new BismuthError(et, es, tok, msg);
    }

    ErrorChain * addErrorAt(antlr4::Token *t);
    ErrorChain * addError(antlr4::Token *t, std::string msg);

    ErrorChain * addBranch(ErrorChain * other);
    // ErrorChain * addCritWarning(antlr4::Token *t, std::string msg);
    std::string toString();
    uint32_t getSeverity();
    // ErrSev getSeverity();

    std::vector<std::string> asTrace();

private: 
    ErrorChain(ErrorChain & other)
    {
        // other.errType = errType; 
        // other.errSev = errSev; 
        // other.chain = chain; 
        error = other.error; 
        branches = other.branches; 
        severity = other.severity;
    }

    uint32_t severity; 

};

class BismuthErrorHandler
{
private:
    ErrType errType;

public:
    BismuthErrorHandler(ErrType ty) : errType(ty) {}

    ErrorChain *addCompilerError(antlr4::Token *t, std::string msg);
    ErrorChain *addError(antlr4::Token *t, std::string msg);
    ErrorChain *addCritWarning(antlr4::Token *t, std::string msg);
    std::vector<ErrorChain *> &getErrors();
    std::string errorList();

    /**
     * @brief Determines if the compiler has errors of a specific severity
     *
     * @param errorFlags int representation of ErrSev to determine which errors to check. Ie. 0 for all, 1 for ERROR, 2 for CRITICAL_WARNING, 3 = ERROR | CRITICAL_WARNING, etc.
     * @return true
     * @return false
     */
    bool hasErrors(int errorFlags);

protected:
    std::vector<ErrorChain *> errors;
};

/**
 * @brief Wrapper around BismuthErrorHandler and antlr4::BaseErrorListener so we can report syntax errors just like the other error types
 *
 */
class BismuthSyntaxErrorListener : public antlr4::BaseErrorListener, public BismuthErrorHandler
{
    virtual void syntaxError(
        antlr4::Recognizer *recognizer,
        antlr4::Token *offendingSymbol,
        size_t line,
        size_t charPositionInLine,
        const std::string &msg,
        std::exception_ptr ex) override
    {
        ErrorChain *e = new ErrorChain(offendingSymbol, msg, SYNTAX, ERROR);
        errors.push_back(e);
        // throw std::invalid_argument("test error thrown: " + msg);
    }

public:
    BismuthSyntaxErrorListener() : BismuthErrorHandler(SYNTAX) {}
};
