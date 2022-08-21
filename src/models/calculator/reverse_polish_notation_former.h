#ifndef SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_FORMER_H_
#define SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_FORMER_H_

#include <list>

#include "calculator_base_exceptions.h"
#include "token.h"
#include "lexeme_analyzer.h"

namespace s21::math {

class ReversePolishNotationFormerException : public s21::exception::IMyBaseException {
 public:
  explicit ReversePolishNotationFormerException(const char *what) {
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
  virtual std::list<MathToken> Create(const std::list<MathToken> &tokens) = 0;
  virtual ~IReversePolishNotationFormer() = default;
};

class ReversePolishNotationFormer final : public IReversePolishNotationFormer {
 public:
  std::list<MathToken> Create(const std::list<MathToken> &tokens) override;
 private:
  bool IsValidTokens(const std::list<MathToken> &tokens);
};

}  // namespace s21::math

#endif  // SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_FORMER_H_
