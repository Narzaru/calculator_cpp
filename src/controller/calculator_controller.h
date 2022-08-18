#ifndef SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
#define SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_

#include <string>
#include "function.h"

#include "../models/calculator/calculator.h"

namespace s21 {
class CalculatorController {
 public:
  explicit CalculatorController(calculator::Calculator *calc);
  ~CalculatorController();

  double evaluate(const std::string &string);
  s21::UniformlyDiscreteFunction GetFunction(const std::string &expression,
                                             const std::string &x_min,
                                             const std::string &x_max,
                                             const std::string &y_min,
                                             const std::string &y_max,
                                             int dots_count);

 private:
  calculator::Calculator *calculator_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
