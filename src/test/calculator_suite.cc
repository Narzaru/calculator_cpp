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
  s21::math::LexemeAnalyzer lexeme_analyzer;
  s21::math::TokenCompiler token_compiler(lexeme_analyzer);
  s21::math::TokenAnalyzer token_analyzer;
  s21::math::ReversePolishNotation rpn(token_analyzer);

  std::list<std::string> list_of_lexemes =
      lexical_analyzer.ParseString("cos(sin(x))*(-tan(x))+4*3");
  std::list<s21::math::Token> infix_list_of_tokens =
      token_compiler.compile(list_of_lexemes);
  std::list<s21::math::Token> postfix_list_of_tokens =
      rpn.create(infix_list_of_tokens);

  TokenNameToString foo;
  std::size_t max_length = 0;
  for (const s21::math::Token &item : infix_list_of_tokens) {
    if (item.getLexeme().length() > max_length) {
      max_length = item.getLexeme().length();
    }
  }

  std::cout << "direct notation" << std::endl;
  for (auto &item : infix_list_of_tokens) {
    std::cout << std::setw(max_length + 1) << item.getLexeme();
    std::cout << " | ";
    std::cout << foo.print_name(item.getName()) << std::endl;
  }

  std::cout << "inderrect notation" << std::endl;
  auto lmda = [&token_analyzer](std::ostream &os, s21::math::Token &token){
    if (token_analyzer.priority(token) == 0) {
      os << "none";
    } else {
      os << token_analyzer.priority(token);
    }
    os << " |";
  };
  for (auto &item : postfix_list_of_tokens) {
    std::cout << "| ";
    std::cout << std::setw(max_length + 1) << item.getLexeme();
    std::cout << " | ";
    std::cout << std::setw(8) << foo.print_name(item.getName());
    std::cout << " | ";
    std::cout << std::setw(4);
    lmda(std::cout, item);
    std::cout << std::endl;
  }
}
