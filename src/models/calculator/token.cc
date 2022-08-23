#include "token.h"

#include <utility>

namespace s21::math {

bool MathToken::operator==(const MathToken &other) const {
  return other.name_ == name_ && other.value_ == value_;
}

bool MathToken::operator==(const Name &name) const { return name_ == name; }

bool MathToken::operator!=(const Name &name) const { return !(*this == name); }

bool MathToken::operator==(const std::string &value) const {
  return value_ == value;
}

bool MathToken::operator!=(const std::string &value) const {
  return !(*this == value);
}

bool MathToken::IsNumber() const {
  return name_ == Name::kVariable || name_ == Name::kNumber;
}

bool MathToken::IsOperator() const {
  return name_ == Name::kOperator || name_ == Name::kUnaryOperator;
}

bool MathToken::IsOpenBracket() const { return name_ == Name::kOpenBracket; }

bool MathToken::IsCloseBracket() const { return name_ == Name::kCloseBracket; }

bool MathToken::IsFunction() const { return name_ == Name::kInfixFunction; }

bool MathToken::IsRightAssociative() const {
  return name_ == Name::kUnaryOperator || value_ == "pow" || value_ == "^";
}

bool MathToken::IsLeftAssociative() const { return !IsRightAssociative(); }

int MathToken::Priority() const {
  int priority = 0;

  if (name_ != Name::kUnaryOperator && (value_ == "+" || value_ == "-")) {
    priority = 1;
  } else if (value_ == "*" || value_ == "/") {
    priority = 2;
  } else if (value_ == "mod" || value_ == "%") {
    priority = 2;
  } else if (value_ == "^" || value_ == "pow"
      || name_ == Name::kUnaryOperator) {
    priority = 3;
  } else if (name_ == Name::kInfixFunction) {
    priority = -1;
  } else {
    priority = -1;
  }
  return priority;
}

bool MathToken::IsWrong() const {
  return name_ == Name::kUnknown || name_ == Name::kEmpty;
}

}  // namespace s21::math
