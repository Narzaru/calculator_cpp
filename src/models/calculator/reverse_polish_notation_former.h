#ifndef SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_
#define SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_

#include <list>

#include "token.h"
#include "lexeme_analyzer.h"
#include "syntactical_analyzer.h"
#include "operator_analyzer.h"

namespace s21 {
namespace math {

class IReversePolishNotationFormer {
 public:
  virtual std::list<Token> create(std::list<Token> tokens) = 0;
  virtual ~IReversePolishNotationFormer() = default;
};

class ReversePolishNotationFormer final : public IReversePolishNotationFormer, public OperatorAnalyzer {
 public:
  std::list<Token> create(std::list<Token> tokens) override;
};

}  // namespace math
}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_H_
