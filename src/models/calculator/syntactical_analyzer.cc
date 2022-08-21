#include "syntactical_analyzer.h"

#include <string>

#include "token.h"

namespace s21::math {

Name SyntacticalAnalyzer::GetTokenName(const std::string &lexeme) {
  if (IsNumber(lexeme)) {
    return Name::kNumber;
  } else if (IsOpenBracket(lexeme)) {
    return Name::kOpenBracket;
  } else if (IsFunction(lexeme)) {
    return Name::kInfixFunction;
  } else if (IsOperator(lexeme)) {
    return Name::kOperator;
  } else if (IsCloseBracket(lexeme)) {
    return Name::kCloseBracket;
  } else if (IsVariable(lexeme)) {
    return Name::kVariable;
  }
  return Name::kUnknown;
}

std::list<MathToken> SyntacticalAnalyzer::Compile(
    const std::list<std::string> &lexemes) {
  std::list<MathToken> out_list;

  // parses the token into token names
  for (const std::string &lexeme : lexemes) {
    out_list.emplace_back(GetTokenName(lexeme), lexeme);
  }

  // additionally parses operators + and - into unary
  Name prew_name = Name::kOperator;
  for (MathToken &token : out_list) {
    if (prew_name == Name::kOperator || prew_name == Name::kUnaryOperator ||
        prew_name == Name::kOpenBracket) {
      if (token.GetValue() == "+" || token.GetValue() == "-") {
        if (token == Name::kOperator || token == Name::kOpenBracket) {
          token.Rename(Name::kUnaryOperator);
        }
      }
    }
    prew_name = token.GetName();
  }

  return out_list;
}

}  // namespace s21::math
