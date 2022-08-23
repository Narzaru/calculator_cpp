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
  [[nodiscard]] virtual double Calculate(const std::list<MathToken> &postfix_tokens) const = 0;
  [[nodiscard]] virtual double Calculate(const std::list<MathToken> &postfix_tokens,
                                         const double *x) const = 0;
  virtual ~IReversePolishNotationCalculator() = default;
};

class ReversePolishNotationCalculator
    : public IReversePolishNotationCalculator {
 public:
  template<typename... args>
  using fptr = double (*)(args...);
  [[nodiscard]] double Calculate(const std::list<MathToken> &postfix_tokens) const override;
  [[nodiscard]] double Calculate(const std::list<MathToken> &postfix_tokens,
                                 const double *x) const override;

 private:
  [[nodiscard]] fptr<double> GetFunction(const MathToken &token) const;
  [[nodiscard]] fptr<double, double> GetOperator(const MathToken &token) const;
  MathToken Calc(std::stack<MathToken> *stack, const MathToken &token) const;
};

}  // namespace math
}  // namespace s21
#endif  // SRC_MODELS_CALCULATOR_REVERSE_POLISH_NOTATION_CALC_H_
