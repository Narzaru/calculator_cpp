#ifndef SRC_VIEW_GTK_CREDIT_INFO_H_
#define SRC_VIEW_GTK_CREDIT_INFO_H_

#include <string>

namespace s21::view {

struct Payments {
  std::list<std::string> monthly_payments;
  std::string overpayment_on_credit;
  std::string total_payment;
};

struct CreditInfo {
  enum CreditType {
    kAnnuity = 0,
    kDifferentiated = 1
  };

  Payments out_info;
};

}  // namespace s21::view
#endif  // SRC_VIEW_GTK_CREDIT_INFO_H_
