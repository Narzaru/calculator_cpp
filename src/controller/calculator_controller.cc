#include "calculator_controller.h"

namespace s21 {
CalculatorController::CalculatorController(calculator::Calculator *calc)
    : calculator_(calc) {}

CalculatorController::~CalculatorController() = default;

double CalculatorController::evaluate(const std::string &string,
                                      const std::string &x) {
  try {
    double num_x = std::stod(x);
    return calculator_->calculate(string, &num_x);
  } catch (...) {
    return std::numeric_limits<double>::quiet_NaN();
  }
}

s21::UDFunction
CalculatorController::GetFunction(const std::string &expression,
                                  const view::GraphProperties &prop,
                                  int dots_count) {

  s21::UDFunction ret_function(dots_count, prop.x_min(), prop.x_max());

  try {
    calculator_->push_expression(expression);
    calculator_->compile_expression();
    for (int i = 0; i < dots_count; ++i) {
      ret_function.Y(i) = calculator_->calculate(&ret_function.X(i));
    }
    ret_function.SetDomain(prop.y_min(), prop.y_max());

    return ret_function;
  } catch (...) {
    return {};
  }
}

} // namespace s21
