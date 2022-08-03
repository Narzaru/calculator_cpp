#ifndef SRC_MODELS_CALCULATOR_TOKEN_H_
#define SRC_MODELS_CALCULATOR_TOKEN_H_

#include <cstdlib>
#include <string>

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

  bool operator==(const Token &other);

  TokenName GetName() { return name_; }
  const std::string &GetLexeme() { return lexeme_; }

 private:
  TokenName name_;
  std::string lexeme_;
};

#endif  // SRC_MODELS_CALCULATOR_TOKEN_H_
