#ifndef SRC_CONTROLLER_FUNCTION_H_
#define SRC_CONTROLLER_FUNCTION_H_

#include "calculator.h"
#include <limits>
#include <vector>

namespace s21 {

class UDFunction final {
  using ICalculator = s21::calculator::ICalculator;
  using double_limits = std::numeric_limits<double>;

public:
  UDFunction();
  explicit UDFunction(int number_of_dots);
  UDFunction(int number_of_dots, double x_begin, double x_end);
  UDFunction(const UDFunction &other);
  ~UDFunction();

  UDFunction &operator=(const UDFunction &other);

  void SetDomain(double y_min, double y_max);

  [[nodiscard]] double &X(int i);
  [[nodiscard]] double &Y(int i);
  [[nodiscard]] const double &X(int i) const;
  [[nodiscard]] const double &Y(int i) const;

  [[nodiscard]] const int &Length() const;

  static bool IsNumber(const double &number);

private:
  int number_of_dots_;

  double *x_values_;
  double *y_values_;
};
} // namespace s21

#endif // SRC_CONTROLLER_FUNCTION_H_
