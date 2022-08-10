#include "syntactical_analyzer.h"

#include <cstddef>
#include <iterator>
#include <string>

#include "token.h"

namespace s21::math {

TokenName SyntacticalAnalyzer::GetTokenName(const std::string &lexeme) {
  if (IsNumber(lexeme)) {
    return TokenName::kNumber;
  } else if (IsOpenBracket(lexeme)) {
    return TokenName::kOpenBracket;
  } else if (IsFunction(lexeme)) {
    return TokenName::kFunction;
  } else if (IsOperator(lexeme)) {
    return TokenName::kOperator;
  } else if (IsCloseBracket(lexeme)) {
    return TokenName::kCloseBracket;
  } else if (IsVariable(lexeme)) {
    return TokenName::kVariable;
  }
  return TokenName::kWrong;
}

std::list<Token> SyntacticalAnalyzer::compile(
    const std::list<std::string> &lexemes) {
  std::list<Token> out_list;

  // parses the token into token names
  for (const std::string &lexeme : lexemes) {
    out_list.emplace_back(GetTokenName(lexeme), lexeme);
  }

  // additionaly parses operators + and - into unary
  TokenName prew_name = TokenName::kOperator;
  for (Token &token : out_list) {
    if (prew_name == TokenName::kOperator || prew_name == TokenName::kUnary ||
        prew_name == TokenName::kOpenBracket) {
      if (token.GetValue() == "+" || token.GetValue() == "-") {
        if (token == TokenName::kOperator || token == TokenName::kOpenBracket) {
          token.rename(TokenName::kUnary);
        }
      }
    }
    prew_name = token.GetName();
  }

  return out_list;
}

}  // namespace s21
