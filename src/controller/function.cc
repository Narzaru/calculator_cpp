#include "function.h"
#include <stdexcept>
#include <cmath>

namespace s21 {
UniformlyDiscreteFunction::UniformlyDiscreteFunction(int number_of_dots, double x_min, double x_max)
    : number_of_dots_(number_of_dots), x_values_(number_of_dots), y_values_(number_of_dots) {
  if (x_min >= x_max) {
    throw std::range_error("x_min >= x_max");
  }
  if (std::isnan(x_min) || std::isinf(x_max) || std::isinf(x_min) || std::isinf(x_max)) {
    throw std::invalid_argument("x is not a number");
  }

  double dx = (x_max - x_min) / (number_of_dots - 1);

  double x = x_min;
  for (auto &item : x_values_) {
    item = x;
    x += dx;
  }
}

void UniformlyDiscreteFunction::CalculateYValues(const std::string &expression,
                                                 s21::calculator::ICalculator *calc) {
  calc->push_expression(expression);
  calc->compile_expression();
  std::vector<double>::size_type x_count = x_values_.size();
  for (std::vector<double>::size_type i = 0; i < x_count; ++i) {
    y_values_[i] = calc->calculate(&x_values_[i]);
  }
}

void UniformlyDiscreteFunction::SetDomain(double y_min, double y_max) {
  for (auto &item : y_values_) {
    if (item < y_min || item > y_max) {
      item = std::numeric_limits<double>::quiet_NaN();
    }
  }
}

const double &UniformlyDiscreteFunction::x(int idx) {
  return x_values_.at(idx);
}

const double &UniformlyDiscreteFunction::y(int idx) {
  return y_values_.at(idx);
}
UniformlyDiscreteFunction::UniformlyDiscreteFunction() : number_of_dots_(0), x_values_(), y_values_() {}

const int &UniformlyDiscreteFunction::GetNumberOfDots() {
  return number_of_dots_;
}
}  // namespace s21