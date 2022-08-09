#ifndef __REVERSE_POLISH_NOTATION_CALC_H__
#define __REVERSE_POLISH_NOTATION_CALC_H__

#include <functional>
#include <list>
#include <stack>
#include <type_traits>
#include "token.h"

namespace s21 {
namespace math {

class IReversePolishNotationCalculator {
 public:
  virtual double calculate(std::list<Token> &postfix_tokens) const = 0;
  virtual double calculate(std::list<Token> &postfix_tokens, const double *x) const = 0;
  virtual ~IReversePolishNotationCalculator() = default;
};

class ReversePolishNotationCalculator : public IReversePolishNotationCalculator {
 public:
  template<typename ...args>
  using fptr = double (*)(args...);
  double calculate(std::list<Token> &postfix_tokens) const override;
  double calculate(std::list<Token> &postfix_tokens, const double *x) const override;

 private:
  fptr<double> get_function(const Token &token) const;
  fptr<double, double> get_operator(const Token &token) const;
  static double operator_plus(double l, double r);
  static double operator_minus(double l, double r);
  Token calc(std::stack<Token> *stack, Token token) const;
};


}  // namespace math
}  // namespace s21
#endif // __REVERSE_POLISH_NOTATION_CALC_H__
