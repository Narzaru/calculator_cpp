#ifndef SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_
#define SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_

#include <list>
#include <string>
#include <vector>

#include "token.h"
#include "lexeme_analyzer.h"

namespace s21 {
namespace math {


class ITokenCompiler {
 public:
  // virtual TokenName get_token_name(const std::string &lexeme) = 0;
  virtual std::list<Token> compile(const std::list<std::string> &lexemes) = 0;
  virtual ~ITokenCompiler() = default;
};

class TokenCompiler final : public ITokenCompiler {
 public:
  TokenCompiler(const ILexemeAnalyzer &token_analyzer);
  [[nodiscard]] std::list<Token> compile(const std::list<std::string> &lexemes) override;

 private:
  [[nodiscard]] TokenName get_token_name(const std::string &lexeme);
 private:
  const ILexemeAnalyzer &lexeme_analyzer_;
};

}  // namespace math
}  // namespace s21
#endif  // SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_
