#ifndef SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_
#define SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_

#include <list>
#include <string>
#include <vector>

#include "token.h"
#include "lexeme_analyzer.h"

namespace s21 {
namespace math {

class ISyntacticalAnalyzer {
 public:
  virtual std::list<Token> compile(const std::list<std::string> &lexemes) = 0;
  virtual ~ISyntacticalAnalyzer() = default;
};


// !TODO(bgreydon) Add validation to the syntactical analyzer
class SyntacticalAnalyzer final : public ISyntacticalAnalyzer, public LexemeAnalyzer {
 public:
  [[nodiscard]] std::list<Token> compile(const std::list<std::string> &lexemes) override;

 private:
  [[nodiscard]] TokenName GetTokenName(const std::string &lexeme);
};

}  // namespace math
}  // namespace s21
#endif  // SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_