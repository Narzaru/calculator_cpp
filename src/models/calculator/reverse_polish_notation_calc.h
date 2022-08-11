#ifndef SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_CALC_H_
#define SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_CALC_H_

#include <functional>
#include <list>
#include <stack>
#include <stdexcept>
#include <type_traits>

#include "calculator_base_exceptions.h"
#include "token.h"

namespace s21 {

class ReversePolishNotationCalcExceptions : public exception::IMyBaseException {
 public:
  explicit ReversePolishNotationCalcExceptions(const char *what) {
    who_ = "IReversePolishNotationCalculator";
    what_ = what;
  }

  [[nodiscard]] const char *who() const noexcept override { return who_; };
  [[nodiscard]] const char *what() const noexcept override { return what_; }

 private:
  const char *who_;
  const char *what_;
};

namespace math {

class IReversePolishNotationCalculator {
 public:
  [[nodiscard]] virtual double calculate(const std::list<Token> &postfix_tokens) const = 0;
  [[nodiscard]] virtual double calculate(const std::list<Token> &postfix_tokens,
                           const double *x) const = 0;
  virtual ~IReversePolishNotationCalculator() = default;
};

class ReversePolishNotationCalculator
    : public IReversePolishNotationCalculator {
 public:
  template <typename... args>
  using fptr = double (*)(args...);
  [[nodiscard]] double calculate(const std::list<Token> &postfix_tokens) const override;
  [[nodiscard]] double calculate(const std::list<Token> &postfix_tokens, const double *x) const override;

 private:
  [[nodiscard]] fptr<double> get_function(const Token &token) const;
  [[nodiscard]] fptr<double, double> get_operator(const Token &token) const;
  Token calc(std::stack<Token> *stack, Token token) const;
};

}  // namespace math
}  // namespace s21
#endif  // SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_CALC_H_
