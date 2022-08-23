#include "calculator_controller.h"

#include <limits>

namespace s21::controller {

CalculatorController::CalculatorController(calculator::Calculator *calc)
    : calculator_(calc) {}

CalculatorController::~CalculatorController() = default;

double CalculatorController::evaluate(const std::string &string,
                                      const std::string &x) {
  double num_x = 0.0;

  try {
    num_x = std::stod(x);
  } catch (...) {
    num_x = std::numeric_limits<double>::quiet_NaN();
  }

  try {
    return calculator_->calculate(string, &num_x);
  } catch (...) {
    return std::numeric_limits<double>::quiet_NaN();
  }
}

view::UDFunction
CalculatorController::GetFunction(const std::string &expression,
                                  const view::GraphProperties &properties,
                                  int dots_count) {
  view::UDFunction function(dots_count, properties.x_min(),
                            properties.x_max());

  try {
    calculator_->push_expression(expression);
    calculator_->compile_expression();
    for (int i = 0; i < dots_count; ++i) {
      function.Y(i) = calculator_->calculate(&function.X(i));
    }
    function.SetDomain(properties.y_min(), properties.y_max());

    return function;
  } catch (...) {
    return {};
  }
}

}  // namespace s21::controller
