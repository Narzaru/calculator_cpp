#include "token.h"

#include <utility>

namespace s21 {
namespace math {

Token::Token() : name_(TokenName::kEmpty), lexeme_() {}

Token::Token(TokenName token_name, Token::string lexeme)
    : name_(token_name), lexeme_(std::move(lexeme)) {}

bool Token::operator==(const Token& other) {
  return other.name_ == name_ && other.lexeme_ == lexeme_;
}

Token& Token::rename(TokenName name) {
  name_ = name;
  return *this;
}

}  // namespace math
}  // namespace s21
