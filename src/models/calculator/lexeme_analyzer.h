#ifndef SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_

#include <string>
#include <utility>
#include <vector>

namespace s21 {
namespace math {

class ILexemeAnalyzer {
 public:
  virtual bool IsNumber(const std::string &lexeme) const = 0;
  virtual bool IsOpenBracket(const std::string &lexeme) const = 0;
  virtual bool IsFunction(const std::string &lexeme) const = 0;
  virtual bool IsOperator(const std::string &lexeme) const = 0;
  virtual bool IsCloseBracket(const std::string &lexeme) const = 0;
  virtual bool IsVariable(const std::string &lexeme) const = 0;

  virtual ~ILexemeAnalyzer() = default;
};

class LexemeAnalyzer : public ILexemeAnalyzer {
 public:
  LexemeAnalyzer() {}

  bool IsNumber(const std::string &lexeme) const override;
  bool IsOpenBracket(const std::string &lexeme) const override;
  bool IsFunction(const std::string &lexeme) const override;
  bool IsOperator(const std::string &lexeme) const override;
  bool IsCloseBracket(const std::string &lexeme) const override;
  bool IsVariable(const std::string &lexeme) const override;

 private:
  bool IsDidgit(int code) const;
  std::vector<std::string> functions = {"cos",  "sin",  "tan", "acos", "asin",
                                        "atan", "sqrt", "ln",  "log"};
  std::vector<std::string> operators = {"+", "-", "*", "/", "^", "mod", "%"};
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_
