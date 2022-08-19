#ifndef SRC_CONTROLLER_FUNCTION_H_
#define SRC_CONTROLLER_FUNCTION_H_

#include <vector>
#include "calculator.h"
#include <limits>

namespace s21 {

class UDFunction {
  using ICalculator = s21::calculator::ICalculator;
  using double_limits = std::numeric_limits<double>;

 public:
  UDFunction();
  explicit UDFunction(int number_of_dots);
  UDFunction(int number_of_dots, double x_begin, double x_end);
  UDFunction(const UDFunction &other);
  ~UDFunction();

  UDFunction &operator=(const UDFunction &other);

  void CalculateYValues(const std::string &expression, ICalculator *calculator);
  void SetDomain(double y_min, double y_max);

  [[nodiscard]] const double &X(int i);
  [[nodiscard]] const double &Y(int i);
  [[nodiscard]] const int &Length() const;

 private:
  int number_of_dots_;
  double *x_values_;
  double *y_values_;

 protected:
  static bool is_number(const double &number);
};
}  // namespace s21

#endif //SRC_CONTROLLER_FUNCTION_H_
