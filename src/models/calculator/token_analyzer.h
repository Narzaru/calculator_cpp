#ifndef SRC_MODELS_CALCULATOR_TOKEN_PARSER_H_
#define SRC_MODELS_CALCULATOR_TOKEN_PARSER_H_

#include "token.h"

namespace s21 {
namespace math {

class ITokenAnalyzer {
 public:
  virtual bool is_number(const Token& token) const = 0;
  virtual bool is_open_bracket(const Token& token) const = 0;
  virtual bool is_function(const Token& token) const = 0;
  virtual bool is_operator(const Token& token) const = 0;
  virtual bool is_close_bracket(const Token& token) const = 0;
  virtual bool is_variable(const Token& token) const = 0;
  virtual bool is_wrong(const Token& token) const = 0;
  virtual bool is_unary(const Token& token) const = 0;
  virtual bool is_empty(const Token& token) const = 0;

  virtual int priority(const Token& token) const = 0;
  virtual bool is_right_associative(const Token& token) const = 0;
  virtual bool is_left_associative(const Token& token) const = 0;
};

class TokenAnalyzer : public ITokenAnalyzer {
 public:
  bool is_number(const Token& token) const override;
  bool is_open_bracket(const Token& token) const override;
  bool is_function(const Token& token) const override;
  bool is_operator(const Token& token) const override;
  bool is_close_bracket(const Token& token) const override;
  bool is_variable(const Token& token) const override;
  bool is_wrong(const Token& token) const override;
  bool is_unary(const Token& token) const override;
  bool is_empty(const Token& token) const override;

  int priority(const Token& token) const override;
  bool is_right_associative(const Token& token) const override;
  bool is_left_associative(const Token& token) const override;
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_TOKEN_PARSER_H_
