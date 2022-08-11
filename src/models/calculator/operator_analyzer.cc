#include "operator_analyzer.h"

#include "token.h"

namespace s21::math {

int OperatorAnalyzer::Priority(const Token &token) const {
  int priority = 0;
  const std::string &lexeme = token.GetValue();

  if (token != TokenName::kUnary && (lexeme == "+" || lexeme == "-")) {
    priority = 1;
  } else if (lexeme == "*" || lexeme == "/") {
    priority = 2;
  } else if (lexeme == "mod" || lexeme == "%") {
    priority = 2;
  } else if (lexeme == "^" || lexeme == "pow") {
    priority = 3;
  } else if (token == TokenName::kUnary && (lexeme == "+" || lexeme == "-")) {
    priority = 4;
  } else {
    priority = 0;
  }
  return priority;
}

bool OperatorAnalyzer::IsRightAssociative(const Token &token) const {
  if (token.GetName() == TokenName::kUnary || token.GetValue() == "pow" || token.GetValue() == "^") {
    return true;
  }
  return false;
}

bool OperatorAnalyzer::IsLeftAssociative(const Token &token) const {
  return !IsRightAssociative(token);
}

}  // namespace s21::math
