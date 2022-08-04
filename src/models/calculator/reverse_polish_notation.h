#ifndef SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_
#define SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_

#include <list>

#include "token.h"
#include "lexeme_analyzer.h"
#include "token_compiler.h"

namespace s21 {
namespace math {

class IReversePolishNotation {
 public:
  virtual std::list<Token> create(std::list<Token> tokens) = 0;
  virtual ~IReversePolishNotation() = default;
};

class ReversePolishNotation final : public IReversePolishNotation {
 public:
  ReversePolishNotation(const ILexemeAnalyzer &analyzer);
  std::list<Token> create(std::list<Token> tokens) override;

 private:
  const ILexemeAnalyzer &analyzer_;
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_
