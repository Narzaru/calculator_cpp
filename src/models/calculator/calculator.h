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
  virtual void push_expression(std::string expression) = 0;
  virtual void compile_expression() = 0;
  [[nodiscard]] virtual double calculate() = 0;
  [[nodiscard]] virtual double calculate(const double *x) = 0;
  [[nodiscard]] virtual double calculate(const std::string &expression) = 0;
  [[nodiscard]] virtual double calculate(const std::string &expression, const double *x) = 0;
};

class Calculator : public ICalculator {
 public:
  Calculator();
  ~Calculator();
  void push_expression(std::string expression) override;
  void compile_expression() override;
  [[nodiscard]] double calculate() override;
  [[nodiscard]] double calculate(const double *x) override;

  [[nodiscard]] double calculate(const std::string &expression) override;
  [[nodiscard]] double calculate(const std::string &expression, const double *x) override;

 private:
  math::ILexicalAnalyzer *lexical_analyzer;
  math::ISyntacticalAnalyzer *syntactical_analyzer;
  math::IReversePolishNotationFormer *rpn_former;
  math::IReversePolishNotationCalculator *rpn_calculator;
  std::string expression_;
  std::list<math::Token> rpn_tokens_;
};

}  // namespace s21::calculator

#endif  // SRC_MODELS_CALCULATOR_CALCULATOR_H_
