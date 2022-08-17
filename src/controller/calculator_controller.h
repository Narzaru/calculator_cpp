#ifndef SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
#define SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_

#include <string>

#include "../models/calculator/calculator.h"

namespace s21 {
class CalcultatorConstroller {
 public:
  explicit CalcultatorConstroller(calculator::Calculator *calc);
  ~CalcultatorConstroller();

  double evaluate(std::string string);

 private:
  calculator::Calculator *calculator_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
