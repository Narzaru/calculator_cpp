#include "token_analyzer.h"

#include "token.h"

namespace s21 {
namespace math {
bool TokenAnalyzer::is_number(const Token& token) const {
  return token.getName() == TokenName::kNumber;
}

bool TokenAnalyzer::is_open_bracket(const Token& token) const {
  return token.getName() == TokenName::kOpenBracket;
}

bool TokenAnalyzer::is_function(const Token& token) const {
  return token.getName() == TokenName::kFunction;
}

bool TokenAnalyzer::is_operator(const Token& token) const {
  return token.getName() == TokenName::kOperator ||
         token.getName() == TokenName::kUnary;
}

bool TokenAnalyzer::is_close_bracket(const Token& token) const {
  return token.getName() == TokenName::kCloseBracket;
}

bool TokenAnalyzer::is_variable(const Token& token) const {
  return token.getName() == TokenName::kVariable;
}

bool TokenAnalyzer::is_wrong(const Token& token) const {
  return token.getName() == TokenName::kWrong;
}

bool TokenAnalyzer::is_unary(const Token& token) const {
  return token.getName() == TokenName::kUnary;
}

bool TokenAnalyzer::is_empty(const Token& token) const {
  return token.getName() == TokenName::kEmpty;
}

int TokenAnalyzer::priority(const Token& token) const {
  int priority = 0;
  const std::string& lexeme = token.getLexeme();

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

bool TokenAnalyzer::is_right_associative(const Token& token) const {
  if (token.getName() == TokenName::kUnary || token.getLexeme() == "pow" ||
      token.getLexeme() == "^") {
    return true;
  }
  return false;
}

bool TokenAnalyzer::is_left_associative(const Token& token) const {
  return !is_right_associative(token);
}

}  // namespace math
}  // namespace s21
