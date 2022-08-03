#include "calculator.h"

#include "reverse_polish_notation.h"

RPNCalculator::RPNCalculator(s21::ILexicalMathAnalyzer &concrete_analyzer,
                             s21::IReversePolishNotation &concrete_rpn_former)
    : analyzer(concrete_analyzer),
      rpn_former_(concrete_rpn_former),
      expression_(),
      is_have_any_error_(false) {}

RPNCalculator &RPNCalculator::push_expression(std::string expression) noexcept {
  expression_ = std::move(expression);
  return *this;
}

RPNCalculator &RPNCalculator::compile_expression() {
  std::list<std::string> lexemes = analyzer.ParseString(expression_);
  return *this;
}

bool RPNCalculator::is_success() const {
  return !is_have_any_error_;
}
