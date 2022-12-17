#pragma once
/**
 * @file test_error_handlers.h
 * @author gpollice
 * @brief Error handlers to be used in tests. They just throw an exception
 * @version 0.1
 * @date 2022-07-06
 */

class TestErrorListener: public antlr4::BaseErrorListener {
  virtual void syntaxError(
      antlr4::Recognizer *recognizer,
      antlr4::Token *offendingSymbol,
      size_t line,
      size_t charPositionInLine,
      const std::string &msg,
      std::exception_ptr e) override {
    throw std::invalid_argument("test error thrown: " + msg);
  }
};