#ifndef SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_

#include <string>
#include <string_view>
#include <utility>
#include <array>

namespace s21::math {

class ILexemeAnalyzer {
 public:
  [[nodiscard]] virtual bool IsNumber(const std::string &lexeme) const = 0;
  [[nodiscard]] virtual bool IsOpenBracket(const std::string &lexeme) const = 0;
  [[nodiscard]] virtual bool IsFunction(const std::string &lexeme) const = 0;
  [[nodiscard]] virtual bool IsOperator(const std::string &lexeme) const = 0;
  [[nodiscard]] virtual bool IsCloseBracket(const std::string &lexeme) const = 0;
  [[nodiscard]] virtual bool IsVariable(const std::string &lexeme) const = 0;

  virtual ~ILexemeAnalyzer() = default;
};

class LexemeAnalyzer : public ILexemeAnalyzer {
 public:
  [[nodiscard]] bool IsNumber(const std::string &lexeme) const override;
  [[nodiscard]] bool IsOpenBracket(const std::string &lexeme) const override;
  [[nodiscard]] bool IsFunction(const std::string &lexeme) const override;
  [[nodiscard]] bool IsOperator(const std::string &lexeme) const override;
  [[nodiscard]] bool IsCloseBracket(const std::string &lexeme) const override;
  [[nodiscard]] bool IsVariable(const std::string &lexeme) const override;

 private:
  [[nodiscard]] bool IsDigit(int code) const;

  static const std::array<std::string_view, 10> functions;
  static const std::array<std::string_view, 10> operators;
};

}  // namespace s21::math

#endif  // SRC_MODELS_CALCULATOR_LEXEME_ANALYZER_H_
