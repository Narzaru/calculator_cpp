#include <stdexcept>
#include <cmath>

#include "function.h"

namespace s21 {

UDFunction::UDFunction()
    : number_of_dots_(0),
      x_values_(nullptr),
      y_values_(nullptr) {}

UDFunction::UDFunction(int number_of_dots)
    : number_of_dots_(number_of_dots),
      x_values_(new double[number_of_dots]),
      y_values_(new double[number_of_dots]) {
  if (number_of_dots <= 0) {
    delete[] x_values_;
    delete[] y_values_;
    number_of_dots = 0;
    x_values_ = nullptr;
    y_values_ = nullptr;
  }
}

UDFunction::UDFunction(int number_of_dots, double x_begin, double x_end)
    : UDFunction(number_of_dots) {
  if (x_begin >= x_end) {
    throw std::range_error("x_min >= x_max");
  }

  if (!is_number(x_begin) || !is_number(x_end)) {
    throw std::invalid_argument("x is not a number or a infinity");
  }

  double dx = (x_end - x_begin) / (number_of_dots - 1);

  double x = x_begin;
  for (int i = 0; i < number_of_dots; ++i) {
    x_values_[i] = x;
    x += dx;
  }
}

UDFunction::~UDFunction() {
  delete[] x_values_;
  delete[] y_values_;
}

UDFunction &UDFunction::operator=(const UDFunction &other) {
  if (&other == this) return *this;
  number_of_dots_ = other.number_of_dots_;
  delete[] x_values_;
  delete[] y_values_;

  x_values_ = new double[other.number_of_dots_];
  y_values_ = new double[other.number_of_dots_];

  for (int i = 0; i < other.number_of_dots_; ++i) {
    x_values_[i] = other.x_values_[i];
    y_values_[i] = other.y_values_[i];
  }
  return *this;
}

UDFunction::UDFunction(const UDFunction &other)
    : UDFunction(other.number_of_dots_) {
  for (int i = 0; i < other.number_of_dots_; ++i) {
    x_values_[i] = other.x_values_[i];
    y_values_[i] = other.y_values_[i];
  }
}

void UDFunction::CalculateYValues(const std::string &expression,
                                  ICalculator *calculator) {
  calculator->push_expression(expression);
  calculator->compile_expression();
  for (int i = 0; i < number_of_dots_; ++i) {
    y_values_[i] = calculator->calculate(&x_values_[i]);
  }
}

void UDFunction::SetDomain(double y_min, double y_max) {
  for (int i = 0; i < number_of_dots_; ++i) {
    if (y_values_[i] > y_max || y_values_[i] < y_min) {
      y_values_[i] = double_limits::quiet_NaN();
    }
  }
}
const double &UDFunction::X(int i) {
  return x_values_[i];
}
const double &UDFunction::Y(int i) {
  return y_values_[i];
}
const int &UDFunction::Length() const {
  return number_of_dots_;
}

bool UDFunction::is_number(const double &number) {
  return !std::isnan(number) && !std::isinf(number);
}

}  // namespace s21