#include <algorithm>

#include "main_window.h"
#include "credit_window.h"

namespace s21::view {
MainWindow::MainWindow(GtkWindow *c_object,
                       const Glib::RefPtr<Gtk::Builder> &builder)
    : Window(c_object), builder_(builder) {
  bind_buttons();
}

MainWindow::~MainWindow() = default;

void MainWindow::BindCalculatorController(
    controller::CalculatorController *controller) {
  controller_ = controller;
}

MainWindow *MainWindow::GetInstance() {
  MainWindow *calculator_instance;
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_file("ui.glade");
  builder->get_widget_derived("calculator_view", calculator_instance);
  return calculator_instance;
}

void MainWindow::bind_buttons() {
  builder_->get_widget("entry", entry_);
  builder_->get_widget("entry_x", entry_x_);

  bind_button_to_add_text_entry("button_1", "1");
  bind_button_to_add_text_entry("button_2", "2");
  bind_button_to_add_text_entry("button_3", "3");
  bind_button_to_add_text_entry("button_4", "4");
  bind_button_to_add_text_entry("button_5", "5");
  bind_button_to_add_text_entry("button_6", "6");
  bind_button_to_add_text_entry("button_7", "7");
  bind_button_to_add_text_entry("button_8", "8");
  bind_button_to_add_text_entry("button_9", "9");
  bind_button_to_add_text_entry("button_0", "0");
  bind_button_to_add_text_entry("button_mod", "mod");
  bind_button_to_add_text_entry("button_pow", "pow");
  bind_button_to_add_text_entry("button_/", "/");
  bind_button_to_add_text_entry("button_*", "*");
  bind_button_to_add_text_entry("button_-", "-");
  bind_button_to_add_text_entry("button_+", "+");
  bind_button_to_add_text_entry("button_.", ".");
  bind_button_to_add_text_entry("button_e", "e");
  bind_button_to_add_text_entry("button_(", "(");
  bind_button_to_add_text_entry("button_)", ")");
  bind_button_to_add_text_entry("button_sin", "sin");
  bind_button_to_add_text_entry("button_cos", "cos");
  bind_button_to_add_text_entry("button_tan", "tan");
  bind_button_to_add_text_entry("button_asin", "asin");
  bind_button_to_add_text_entry("button_acos", "acos");
  bind_button_to_add_text_entry("button_atan", "atan");
  bind_button_to_add_text_entry("button_sqrt", "sqrt");
  bind_button_to_add_text_entry("button_ln", "ln");
  bind_button_to_add_text_entry("button_log", "log");

  bind_button_to_clear_entry("button_C");

  bind_button_to_del_char_entry("button_DEL");

  bind_button_to_evaluate("button_=");

  bind_button_to_show_plotter("button_plot");
  bind_button_to_show_credit("button_credit");


  entry_->signal_activate().connect(
      sigc::mem_fun(*this, &MainWindow::evaluate));
}

void MainWindow::SwitchToPlotter() {
  PlotterWindow *plotter = new PlotterWindow(controller_);
  plotter->show();
}

void MainWindow::SwitchToCredit() {
  CreditWindow *credit = new CreditWindow(controller_);
  credit->show();
}

void MainWindow::bind_button_to_show_plotter(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::SwitchToPlotter));
}

void MainWindow::bind_button_to_show_credit(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::SwitchToCredit));
}

void MainWindow::bind_button_to_add_text_entry(const char *glade_id,
                                               const char *text) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::bind(sigc::mem_fun(*this, &MainWindow::add_text_to_entry), text));
}

void MainWindow::bind_button_to_clear_entry(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::clear_entry));
}

void MainWindow::bind_button_to_del_char_entry(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::del_char_from_entry));
}

void MainWindow::bind_button_to_evaluate(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::evaluate));
}

void MainWindow::add_text_to_entry(const char *text) {
  Glib::ustring string = entry_->get_text();
  string.insert(entry_->get_position(), text);
  entry_->set_text(string);
  int size = 0;
  while (string[size] != '\0') {
    size++;
  }
  entry_->set_position(entry_->get_position() + size);
}

void MainWindow::clear_entry() {
  entry_->delete_text(0, -1);
  entry_x_->delete_text(0, -1);
}

void MainWindow::del_char_from_entry() {
  int start_position = entry_->get_position() - 1;
  int end_position = entry_->get_position();
  entry_->delete_text(start_position, end_position);
}

void MainWindow::evaluate() {
  const Glib::ustring &expression = entry_->get_text();
  const Glib::ustring &x_str = entry_x_->get_text();

  double result = controller_->evaluate(expression, x_str);
  clear_entry();
  std::string str_result = std::to_string(result);
  str_result.erase(str_result.find_last_not_of('0') + 1, std::string::npos);
  str_result.erase(str_result.find_last_not_of('.') + 1, std::string::npos);
  add_text_to_entry(str_result.c_str());
}

}  // namespace s21::view
