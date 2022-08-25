#ifndef SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
#define SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_

#include "models/calculator/calculator.h"
#include "models/bank/credit.h"

#include "view/gtk/function.h"
#include "view/gtk/function_properties.h"
#include "view/gtk/credit_info.h"

#include <string>

namespace s21::controller {

class CalculatorController {
  using kstring = const std::string &;
  using UDFunction = view::UDFunction;
  using fprop = const view::GraphProperties &;
  using CreditInfo = view::CreditInfo;
 public:
  explicit CalculatorController(calculator::Calculator *calc, bank::CreditCalc *credit_calc);
  ~CalculatorController();

  double Evaluate(kstring string, kstring x);

  UDFunction GetFunction(kstring expression, fprop properties, int dots_count);

  CreditInfo GetCreditInfo(kstring amount_str,
                           kstring term_str,
                           kstring interest_rate_str,
                           view::CreditInfo::CreditType type);

 private:
  calculator::Calculator *calculator_;
  bank::CreditCalc *credit_calculator_;
};

}  // namespace s21::controller

#endif  // SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
