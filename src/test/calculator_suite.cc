#include <gtest/gtest.h>

#include <cstddef>
#include <iomanip>
#include <ios>
#include <list>
#include <ostream>

#include "../models/calculator/infix_math_compiler.h"

TEST(suite, test_1) {
  s21::math::LexicalAnalyzer lexical_analyzer;
  s21::math::SyntacticalAnalyzer syntatic_analyzer;
  s21::math::ReversePolishNotationFormer rpn;
  s21::math::ReversePolishNotationCalculator rpnc;

  std::list<std::string> list_of_lexemes;
    list_of_lexemes = lexical_analyzer.ParseString("2 ^ 2 ^ 3 + 1");

  std::list<s21::math::Token> infix_list_of_tokens;
    infix_list_of_tokens = syntatic_analyzer.compile(list_of_lexemes);
  std::list<s21::math::Token> postfix_list_of_tokens;
    postfix_list_of_tokens = rpn.create(infix_list_of_tokens);

  double res = rpnc.calculate(postfix_list_of_tokens, nullptr);
  std::cout << std::endl << res << std::endl;
}

TEST(suite, test_2) {
  s21::Calculator calc;
  calc.push_expression("sin(cas(3))");
  calc.compile_expression();
  std::cout << calc.calculate() << std::endl;
}

TEST(suite, test_3) {
  s21::Calculator calc;
  double x = 1;
  std::cout << calc.calculate("-cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x", &x) << std::endl;
}

TEST(suite, test_4) {
  s21::math::ILexicalAnalyzer *analyzer = new s21::math::LexicalAnalyzer;
  delete analyzer;
}
