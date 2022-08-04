#ifndef SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_

#include <string>
#include <utility>
#include <vector>

namespace s21 {
namespace math {

class ILexemeAnalyzer {
 public:
  virtual bool is_didgit(int code) const = 0;
  virtual bool is_number(const std::string &lexeme) const = 0;
  virtual bool is_open_bracket(const std::string &lexeme) const = 0;
  virtual bool is_function(const std::string &lexeme) const = 0;
  virtual bool is_operator(const std::string &lexeme) const = 0;
  virtual bool is_close_bracket(const std::string &lexeme) const = 0;
  virtual bool is_variable(const std::string &lexeme) const = 0;

  virtual ~ILexemeAnalyzer() = default;
};

class LexemeAnalyzer final : public ILexemeAnalyzer {
 public:
  LexemeAnalyzer() {}

  bool is_didgit(int code) const override;
  bool is_number(const std::string &lexeme) const override;
  bool is_open_bracket(const std::string &lexeme) const override;
  bool is_function(const std::string &lexeme) const override;
  bool is_operator(const std::string &lexeme) const override;
  bool is_close_bracket(const std::string &lexeme) const override;
  bool is_variable(const std::string &lexeme) const override;

 private:
  std::vector<std::string> functions = {"cos",  "sin",  "tan", "acos", "asin",
                                        "atan", "sqrt", "ln",  "log"};
  std::vector<std::string> operations = {"+", "-", "*", "/", "^", "mod", "%"};
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_
