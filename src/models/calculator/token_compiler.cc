#include "token_compiler.h"

#include <cstddef>
#include <iterator>
#include <string>

#include "token.h"

namespace s21 {
namespace math {
TokenCompiler::TokenCompiler(const ILexemeAnalyzer &token_analyzer)
    : lexeme_analyzer_(token_analyzer) {}

TokenName TokenCompiler::get_token_name(const std::string &lexeme) {
  if (lexeme_analyzer_.is_number(lexeme)) {
    return TokenName::kNumber;
  } else if (lexeme_analyzer_.is_open_bracket(lexeme)) {
    return TokenName::kOpenBracket;
  } else if (lexeme_analyzer_.is_function(lexeme)) {
    return TokenName::kFunction;
  } else if (lexeme_analyzer_.is_operator(lexeme)) {
    return TokenName::kOperator;
  } else if (lexeme_analyzer_.is_close_bracket(lexeme)) {
    return TokenName::kCloseBracket;
  } else if (lexeme_analyzer_.is_variable(lexeme)) {
    return TokenName::kVariable;
  }
  return TokenName::kWrong;
}

std::list<Token> TokenCompiler::compile(const std::list<std::string> &lexemes) {
  std::list<Token> out_list;

  // parses the token into token names
  for (const std::string &lexeme : lexemes) {
    out_list.emplace_back(get_token_name(lexeme), lexeme);
  }

  // additionaly parses operators + and - into unary
  TokenName prew_name = TokenName::kOperator;
  for (Token &token : out_list) {
    if (prew_name == TokenName::kOperator || prew_name == TokenName::kUnary ||
        prew_name == TokenName::kOpenBracket) {
      if (token.getLexeme() == "+" || token.getLexeme() == "-") {
        if (token.getName() == TokenName::kOperator ||
            token.getName() == TokenName::kOpenBracket) {
          token.rename(TokenName::kUnary);
        }
      }
    }
    prew_name = token.getName();
  }

  return out_list;
}

}  // namespace math
}  // namespace s21
