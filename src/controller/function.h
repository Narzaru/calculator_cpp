#ifndef SRC_CONTROLLER_FUNCTION_H_
#define SRC_CONTROLLER_FUNCTION_H_

#include <vector>
#include "../models/calculator/calculator.h"

namespace s21 {
class UniformlyDiscreteFunction {
 public:
  UniformlyDiscreteFunction();
  UniformlyDiscreteFunction(int number_of_dots, double x_min, double x_max);
  void CalculateYValues(const std::string &expression, s21::calculator::ICalculator *calc);
  void SetDomain(double y_min, double y_max);
  const double &x(int idx);
  const double &y(int idx);
  const int &GetNumberOfDots();

 private:
  int number_of_dots_;
  std::vector<double> x_values_;
  std::vector<double> y_values_;
};
}  // namespace s21

#endif //SRC_CONTROLLER_FUNCTION_H_
