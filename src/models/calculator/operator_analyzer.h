#ifndef SRC_MODELS_CALCULATOR_TOKEN_PARSER_H_
#define SRC_MODELS_CALCULATOR_TOKEN_PARSER_H_

#include "token.h"

namespace s21 {
namespace math {

class IOperatorAnalyzer {
 public:
  virtual int priority(const Token& token) const = 0;
  virtual bool is_right_associative(const Token& token) const = 0;
  virtual bool is_left_associative(const Token& token) const = 0;
};

class OperatorAnalyzer : public IOperatorAnalyzer {
 public:
  int priority(const Token& token) const override;
  bool is_right_associative(const Token& token) const override;
  bool is_left_associative(const Token& token) const override;
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_TOKEN_PARSER_H_
