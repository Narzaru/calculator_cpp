#include "calculator_controller.h"

namespace s21 {
CalcultatorConstroller::CalcultatorConstroller(calculator::Calculator *calc)
    : calculator_(calc) {}

CalcultatorConstroller::~CalcultatorConstroller() {}

double CalcultatorConstroller::evaluate(std::string string) {
  return calculator_->calculate(string);
}

}  // namespace s21
