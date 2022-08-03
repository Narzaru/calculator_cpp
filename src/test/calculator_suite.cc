#include <gtest/gtest.h>

#include <iomanip>
#include <ios>
#include <list>

#include "../models/calculator/calculator.h"
#include "../models/calculator/lexical_analyzer.h"

class foo {
 public:
  const std::string &print_name(TokenName n) {
    switch (n) {
      case TokenName::kCloseBracket:
        return names[0];
      case TokenName::kNumber:
        return names[1];
      case TokenName::kOpenBracket:
        return names[2];
      case TokenName::kFunction:
        return names[3];
      case TokenName::kOperator:
        return names[4];
      case TokenName::kVariable:
        return names[5];
      case TokenName::kWrong:
        return names[6];
      case TokenName::kUnary:
        return names[7];
      case TokenName::kEmpty:
        return names[8];
        break;
    }
  }

 private:
  std::vector<std::string> names = {"Close bracket", "Number",   "Open bracket",
                                    "Function",      "Operator", "Variable",
                                    "Wrong",         "Unary",    "Empty"};
};

TEST(suite, test_1) {
  foo helper;
  s21::TokenAnalyzer token_analyzer;
  MathTokenCompiler token_compiler(token_analyzer);
  s21::LexicalMathAnalyzer analyzer;
  std::list<std::string> tokens = analyzer.ParseString("asd asd 3.4 +    4.e+0");
  for (auto item : tokens) {
    std::cout << item << std::endl;
    // std::cout << std::setw(10) << std::left << item.GetLexeme();
    // std::cout << " | ";
    // std::cout << helper.print_name(item.GetName());
    // std::cout << std::endl;
  }
}
