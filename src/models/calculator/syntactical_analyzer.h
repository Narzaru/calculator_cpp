#ifndef SRC_MODELS_CALCULATOR_SYNTACTICAL_ANALYZER_H_
#define SRC_MODELS_CALCULATOR_SYNTACTICAL_ANALYZER_H_

#include <list>
#include <string>
#include <vector>

#include "token.h"
#include "lexeme_analyzer.h"

namespace s21::math {

class ISyntacticalAnalyzer {
 public:
  virtual std::list<MathToken> Compile(const std::list<std::string> &lexemes) = 0;
  virtual ~ISyntacticalAnalyzer() = default;
};

class SyntacticalAnalyzer final : public ISyntacticalAnalyzer, public LexemeAnalyzer {
 public:
  [[nodiscard]] std::list<MathToken> Compile(const std::list<std::string> &lexemes) override;

 private:
  [[nodiscard]] Name GetTokenName(const std::string &lexeme);
};

}  // namespace s21::math

#endif  // SRC_MODELS_CALCULATOR_SYNTACTICAL_ANALYZER_H_
