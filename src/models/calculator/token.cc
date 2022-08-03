#include "token.h"

#include <utility>

Token::Token() : name_(TokenName::kEmpty), lexeme_() {};

Token::Token(TokenName token_name, Token::string lexeme)
    : name_(token_name), lexeme_(std::move(lexeme)) {}

bool Token::operator==(const Token &other) {
  if (other.name_ == name_ && other.lexeme_ == lexeme_) {
    return true;
  } else {
    return false;
  }
}
