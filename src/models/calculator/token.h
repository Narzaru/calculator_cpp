#ifndef SRC_MODELS_CALCULATOR_TOKEN_H_
#define SRC_MODELS_CALCULATOR_TOKEN_H_

#include <cstdlib>
#include <iostream>
#include <string>

namespace s21::math {

enum class TokenName {
  kNumber,
  kOpenBracket,
  kFunction,
  kOperator,
  kCloseBracket,
  kVariable,
  kWrong,
  kUnary,
  kEmpty
};

class Token {
  using string = std::string;

 public:
  Token(TokenName token_name, string lexeme);

  bool operator==(const Token &other) const;
  bool operator==(const TokenName &name) const;
  bool operator!=(const TokenName &name) const;

  [[nodiscard]] TokenName GetName() const { return name_; }
  [[nodiscard]] const std::string &GetValue() const { return value_; }
  Token &Rename(TokenName name);

 private:
  TokenName name_;
  std::string value_;
};

}  // namespace s21::math

#endif  // SRC_MODELS_CALCULATOR_TOKEN_H_
