#include "function_properties.h"

namespace s21::view {

GraphProperties::GraphProperties()
    : x_min_(0), x_max_(0), y_min_(0), y_max_(0) {}

GraphProperties::GraphProperties(const std::string &x_min,
                                 const std::string &x_max,
                                 const std::string &y_min,
                                 const std::string &y_max) {
  x_min_ = std::stod(x_min);
  x_max_ = std::stod(x_max);
  y_min_ = std::stod(y_min);
  y_max_ = std::stod(y_max);
}

const double &GraphProperties::x_min() const { return x_min_; }

const double &GraphProperties::x_max() const { return x_max_; }

const double &GraphProperties::y_min() const { return y_min_; }

const double &GraphProperties::y_max() const { return y_max_; }

} // namespace s21::view