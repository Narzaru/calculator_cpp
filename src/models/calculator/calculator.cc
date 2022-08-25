#include "calculator.h"

#include "calculator_base_exceptions.h"
#include "lexical_analyzer.h"
#include "reverse_polish_notation_calc.h"
#include "reverse_polish_notation_former.h"
#include "syntactical_analyzer.h"

namespace s21::calculator {

Calculator::Calculator() : lexical_analyzer_(nullptr), syntactical_analyzer_(
    nullptr), rpn_former_(nullptr), rpn_calculator_(nullptr) {
  try {
    lexical_analyzer_ = new math::LexicalAnalyzer;
  } catch (std::bad_alloc &e) {
    lexical_analyzer_ = nullptr;
  }
  try {
    syntactical_analyzer_ = new math::SyntacticalAnalyzer;
  } catch (std::bad_alloc &e) {
    delete lexical_analyzer_;
    lexical_analyzer_ = nullptr;
    syntactical_analyzer_ = nullptr;
    throw std::bad_alloc();
  }
  try {
    rpn_former_ = new math::ReversePolishNotationFormer;
  } catch (std::bad_alloc &e) {
    delete lexical_analyzer_;
    delete syntactical_analyzer_;
    lexical_analyzer_ = nullptr;
    syntactical_analyzer_ = nullptr;
    rpn_former_ = nullptr;
    throw std::bad_alloc();
  }
  try {
    rpn_calculator_ = new math::ReversePolishNotationCalculator;
  } catch (std::bad_alloc &e) {
    delete lexical_analyzer_;
    delete syntactical_analyzer_;
    delete rpn_former_;
    lexical_analyzer_ = nullptr;
    syntactical_analyzer_ = nullptr;
    rpn_former_ = nullptr;
    rpn_calculator_ = nullptr;
    throw std::bad_alloc();
  }
}

Calculator::~Calculator() {
  delete lexical_analyzer_;
  delete syntactical_analyzer_;
  delete rpn_former_;
  delete rpn_calculator_;
}

void Calculator::PushExpression(const std::string &expression) {
  expression_ = expression;
}

void Calculator::CompileExpression() {
  std::list<std::string> list_of_lexemes;
  list_of_lexemes = lexical_analyzer_->ParseString(expression_);

  std::list<s21::math::MathToken> list_of_tokens;
  list_of_tokens = syntactical_analyzer_->Compile(list_of_lexemes);

  list_of_tokens = rpn_former_->Create(list_of_tokens);

  rpn_tokens_ = list_of_tokens;
}

double Calculator::Calculate() { return this->Calculate(nullptr); }

double Calculator::Calculate(const double *x) {
  return rpn_calculator_->Calculate(rpn_tokens_, x);
}

double Calculator::Calculate(const std::string &expression) {
  return Calculate(expression, nullptr);
}

double Calculator::Calculate(const std::string &expression, const double *x) {
  std::list<std::string> list_of_lexemes;
  list_of_lexemes = lexical_analyzer_->ParseString(expression);

  std::list<s21::math::MathToken> list_of_tokens;
  list_of_tokens = syntactical_analyzer_->Compile(list_of_lexemes);

  list_of_tokens = rpn_former_->Create(list_of_tokens);

  return rpn_calculator_->Calculate(list_of_tokens, x);
}

}  // namespace s21::calculator
