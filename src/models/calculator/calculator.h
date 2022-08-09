#ifndef SRC_MODELS_CALCULATOR_CALCULATOR_H_
#define SRC_MODELS_CALCULATOR_CALCULATOR_H_

#include <list>
#include <string>

#include "lexical_analyzer.h"
#include "reverse_polish_notation_former.h"
#include "token.h"
#include "syntactical_analyzer.h"

namespace s21 {
namespace math {

class Calculator {
 public:
  Calculator &push_expression(std::string expression) noexcept;
  Calculator &compile_expression();
  [[nodiscard]] double calculate();
  [[nodiscard]] double calculate(const double &x);
  [[nodiscard]] bool is_success() const;

 private:
  ILexicalAnalyzer *analyzer;

  IReversePolishNotationFormer *rpn_former_;
  std::string expression_;
  std::list<Token> rpn_tokens_;
  bool is_have_any_error_;
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_CALCULATOR_H_
