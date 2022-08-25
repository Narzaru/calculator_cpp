#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>

#include <iostream>
#include <gtkmm/cellrendererprogress.h>

#include "credit_window.h"

namespace s21::view {

CreditWindow::CreditWindow(controller::CalculatorController *controller)
    : payment_id_(1) {
  controller_ = controller;

  // Entry's setup
  amount_.set_placeholder_text("credit amount");
  term_.set_placeholder_text("term, month");
  interest_rate_.set_placeholder_text("interest rate, %");

  payment_type_.append("annuity (approximate)");
  payment_type_.append("differentiated (approximate)");
  payment_type_.set_active(0);

  // Left box
  //// User input
  auto *user_box = new Gtk::Box;
  user_box->set_orientation(Gtk::ORIENTATION_VERTICAL);
  user_box->set_spacing(5);
  user_box->add(payment_type_);
  user_box->add(amount_);
  user_box->add(term_);
  user_box->add(interest_rate_);

  //// Overpayment and total payment output
  auto *overpayment_label = new Gtk::Label;
  overpayment_label->set_text("overpayment on credit");
  auto *total_payment_label = new Gtk::Label;
  total_payment_label->set_text("total payment");
  overpayment_.set_editable(false);
  total_payment_.set_editable(false);
  user_box->add(*overpayment_label);
  user_box->add(overpayment_);
  user_box->add(*total_payment_label);
  user_box->add(total_payment_);

  // Output box
  //// list of payments
  list_store_ = Gtk::ListStore::create(columns_);
  tree_view_.set_model(list_store_);
  tree_view_.append_column("Month", columns_.month_id_);
  tree_view_.append_column("Monthly payment", columns_.monthly_payment_);
  tree_view_.property_expand() = true;

  auto *scrolled_window = new Gtk::ScrolledWindow;
  scrolled_window->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
  scrolled_window->property_expand() = Gtk::EXPAND;
  scrolled_window->add(tree_view_);


  // Main window box
  auto *window_box = new Gtk::Box;
  window_box->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  window_box->add(*user_box);
  window_box->add(*scrolled_window);

  // Window setup
  add(*window_box);
  set_resizable(false);

  // Bind signals
  signal_key_press_event()
      .connect(sigc::mem_fun(*this, &CreditWindow::CreditWindowKeyHandler),
               false);

  // Show window
  show_all_children();
}

bool CreditWindow::CreditWindowKeyHandler(GdkEventKey *key) {
  if (key->keyval == GDK_KEY_Return) {
    Evaluate();
    return true;
  } else if (key->keyval == GDK_KEY_Escape) {
    ClearEntries();
    ClearPayments();
  }
  return false;
}

void CreditWindow::PushPayment(const Glib::ustring &string) {
  auto row = *(list_store_->append());
  row[columns_.month_id_] = payment_id_;
  row[columns_.monthly_payment_] = string;

  ++payment_id_;
}

void CreditWindow::ClearPayments() {
  list_store_->clear();
  payment_id_ = 1;
}

void CreditWindow::ClearEntries() {
  overpayment_.set_text("");
  total_payment_.set_text("");
}

void CreditWindow::Evaluate() {
  ClearPayments();
  const auto &amount = amount_.get_text();
  const auto &term = term_.get_text();
  const auto &interest_rate = interest_rate_.get_text();

  CreditInfo::CreditType type;
  if (payment_type_.get_active_row_number() == 0) {
    type = CreditInfo::CreditType::kAnnuity;
  } else if (payment_type_.get_active_row_number() == 1) {
    type = CreditInfo::CreditType::kDifferentiated;
  }

  CreditInfo info = controller_->GetCreditInfo(amount, term, interest_rate, type);

  if (info.out_info.overpayment_on_credit.empty()) {
    total_payment_.set_text("error");
    overpayment_.set_text("error");
  } else {
    for (const auto &item : info.out_info.monthly_payments) {
      PushPayment(item);
    }

    total_payment_.set_text(info.out_info.total_payment);
    overpayment_.set_text(info.out_info.overpayment_on_credit);
  }
}

}  // namespace s21::view
