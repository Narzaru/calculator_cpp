#include <cmath>
#include <numeric>

#include "credit.h"

namespace s21::bank {

CreditCalc::CreditCalc() : amount_(0.0), term_(0.0), interest_rate_(0.0) {}

CreditCalc &CreditCalc::Set(double amount, int term, double interest_rate) {
  amount_ = amount;
  term_ = term;
  interest_rate_ = interest_rate;
  return *this;
}

std::vector<double> CreditCalc::AnnuityPayments() const {
  // monthly interest rate
  double mir = interest_rate_ / 1200;

  double annuity_ratio_top = mir * std::pow(1 + mir, term_);
  double annuity_ratio_bot = std::pow(1 + mir, term_) - 1;
  double annuity_ratio = annuity_ratio_top / annuity_ratio_bot;

  double monthly_payment = amount_ * annuity_ratio;

  return std::vector<double>(term_, monthly_payment);
}

std::vector<double> CreditCalc::DifferentiatedPayments() const {
  Payments payments;

  double yearly_interest_rate = interest_rate_ / 100.0;
  double monthly_basic_payment = amount_ / term_;

  for (int i = 0; i < term_; ++i) {
    double loan_interest = (amount_ - monthly_basic_payment * i) * yearly_interest_rate;
    payments.push_back(monthly_basic_payment + loan_interest * (30.4166666 / 365.0));
  }

  return payments;
}

double CreditCalc::TotalPayments(const Payments &all) {
  return std::accumulate(all.begin(), all.end(), 0.0);
}

}  // namespace s21::bank
