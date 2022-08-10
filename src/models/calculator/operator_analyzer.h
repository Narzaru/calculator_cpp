#ifndef SRC_MODELS_CALCULATOR_OPERATOR_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_OPERATOR_ANALYZER_H_

#include "token.h"

namespace s21::math {

class IOperatorAnalyzer {
 public:
  [[nodiscard]] virtual int priority(const Token& token) const = 0;
  [[nodiscard]] virtual bool is_right_associative(const Token& token) const = 0;
  [[nodiscard]] virtual bool is_left_associative(const Token& token) const = 0;
  virtual ~IOperatorAnalyzer() = default;
};

class OperatorAnalyzer : public IOperatorAnalyzer {
 public:
  [[nodiscard]] int priority(const Token& token) const override;
  [[nodiscard]] bool is_right_associative(const Token& token) const override;
  [[nodiscard]] bool is_left_associative(const Token& token) const override;
};

}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_OPERATOR_ANALYZER_H_
