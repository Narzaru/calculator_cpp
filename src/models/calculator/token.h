#ifndef SRC_MODELS_CALCULATOR_TOKEN_H_
#define SRC_MODELS_CALCULATOR_TOKEN_H_

#include <cstdlib>
#include <iostream>
#include <string>

namespace s21 {
namespace math {

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
  Token();
  Token(TokenName token_name, string lexeme);

  Token(const Token &other) = default;
  Token(Token &&other) = default;
  Token &operator=(const Token &other) = default;
  Token &operator=(Token &&other) = default;

  bool operator==(const Token &other) const;
  bool operator==(const TokenName &name) const;
  bool operator!=(const TokenName &name) const;

  [[nodiscard]] TokenName getName() const { return name_; }
  [[nodiscard]] const std::string &getLexeme() const { return lexeme_; }
  Token &rename(TokenName name);

 private:
  TokenName name_;
  std::string lexeme_;
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_TOKEN_H_
