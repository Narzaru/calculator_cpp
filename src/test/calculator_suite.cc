#include <gtest/gtest.h>

#include <cstddef>
#include <iomanip>
#include <ios>
#include <list>
#include <ostream>

#include "../models/calculator/infix_math_compiler.h"

class TokenNameToString {
 public:
  const std::string &print_name(s21::math::TokenName n) {
    switch (n) {
      case s21::math::TokenName::kCloseBracket:
        return names[0];
      case s21::math::TokenName::kNumber:
        return names[1];
      case s21::math::TokenName::kOpenBracket:
        return names[2];
      case s21::math::TokenName::kFunction:
        return names[3];
      case s21::math::TokenName::kOperator:
        return names[4];
      case s21::math::TokenName::kVariable:
        return names[5];
      case s21::math::TokenName::kWrong:
        return names[6];
      case s21::math::TokenName::kUnary:
        return names[7];
      case s21::math::TokenName::kEmpty:
        return names[8];
      default:
        return names[9];
    }
  }

 private:
  std::vector<std::string> names = {
      "Close bracket", "Number", "Open bracket", "Function", "Operator",
      "Variable",      "Wrong",  "Unary",        "Empty",    "error"};
};

TEST(suite, test_1) {
  s21::math::LexicalAnalyzer lexical_analyzer;
  s21::math::SyntacticalAnalyzer syntatic_analyzer;
  s21::math::ReversePolishNotationFormer rpn;
  s21::math::ReversePolishNotationCalculator rpnc;

  std::list<std::string> list_of_lexemes;
  try {
    list_of_lexemes = lexical_analyzer.ParseString("2 ^ 2 ^ 3 + 1");
  } catch (const std::string &message) {
    std::cout << "0 " + message;
  }

  std::list<s21::math::Token> infix_list_of_tokens;
  try {
    infix_list_of_tokens = syntatic_analyzer.compile(list_of_lexemes);
  } catch (const std::string &message) {
    std::cout << "1 " + message;
  }
  std::list<s21::math::Token> postfix_list_of_tokens;
  try {
    postfix_list_of_tokens = rpn.create(infix_list_of_tokens);
  } catch (const std::string &message) {
    std::cout << "2 " + message;
  }

  double res = rpnc.calculate(postfix_list_of_tokens, nullptr);
  std::cout << std::endl << res << std::endl;
}

TEST(suite, test_2) {
  s21::Calculator calc;
  calc.push_expression("2 ^ 2 ^ 3 + 1");
  calc.compile_expression();
  std::cout << calc.calculate() << std::endl;
}

TEST(suite, test_3) {
  s21::Calculator calc;
  std::cout << calc.calculate("2 ^ 2 ^ 3 + 1") << std::endl;
}
