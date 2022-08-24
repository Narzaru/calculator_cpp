#ifndef SRC_VIEW_GTK_CREDIT_WINDOW_H_
#define SRC_VIEW_GTK_CREDIT_WINDOW_H_

#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>

#include "controller/calculator_controller.h"

namespace s21::view {

class CreditWindow : public Gtk::Window {
 public:
  explicit CreditWindow(controller::CalculatorController *controller);

 private:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord {
   public:
    ModelColumns()  {
      add(month_id_);
      add(monthly_payment_);
    }

    Gtk::TreeModelColumn<unsigned int> month_id_;
    Gtk::TreeModelColumn<Glib::ustring> monthly_payment_;
  };

  int payment_id_;

  // user input
  Gtk::Entry amount_;
  Gtk::Entry term_;
  Gtk::Entry interest_rate_;
  Gtk::ComboBoxText payment_type_;

  // user output
  Gtk::Entry overpayment_;
  Gtk::Entry total_payment_;

  Glib::RefPtr<Gtk::ListStore> list_store_;
  ModelColumns columns_;
  Gtk::TreeView tree_view_;

  // other things
  controller::CalculatorController *controller_;

  void PushPayment(const Glib::ustring &string);
  void ClearPayments();
  void ClearEntries();
  bool CreditWindowKeyHandler(GdkEventKey *key);
  void Evaluate();
};

}  // s21::view

#endif //SRC_VIEW_GTK_CREDIT_WINDOW_H_
