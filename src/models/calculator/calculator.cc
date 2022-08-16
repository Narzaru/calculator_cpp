#include "calculator.h"

#include "calculator_base_exceptions.h"
#include "lexical_analyzer.h"
#include "reverse_polish_notation_calc.h"
#include "reverse_polish_notation_former.h"
#include "syntactical_analyzer.h"

namespace s21 {
namespace calculator {
Calculator::Calculator() {
  lexical_analyzer = new math::LexicalAnalyzer;
  syntactical_analyzer = new math::SyntacticalAnalyzer;
  rpn_former = new math::ReversePolishNotationFormer;
  rpn_calculator = new math::ReversePolishNotationCalculator;
}

Calculator::~Calculator() {
  delete lexical_analyzer;
  delete syntactical_analyzer;
  delete rpn_former;
  delete rpn_calculator;
}

Calculator &Calculator::push_expression(std::string expression) {
  expression_ = std::move(expression);
  return *this;
}

Calculator &Calculator::compile_expression() {
  std::list<std::string> list_of_lexemes;
  list_of_lexemes = lexical_analyzer->ParseString(expression_);

  std::list<s21::math::Token> list_of_tokens;
  list_of_tokens = syntactical_analyzer->Compile(list_of_lexemes);

  list_of_tokens = rpn_former->Create(list_of_tokens);

  rpn_tokens_ = list_of_tokens;

  return *this;
}

double Calculator::calculate() {
  return this->calculate(nullptr);
}

double Calculator::calculate(const double *x) {
  return rpn_calculator->Calculate(rpn_tokens_, x);
}

double Calculator::calculate(const std::string &expression) {
  return calculate(expression, nullptr);
}

double Calculator::calculate(const std::string &expression, const double *x) {
  std::list<std::string> list_of_lexemes;
  list_of_lexemes = lexical_analyzer->ParseString(expression);

  std::list<s21::math::Token> list_of_tokens;
  list_of_tokens = syntactical_analyzer->Compile(list_of_lexemes);

  list_of_tokens = rpn_former->Create(list_of_tokens);

  return rpn_calculator->Calculate(list_of_tokens, x);
}
}  // namespace calculator
}  // namespace s21
