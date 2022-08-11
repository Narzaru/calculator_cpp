#ifndef SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_FORMER_H_
#define SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_FORMER_H_

#include <list>

#include "calculator_base_exceptions.h"
#include "token.h"
#include "lexeme_analyzer.h"
#include "operator_analyzer.h"

namespace s21::math {

class IReversePolishNotationFormerException : s21::exception::IMyBaseException {
  public:
  explicit IReversePolishNotationFormerException(const char *what) {
    who_ = "IReversePolishNotationFormer";
    what_ = what;
  }

  [[nodiscard]] const char *who() const noexcept override {
    return who_;
  }

  [[nodiscard]] const char *what() const noexcept override {
    return what_;
  }

  private:
    const char *who_;
    const char *what_;
};

class IReversePolishNotationFormer {
 public:
  virtual std::list<Token> create(const std::list<Token> &tokens) = 0;
  virtual ~IReversePolishNotationFormer() = default;
};

class ReversePolishNotationFormer final : public IReversePolishNotationFormer, public OperatorAnalyzer {
 public:
  std::list<Token> create(const std::list<Token> &tokens) override;
 private:
  bool IsValidTokens(const std::list<Token> &tokens);
};

}  // namespace s21

#endif  // SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_FORMER_H_
