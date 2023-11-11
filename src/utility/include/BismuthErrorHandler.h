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
#include "antlr4-runtime.h"
#include <string>
#include <vector>
#include <sstream>

/**
 * @brief Defines various error types the compiler can throw
 *
 */
enum ErrType
{
  SYNTAX,   // Syntactic errors         (Lexer/parser)
  SEMANTIC, // Semantic errors          (Semantic Analysis)
  CODEGEN   // Code generation errors   (LLVM IR Codegen)
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
};

/**
 * @brief Defines an error in the language
 *
 */
struct BismuthError
{
  antlr4::Token *token; // Where the error occurred
  std::string message;  // Error Message text

  BismuthError(antlr4::Token *tok, std::string msg)
  {
    token = tok;
    message = msg;
  }

  std::string toString()
  {
    if (!token)
      return message; // TODO: DO BETTER
    std::ostringstream e;
    // token->getInputStream()->getSourceName()
    e << token->getInputStream()->getSourceName() << ":" << token->getLine() << ':' << token->getCharPositionInLine() << ": " << message;
    return e.str();
  }
};

struct ErrorChain
{
  ErrType errType;
  ErrSev errSev;

  std::vector<BismuthError *> chain;

  ErrorChain(antlr4::Token *tok, std::string msg, ErrType et, ErrSev es)
  {
    errType = et;
    errSev = es;
    BismuthError *primaryError = new BismuthError(tok, msg);
    chain.push_back(primaryError);
  }

  void addError(antlr4::Token *t, std::string msg)
  {
    BismuthError *e = new BismuthError(t, msg);
    chain.push_back(e);
  }

  void addCritWarning(antlr4::Token *t, std::string msg)
  {
    BismuthError *e = new BismuthError(t, msg);
    chain.push_back(e);
  }

  std::string toString()
  {
    std::ostringstream e;

    e << ErrorChain::getStringForSeverity(errSev) << " (" << ErrorChain::getStringForErrorType(errType) << "): " << std::endl;

    if (chain.size() == 0)
    {
      e << "UNKNOWN ERROR" << std::endl; // Shouldn't be possible anymore
    }

    for (BismuthError *error : chain)
    {
      e << error->toString() << std::endl;
    }

    return e.str();
  }

  ErrSev getSeverity() { return errSev; }

  static std::string getStringForErrorType(ErrType e)
  {
    switch (e)
    {
    case SYNTAX:
      return "SYNTAX";
    case SEMANTIC:
      return "SEMANTIC";
    case CODEGEN:
      return "CODEGEN";
    }
  }

  static std::string getStringForSeverity(ErrSev e)
  {
    switch (e)
    {
    case ERROR:
      return "Error";
    case CRITICAL_WARNING:
      return "Critical Warning";
    case WARNING:
      return "Warning";
    case INFO:
      return "Informational";
    }
  }
};

class BismuthErrorHandler
{
private:
  ErrType errType;

public:
  BismuthErrorHandler(ErrType ty) : errType(ty) {}

  ErrorChain *addError(antlr4::Token *t, std::string msg)
  {
    ErrorChain *e = new ErrorChain(t, msg, errType, ERROR);
    errors.push_back(e);

    return e;
  }

  ErrorChain *addCritWarning(antlr4::Token *t, std::string msg)
  {
    ErrorChain *e = new ErrorChain(t, msg, errType, CRITICAL_WARNING);
    errors.push_back(e);

    return e;
  }

  std::vector<ErrorChain *> &getErrors() { return errors; }

  std::string errorList()
  {
    std::ostringstream errList;
    for (ErrorChain *e : errors)
    {
      errList << e->toString() << std::endl;
    }
    errList << "Number of Errors: " << errors.size() << std::endl; 
    
    return errList.str();
  }

  /**
   * @brief Determines if the compiler has errors of a specific severity
   *
   * @param errorFlags int representation of ErrSev to determine which errors to check. Ie. 0 for all, 1 for ERROR, 2 for CRITICAL_WARNING, 3 = ERROR | CRITICAL_WARNING, etc.
   * @return true
   * @return false
   */
  bool hasErrors(int errorFlags)
  {
    // If no flags provided, then return if we have any
    if (!errorFlags)
      return !errors.empty();

    for (ErrorChain *err : errors)
    {
      std::cerr << err->getSeverity() << " & " << errorFlags << std::endl;
      if (err->getSeverity() & errorFlags)
        return true;
    }

    return false; //! errors.empty();
  }

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