#ifndef __CALCULATOR_CONTROLLER_H__
#define __CALCULATOR_CONTROLLER_H__

#include <string>
#include "../models/calculator/calculator.h"

namespace s21 {
class CalcultatorConstroller {
  public:
  CalcultatorConstroller(s21::calculator::Calculator &calc) : calculator_(calc){}
  ~CalcultatorConstroller() = default;

  double evaluate(std::string string) const {
    return calculator_.calculate(string);
  }

  private:
    s21::calculator::Calculator &calculator_;
};
}  // namespace s21

#endif // __CALCULATOR_CONTROLLER_H__
