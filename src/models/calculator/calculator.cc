#include "calculator.h"

#include "calculator_base_exceptions.h"
#include "lexical_analyzer.h"
#include "reverse_polish_notation_calc.h"
#include "reverse_polish_notation_former.h"
#include "syntactical_analyzer.h"

namespace s21::calculator {

Calculator::Calculator() : lexical_analyzer(nullptr), syntactical_analyzer(
    nullptr), rpn_former(nullptr), rpn_calculator(nullptr) {
  try {
    lexical_analyzer = new math::LexicalAnalyzer;
  } catch (std::bad_alloc &e) {
    lexical_analyzer = nullptr;
  }
  try {
    syntactical_analyzer = new math::SyntacticalAnalyzer;
  } catch (std::bad_alloc &e) {
    delete lexical_analyzer;
    lexical_analyzer = nullptr;
    syntactical_analyzer = nullptr;
    throw std::bad_alloc();
  }
  try {
    rpn_former = new math::ReversePolishNotationFormer;
  } catch (std::bad_alloc &e) {
    delete lexical_analyzer;
    delete syntactical_analyzer;
    lexical_analyzer = nullptr;
    syntactical_analyzer = nullptr;
    rpn_former = nullptr;
    throw std::bad_alloc();
  }
  try {
    rpn_calculator = new math::ReversePolishNotationCalculator;
  } catch (std::bad_alloc &e) {
    delete lexical_analyzer;
    delete syntactical_analyzer;
    delete rpn_former;
    lexical_analyzer = nullptr;
    syntactical_analyzer = nullptr;
    rpn_former = nullptr;
    rpn_calculator = nullptr;
    throw std::bad_alloc();
  }
}

Calculator::~Calculator() {
  delete lexical_analyzer;
  delete syntactical_analyzer;
  delete rpn_former;
  delete rpn_calculator;
}

void Calculator::push_expression(const std::string &expression) {
  expression_ = expression;
}

void Calculator::compile_expression() {
  std::list<std::string> list_of_lexemes;
  list_of_lexemes = lexical_analyzer->ParseString(expression_);

  std::list<s21::math::MathToken> list_of_tokens;
  list_of_tokens = syntactical_analyzer->Compile(list_of_lexemes);

  list_of_tokens = rpn_former->Create(list_of_tokens);

  rpn_tokens_ = list_of_tokens;
}

double Calculator::calculate() { return this->calculate(nullptr); }

double Calculator::calculate(const double *x) {
  return rpn_calculator->Calculate(rpn_tokens_, x);
}

double Calculator::calculate(const std::string &expression) {
  return calculate(expression, nullptr);
}

double Calculator::calculate(const std::string &expression, const double *x) {
  std::list<std::string> list_of_lexemes;
  list_of_lexemes = lexical_analyzer->ParseString(expression);

  std::list<s21::math::MathToken> list_of_tokens;
  list_of_tokens = syntactical_analyzer->Compile(list_of_lexemes);

  list_of_tokens = rpn_former->Create(list_of_tokens);

  return rpn_calculator->Calculate(list_of_tokens, x);
}

}  // namespace s21::calculator
