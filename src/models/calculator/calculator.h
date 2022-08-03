#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include <list>
#include <string>

#include "lexical_analyzer.h"
#include "reverse_polish_notation.h"
#include "token.h"
#include "token_compiler.h"

class RPNCalculator {
 public:
  RPNCalculator(s21::ILexicalMathAnalyzer &analyzer,
                s21::IReversePolishNotation &concrete_rpn_former);
  RPNCalculator &push_expression(std::string expression) noexcept;
  RPNCalculator &compile_expression();
  [[nodiscard]] double calculate();
  [[nodiscard]] double calculate(const double &x);
  [[nodiscard]] bool is_success() const;

 private:
  s21::ILexicalMathAnalyzer &analyzer;
  s21::IReversePolishNotation &rpn_former_;
  std::string expression_;
  std::list<Token> rpn_tokens_;
  bool is_have_any_error_;
};

#endif  // __CALCULATOR_H__
