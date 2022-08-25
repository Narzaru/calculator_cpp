#include "calculator_controller.h"

#include <limits>

namespace s21::controller {

CalculatorController::CalculatorController(calculator::Calculator *calc, bank::CreditCalc *credit_calc)
    : calculator_(calc), credit_calculator_(credit_calc) {}

CalculatorController::~CalculatorController() = default;

double CalculatorController::evaluate(kstring string, kstring &x) {
  double num_x = 0.0;

  try {
    num_x = std::stod(x);
  } catch (...) {
    num_x = std::numeric_limits<double>::quiet_NaN();
  }

  try {
    return calculator_->Calculate(string, &num_x);
  } catch (...) {
    return std::numeric_limits<double>::quiet_NaN();
  }
}

view::UDFunction CalculatorController::GetFunction(kstring &expression, fprop &properties, int dots_count) {
  view::UDFunction function(dots_count, properties.x_min(), properties.x_max());

  try {
    calculator_->PushExpression(expression);
    calculator_->CompileExpression();
    for (int i = 0; i < dots_count; ++i) {
      function.Y(i) = calculator_->Calculate(&function.X(i));
    }
    function.SetDomain(properties.y_min(), properties.y_max());
    return function;
  } catch (...) {
    return {};
  }
}

view::CreditInfo CalculatorController::GetCreditInfo(kstring amount_str,
                                                     kstring term_str,
                                                     kstring interest_rate_str,
                                                     CreditInfo::CreditType type) {
  double amount = 0.;
  int term = 0;
  double interest_rate = 0.;

  try {
    amount = std::stod(amount_str);
    term = static_cast<int>(std::stod(term_str));
    interest_rate = std::stod(interest_rate_str);

    if (amount <= 0 || term <= 0 || interest_rate <= 0) {
      throw std::invalid_argument("negative value");
    }
  } catch (...) {
    return {};
  }

  view::CreditInfo info;
  credit_calculator_->Set(amount, term, interest_rate);

  std::vector<double> payments;

  if (type == view::CreditInfo::kAnnuity) {
    payments = credit_calculator_->AnnuityPayments();
  } else if (type == view::CreditInfo::kDifferentiated) {
    payments = credit_calculator_->DifferentiatedPayments();
  }

  for (const auto &item : payments) {
    info.out_info.monthly_payments.push_back(std::to_string(item));
  }

  double total = credit_calculator_->TotalPayments(payments);
  double overpayment = total - amount;

  info.out_info.total_payment = std::to_string(total);
  info.out_info.overpayment_on_credit = std::to_string(overpayment);

  return info;
}

}  // namespace s21::controller
