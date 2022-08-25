#ifndef SRC_MODELS_CALCULATOR_CALCULATOR_H_
#define SRC_MODELS_CALCULATOR_CALCULATOR_H_

#include <list>
#include <string>

#include "lexical_analyzer.h"
#include "reverse_polish_notation_calc.h"
#include "reverse_polish_notation_former.h"
#include "syntactical_analyzer.h"
#include "token.h"

namespace s21::calculator {

class ICalculator {
 public:
  virtual void PushExpression(const std::string &expression) = 0;
  virtual void CompileExpression() = 0;
  [[nodiscard]] virtual double Calculate() = 0;
  [[nodiscard]] virtual double Calculate(const double *x) = 0;
  [[nodiscard]] virtual double Calculate(const std::string &expression) = 0;
  [[nodiscard]] virtual double Calculate(const std::string &expression,
                                         const double *x) = 0;
  virtual ~ICalculator() = default;
};

class Calculator : public ICalculator {
 public:
  Calculator();
  ~Calculator() override;

  void PushExpression(const std::string &expression) override;
  void CompileExpression() override;

  [[nodiscard]] double Calculate() override;
  [[nodiscard]] double Calculate(const double *x) override;

  [[nodiscard]] double Calculate(const std::string &expression) override;
  [[nodiscard]] double Calculate(const std::string &expression,
                                 const double *x) override;

 private:
  math::ILexicalAnalyzer *lexical_analyzer_;
  math::ISyntacticalAnalyzer *syntactical_analyzer_;
  math::IReversePolishNotationFormer *rpn_former_;
  math::IReversePolishNotationCalculator *rpn_calculator_;
  std::string expression_;
  std::list<math::MathToken> rpn_tokens_;
};

}  // namespace s21::calculator

#endif  // SRC_MODELS_CALCULATOR_CALCULATOR_H_
