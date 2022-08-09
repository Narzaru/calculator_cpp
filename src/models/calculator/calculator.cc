#include "calculator.h"

#include "reverse_polish_notation_former.h"

namespace s21 {
namespace math {

Calculator &Calculator::push_expression(std::string expression) noexcept {
  expression_ = std::move(expression);
  return *this;
}

Calculator &Calculator::compile_expression() {
  std::list<std::string> lexemes = analyzer->ParseString(expression_);
  return *this;
}

bool Calculator::is_success() const {
  return !is_have_any_error_;
}

}  // namespace math
}  // namespace s21
