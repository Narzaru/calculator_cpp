
#include "reverse_polish_notation_calc.h"

#include <cmath>
#include <limits>
#include <stack>
#include <string>

#include "token.h"

namespace s21::math {
double ReversePolishNotationCalculator::Calculate(
    const std::list<MathToken> &postfix_tokens) const {
  return Calculate(postfix_tokens, nullptr);
}

double ReversePolishNotationCalculator::Calculate(
    const std::list<MathToken> &postfix_tokens, const double *x) const {
  std::stack<MathToken> stack;

  for (const auto &item : postfix_tokens) {
    if (item == Name::kNumber) {
      stack.emplace(item.GetName(), item.GetValue());
    } else if (item == Name::kVariable) {
      if (x != nullptr) {
        stack.emplace(Name::kNumber, std::to_string(*x));
      } else {
        throw ReversePolishNotationCalcExceptions("x is not set");
      }
    } else if (item.IsOperator() || item.IsFunction()) {
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
ReversePolishNotationCalculator::GetFunction(const MathToken &token) const {
  if (token == "cos") {
    return std::cos;
  } else if (token == "sin") {
    return std::sin;
  } else if (token == "tan") {
    return std::tan;
  } else if (token == "acos") {
    return std::acos;
  } else if (token == "asin") {
    return std::asin;
  } else if (token == "atan") {
    return std::atan;
  } else if (token == "sqrt") {
    return std::sqrt;
  } else if (token == "ln") {
    return std::log;
  } else if (token == "log") {
    return std::log10;
  } else if (token == "-") {
    return [](double l) { return -1.0 * l; };
  } else if (token == "abs") {
    return std::abs;
  } else if (token == "+") {
    return [](double l) { return l; };
  }
  throw ReversePolishNotationCalcExceptions(
      "math function not found or not implemented");
}

ReversePolishNotationCalculator::fptr<double, double>
ReversePolishNotationCalculator::GetOperator(const MathToken &token) const {
  if (token == "+") {
    return [](double l, double r) { return l + r; };
  } else if (token == "-") {
    return [](double l, double r) { return l - r; };
  } else if (token == "/") {
    return [](double l, double r) {
      if (std::fabs(r) < std::numeric_limits<float>::epsilon()) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      return l / r;
    };
  } else if (token == "*") {
    return [](double l, double r) { return l * r; };
  } else if (token == "^") {
    return [](double l, double r) { return std::pow(l, r); };
  } else if (token == "mod" || token == "%") {
    return [](double l, double r) { return std::fmod(l, r); };
  }
  throw ReversePolishNotationCalcExceptions(
      "math operator not found or not implemented");
}

MathToken ReversePolishNotationCalculator::Calc(std::stack<MathToken> *stack,
                                                const MathToken &token) const {
  double left_operand = std::numeric_limits<double>::quiet_NaN();
  double right_operand = std::numeric_limits<double>::quiet_NaN();

  if (stack->empty()) {
    throw ReversePolishNotationCalcExceptions(
        "not enough operands for an operation");
  }
  right_operand = std::stod(stack->top().GetValue());
  stack->pop();

  if (token == Name::kOperator) {
    if (stack->empty()) {
      throw ReversePolishNotationCalcExceptions(
          "not enough operands for an operation");
    }
    left_operand = std::stod(stack->top().GetValue());
    stack->pop();
  }

  if (token == Name::kInfixFunction || token == Name::kUnaryOperator) {
    return {Name::kNumber, std::to_string(GetFunction(token)(right_operand))};
  } else if (token == Name::kOperator) {
    return {Name::kNumber,
            std::to_string(GetOperator(token)(left_operand, right_operand))};
  } else {
    throw ReversePolishNotationCalcExceptions("token are not a operator");
  }
}

}  // namespace s21::math
