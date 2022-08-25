#ifndef SRC_MODELS_CALCULATOR_LEXICAL_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_LEXICAL_ANALYZER_H_

#include <cstddef>
#include <iostream>
#include <list>
#include <vector>

#include "token.h"
#include "syntactical_analyzer.h"

namespace s21::math {

class ILexicalAnalyzer {
 public:
  virtual std::list<std::string> ParseString(std::string expression) = 0;
  virtual ~ILexicalAnalyzer() = default;
};

class LexicalAnalyzer : public ILexicalAnalyzer {
  using string = std::string;
  template<typename T>
  using list = std::list<T>;
  template<typename T>
  using vector = std::vector<T>;
  using size_type = std::size_t;

 public:
  // Parse a string expression into list of lexemes
  [[nodiscard]] list<string> ParseString(std::string expression) override;

 private:
  // A delimiter is a math operations and brackets
  static const std::array<std::string_view, 11> delimiters_;

  void ClearSpaces(string *string);
  bool IsDelimiter(const string &string, size_type position);
  size_type GetDelimiterLength(const string &string, size_type position);
  size_type GetSequenceLength(const string &string, size_type position);
};

}  // namespace s21::math
#endif  // SRC_MODELS_CALCULATOR_LEXICAL_ANALYZER_H_
