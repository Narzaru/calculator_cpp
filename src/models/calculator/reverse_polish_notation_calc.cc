
#include "reverse_polish_notation_calc.h"

#include <cmath>
#include <functional>
#include <limits>
#include <math.h>
#include <stack>
#include <string>

#include "token.h"

namespace s21::math {
double ReversePolishNotationCalculator::Calculate(const std::list<Token> &postfix_tokens) const {
  return Calculate(postfix_tokens, nullptr);
}

double ReversePolishNotationCalculator::Calculate(
    const std::list<Token> &postfix_tokens, const double *x) const {
  std::stack<Token> stack;

  for (const auto &item : postfix_tokens) {
    if (item == TokenName::kNumber || item == TokenName::kVariable) {
      if (item == TokenName::kVariable) {
        if (x != nullptr) {
          stack.emplace(TokenName::kNumber, std::to_string(*x));
        } else {
          throw ReversePolishNotationCalcExceptions("x is not set");
        }
      } else {
        stack.emplace(item.GetName(), item.GetValue());
      }
    } else if (item == TokenName::kOperator || item == TokenName::kUnary ||
        item == TokenName::kFunction) {
      stack.push(Calc(&stack, item));
    } else {
      throw ReversePolishNotationCalcExceptions("unresolved token type");
    }
  }
  if (stack.empty()) {
    throw ReversePolishNotationCalcExceptions("expression has no solution");
  }
  return std::stod(stack.top().GetValue());
}

ReversePolishNotationCalculator::fptr<double>
ReversePolishNotationCalculator::GetFunction(const Token &token) const {
  if (token.GetValue() == "cos") {
    return std::cos;
  } else if (token.GetValue() == "sin") {
    return std::sin;
  } else if (token.GetValue() == "tan") {
    return std::tan;
  } else if (token.GetValue() == "acos") {
    return std::acos;
  } else if (token.GetValue() == "asin") {
    return std::asin;
  } else if (token.GetValue() == "atan") {
    return std::atan;
  } else if (token.GetValue() == "sqrt") {
    return std::sqrt;
  } else if (token.GetValue() == "ln") {
    return std::log;
  } else if (token.GetValue() == "log") {
    return std::log10;
  } else if (token.GetValue() == "-") {
    return [](double l) { return -1.0 * l; };
  } else if (token.GetValue() == "+") {
    return [](double l) { return l; };
  }
  throw ReversePolishNotationCalcExceptions("math function not found or not implemented");
}

ReversePolishNotationCalculator::fptr<double, double>
ReversePolishNotationCalculator::GetOperator(const Token &token) const {
  if (token.GetValue() == "+") {
    return [](double l, double r) { return l + r; };
  } else if (token.GetValue() == "-") {
    return [](double l, double r) { return l - r; };
  } else if (token.GetValue() == "/") {
    return [](double l, double r) {
      if (std::fabs(r) <= std::numeric_limits<float>::epsilon()) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      return l / r;
    };
  } else if (token.GetValue() == "*") {
    return [](double l, double r) { return l * r; };
  } else if (token.GetValue() == "^") {
    return [](double l, double r) { return std::pow(l, r); };
  } else if (token.GetValue() == "mod" || token.GetValue() == "%") {
    return [](double l, double r) { return std::fmod(l, r); };
  }
  throw ReversePolishNotationCalcExceptions("math operator not found or not implemented");
}

Token ReversePolishNotationCalculator::Calc(std::stack<Token> *stack, Token token) const {
  double left_operand = std::numeric_limits<double>::quiet_NaN();
  double right_operand = std::numeric_limits<double>::quiet_NaN();

  if (stack->empty()) {
    throw ReversePolishNotationCalcExceptions("not enought operands for an operation");
  }
  right_operand = std::stod(stack->top().GetValue());
  stack->pop();

  if (token == TokenName::kOperator) {
    if (stack->empty()) {
      throw ReversePolishNotationCalcExceptions("not enought operands for an operation");
    }
    left_operand = std::stod(stack->top().GetValue());
    stack->pop();
  }

  if (token == TokenName::kFunction || token == TokenName::kUnary) {
    return {TokenName::kNumber, std::to_string(GetFunction(token)(right_operand))};
  } else if (token == TokenName::kOperator) {
    return {TokenName::kNumber, std::to_string(GetOperator(token)(left_operand, right_operand))};
  } else {
    throw ReversePolishNotationCalcExceptions("token are not a operator");
  }
}

}  // namespace s21::math
