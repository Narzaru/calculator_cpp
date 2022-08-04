#ifndef SRC_MODELS_CALCULATOR_LEXICAL_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_LEXICAL_ANALYZER_H_

#include <cstddef>
#include <iostream>
#include <list>
#include <vector>

#include "token.h"
#include "token_compiler.h"

namespace s21 {
namespace math {

class ILexicalAnalyzer {
 public:
  virtual std::list<std::string> ParseString(std::string expression) = 0;
};

class LexicalAnalyzer : public ILexicalAnalyzer {
  using string = std::string;
  template <typename T>
  using list = std::list<T>;
  template <typename T>
  using vector = std::vector<T>;
  using size_type = std::size_t;

 public:
  // Parse a string expression into list of lexemes
  [[nodiscard]] list<string> ParseString(std::string expression) override;

 private:
  // A delimiter is a math operations and brackets
  vector<string> delimiters{" ", "(", ")", "+",   "-",  "*",
                            "/", "^", "%", "mod", "pow"};

  void ClearSpaces(string *string);
  bool IsDelimiter(const string &string, size_type position);
  size_type GetDelimiterLength(const string &string, size_type position);
  size_type GetSequenceLength(const string &string, size_type position);
};

}  // namespace math
}  // namespace s21
#endif  // SRC_MODELS_CALCULATOR_LEXICAL_ANALYZER_H_
