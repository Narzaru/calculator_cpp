#ifndef SRC_VIEW_GTK_MAIN_WINDOW_H_
#define SRC_VIEW_GTK_MAIN_WINDOW_H_

#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/window.h>

#include "controller/calculator_controller.h"
#include "plotter_window.h"
#include "sigc++/functors/mem_fun.h"

namespace s21::view {
class MainWindow : public Gtk::Window {
 public:
  static MainWindow *GetInstance();

  MainWindow(GtkWindow *c_object, const Glib::RefPtr<Gtk::Builder> &builder);
  ~MainWindow() override;

  void BindCalculatorController(controller::CalculatorController *controller);

 private:
  const Glib::RefPtr<Gtk::Builder> &builder_;
  Gtk::Entry *entry_;
  Gtk::Entry *entry_x_;
  controller::CalculatorController *controller_;

  void bind_buttons();
  void SwitchToPlotter();
  void SwitchToCredit();

  void bind_button_to_show_plotter(const char *glade_id);
  void bind_button_to_show_credit(const char *glade_id);
  void bind_button_to_add_text_entry(const char *glade_id, const char *text);
  void bind_button_to_clear_entry(const char *glade_id);
  void bind_button_to_del_char_entry(const char *glade_id);
  void bind_button_to_evaluate(const char *glade_id);

  void add_text_to_entry(const char *text);
  void clear_entry();
  void del_char_from_entry();
  void evaluate();
};
}  // namespace s21::view

#endif  // SRC_VIEW_GTK_MAIN_WINDOW_H_
