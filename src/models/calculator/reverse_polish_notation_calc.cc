
#include "reverse_polish_notation_calc.h"
#include "token.h"
#include <stack>
#include <string>
#include <cmath>

namespace s21 {
namespace math {
double ReversePolishNotationCalculator::calculate(std::list<Token> &postfix_tokens) const {
  return calculate(postfix_tokens, nullptr);
}

double ReversePolishNotationCalculator::calculate(std::list<Token> &postfix_tokens, const double *x) const {
  std::stack<Token> stack;

  for (const auto &item : postfix_tokens) {
    if (item == TokenName::kNumber || item == TokenName::kVariable) {
      if (x != nullptr && item == TokenName::kVariable) {
        stack.emplace(TokenName::kNumber, std::to_string(*x));
      } else {
        stack.emplace(item.GetName(), item.GetValue());
      }
    } else if (item == TokenName::kOperator || item == TokenName::kUnary || item == TokenName::kFunction) {
      stack.push(calc(&stack, item));
    }
  }
  return std::stod(stack.top().GetValue());
}

ReversePolishNotationCalculator::fptr<double> ReversePolishNotationCalculator::get_function(const Token &token) const{
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
    return [](double l) {
      return -1.0 * l;
    };
  } else if (token.GetValue() == "+") {
    return [](double l) {
      return l;
    };
  }
  throw -1;
}

ReversePolishNotationCalculator::fptr<double, double> ReversePolishNotationCalculator::get_operator(const Token &token) const {
  if (token.GetValue() == "+") {
    return [](double l, double r) {
      return l + r;
    };
  } else if (token.GetValue() == "-") {
    return [](double l, double r) {
      return l - r;
    };
  } else if (token.GetValue() == "/") {
    return [](double l, double r) {
      return l / r;
    };
  } else if (token.GetValue() == "*") {
    return [](double l, double r) {
      return l / r;
    };
  } else if (token.GetValue() == "^") {
    return [](double l, double r) {
      return std::pow<double>(l, r);
    };
  } else if (token.GetValue() == "mod" || token.GetValue() == "%") {
    return [](double l, double r) {
      return std::fmod(l, r);
    };
  }
  throw -1;
}

Token ReversePolishNotationCalculator::calc(std::stack<Token> *stack, Token token) const {
  fptr<double> function;
  fptr<double, double> operation;

  double right_number = std::stod(stack->top().GetValue());
  stack->pop();

  if (token == TokenName::kFunction || token == TokenName::kUnary) {
    function = get_function(token);
    right_number = function(right_number);
    return Token(TokenName::kNumber, std::to_string(right_number));
  } else if (token == TokenName::kOperator) {
    if (stack->empty()) {
      throw -1;
    }
    double left_number = std::stod(stack->top().GetValue());
    stack->pop();
    operation = get_operator(token);
    right_number = operation(left_number, right_number);
    return Token(TokenName::kNumber, std::to_string(right_number));
  } else {
    throw -1;
  }
}

}  // namespace math
}  // namespace s21
