#include "token_compiler.h"

#include <string>

#include "token.h"

MathTokenCompiler::MathTokenCompiler(s21::ITokenAnalyzer &token_analyzer)
    : token_analyzer_(token_analyzer) {}

TokenName MathTokenCompiler::get_token_name(const std::string &lexeme) {
  if (token_analyzer_.is_number(lexeme)) {
    return TokenName::kNumber;
  } else if (token_analyzer_.is_open_bracket(lexeme)) {
    return TokenName::kOpenBracket;
  } else if (token_analyzer_.is_function(lexeme)) {
    return TokenName::kFunction;
  } else if (token_analyzer_.is_operator(lexeme)) {
    return TokenName::kOperator;
  } else if (token_analyzer_.is_close_bracket(lexeme)) {
    return TokenName::kCloseBracket;
  } else if (token_analyzer_.is_variable(lexeme)) {
    return TokenName::kVariable;
  }
  return TokenName::kWrong;
}
