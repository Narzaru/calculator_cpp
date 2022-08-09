#include "operator_analyzer.h"

#include "token.h"

namespace s21 {
namespace math {

int OperatorAnalyzer::priority(const Token& token) const {
  int priority = 0;
  const std::string& lexeme = token.GetValue();

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

bool OperatorAnalyzer::is_right_associative(const Token& token) const {
  if (token.GetName() == TokenName::kUnary || token.GetValue() == "pow" || token.GetValue() == "^") {
    return true;
  }
  return false;
}

bool OperatorAnalyzer::is_left_associative(const Token& token) const {
  return !is_right_associative(token);
}

}  // namespace math
}  // namespace s21
