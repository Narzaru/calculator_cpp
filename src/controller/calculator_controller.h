#ifndef SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
#define SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_

#include "../models/calculator/calculator.h"
#include "../view/gtk/function_properties.h"
#include "function.h"

#include <string>

namespace s21 {
class CalculatorController {
public:
  explicit CalculatorController(calculator::Calculator *calc);
  ~CalculatorController();

  double evaluate(const std::string &string);
  double evaluate(const std::string &string, const std::string &x);

  s21::UDFunction GetFunction(const std::string &expression,
                              const view::GraphProperties &prop,
                              int dots_count);

private:
  calculator::Calculator *calculator_;
};
} // namespace s21

#endif // SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
