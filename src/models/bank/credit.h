#ifndef SRC_MODELS_BANK_CREDIT_H_
#define SRC_MODELS_BANK_CREDIT_H_

#include <vector>

namespace s21::bank {

class CreditCalc {
  using Payments = std::vector<double>;
 public:
  CreditCalc();

  CreditCalc &Set(double amount, int term, double interest_rate);
  [[nodiscard]] Payments AnnuityPayments() const;
  [[nodiscard]] Payments DifferentiatedPayments() const;
  [[nodiscard]] static double TotalPayments(const Payments &all);

 private:
  double amount_;
  int term_;
  double interest_rate_;
};

}  // namespace s21::bank

#endif  // SRC_MODELS_BANK_CREDIT_H_
