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

  void BindButtons();
  void SwitchToPlotter();
  void SwitchToCredit();

  void BindButtonToShowPlotter(const char *glade_id);
  void BindButtonToShowCredit(const char *glade_id);
  void BindButtonToAddTextEntry(const char *glade_id, const char *text);
  void BindButtonToClearEntry(const char *glade_id);
  void BindButtonToDelCharEntry(const char *glade_id);
  void BindButtonToEvaluate(const char *glade_id);

  void AddTextToEntry(const char *text);
  void ClearEntry();
  void DelCharFromEntry();
  void Evaluate();
};
}  // namespace s21::view

#endif  // SRC_VIEW_GTK_MAIN_WINDOW_H_
