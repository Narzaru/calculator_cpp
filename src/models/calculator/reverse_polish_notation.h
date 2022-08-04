#ifndef SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_
#define SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_

#include <list>

#include "token.h"
#include "lexeme_analyzer.h"
#include "token_compiler.h"
#include "token_analyzer.h"

namespace s21 {
namespace math {

class IReversePolishNotation {
 public:
  virtual std::list<Token> create(std::list<Token> tokens) = 0;
  virtual ~IReversePolishNotation() = default;
};

class ReversePolishNotation : public IReversePolishNotation, public TokenAnalyzer {
 public:
  ReversePolishNotation(const ITokenAnalyzer &analyzer);
  std::list<Token> create(std::list<Token> tokens) override;

 private:
  const ITokenAnalyzer &analyzer_;
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_
