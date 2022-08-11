#ifndef SRC_MODELS_CALCULATOR_OPERATOR_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_OPERATOR_ANALYZER_H_

#include "token.h"

namespace s21::math {

class IOperatorAnalyzer {
 public:
  [[nodiscard]] virtual int Priority(const Token &token) const = 0;
  [[nodiscard]] virtual bool IsRightAssociative(const Token &token) const = 0;
  [[nodiscard]] virtual bool IsLeftAssociative(const Token &token) const = 0;
  virtual ~IOperatorAnalyzer() = default;
};

class OperatorAnalyzer : public IOperatorAnalyzer {
 public:
  [[nodiscard]] int Priority(const Token &token) const override;
  [[nodiscard]] bool IsRightAssociative(const Token &token) const override;
  [[nodiscard]] bool IsLeftAssociative(const Token &token) const override;
};

}  // namespace s21::math

#endif  // SRC_MODELS_CALCULATOR_OPERATOR_ANALYZER_H_
