#include "calculator_controller.h"

namespace s21 {
CalculatorController::CalculatorController(calculator::Calculator *calc)
    : calculator_(calc) {}

CalculatorController::~CalculatorController() = default;

double CalculatorController::evaluate(const std::string &string) {
  return calculator_->calculate(string);
}
s21::UniformlyDiscreteFunction CalculatorController::GetFunction(const std::string &expression,
                                                                 const std::string &sx_min,
                                                                 const std::string &sx_max,
                                                                 const std::string &sy_min,
                                                                 const std::string &sy_max,
                                                                 int dots_count) {
  double x_min = std::stod(sx_min);
  double x_max = std::stod(sx_max);
  double y_min = std::stod(sy_min);
  double y_max = std::stod(sy_max);
  s21::UniformlyDiscreteFunction ret_function(dots_count, x_min, x_max);
  ret_function.CalculateYValues(expression, calculator_);
  ret_function.SetDomain(y_min, y_max);
  return ret_function;
}



}  // namespace s21
