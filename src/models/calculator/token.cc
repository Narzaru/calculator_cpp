#include "token.h"

#include <utility>

namespace s21::math {

Token::Token(TokenName token_name, Token::string lexeme)
    : name_(token_name), value_(std::move(lexeme)) {}

bool Token::operator==(const Token &other) const {
  return other.name_ == name_ && other.value_ == value_;
}

bool Token::operator==(const TokenName &name) const {
  return name_ == name;
}

bool Token::operator!=(const TokenName &name) const {
  return !(*this == name);
}

Token &Token::Rename(TokenName name) {
  name_ = name;
  return *this;
}

}  // namespace s21::math
