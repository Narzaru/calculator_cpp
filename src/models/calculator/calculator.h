#ifndef SRC_MODELS_CALCULATOR_CALCULATOR_H_
#define SRC_MODELS_CALCULATOR_CALCULATOR_H_

#include <list>
#include <string>

#include "lexical_analyzer.h"
#include "reverse_polish_notation_calc.h"
#include "reverse_polish_notation_former.h"
#include "syntactical_analyzer.h"
#include "token.h"

namespace s21 {

class Calculator {
 public:
  Calculator();
  ~Calculator();
  Calculator &push_expression(std::string expression);
  Calculator &compile_expression();
  [[nodiscard]] double calculate();
  [[nodiscard]] double calculate(const double *x);

  [[nodiscard]] double calculate(const std::string &expression);
  [[nodiscard]] double calculate(const std::string &expression, const double *x);

 private:
  math::ILexicalAnalyzer *lexical_analyzer;
  math::ISyntacticalAnalyzer *syntactical_analyzer;
  math::IReversePolishNotationFormer *rpn_former;
  math::IReversePolishNotationCalculator *rpn_calculator;
  std::string expression_;
  std::list<math::Token> rpn_tokens_;
};

}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_CALCULATOR_H_
