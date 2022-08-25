#include <algorithm>

#include "main_window.h"
#include "credit_window.h"

namespace s21::view {
MainWindow::MainWindow(GtkWindow *c_object,
                       const Glib::RefPtr<Gtk::Builder> &builder)
    : Window(c_object), builder_(builder) {
  BindButtons();
}

MainWindow::~MainWindow() = default;

void MainWindow::BindCalculatorController(
    controller::CalculatorController *controller) {
  controller_ = controller;
}

MainWindow *MainWindow::GetInstance() {
  MainWindow *calculator_instance;
  Glib::RefPtr<Gtk::Builder> builder =
      Gtk::Builder::create_from_resource("/uis/ui.glade");
  builder->get_widget_derived("calculator_view", calculator_instance);
  return calculator_instance;
}

void MainWindow::BindButtons() {
  builder_->get_widget("entry", entry_);
  builder_->get_widget("entry_x", entry_x_);

  BindButtonToAddTextEntry("button_1", "1");
  BindButtonToAddTextEntry("button_2", "2");
  BindButtonToAddTextEntry("button_3", "3");
  BindButtonToAddTextEntry("button_4", "4");
  BindButtonToAddTextEntry("button_5", "5");
  BindButtonToAddTextEntry("button_6", "6");
  BindButtonToAddTextEntry("button_7", "7");
  BindButtonToAddTextEntry("button_8", "8");
  BindButtonToAddTextEntry("button_9", "9");
  BindButtonToAddTextEntry("button_0", "0");
  BindButtonToAddTextEntry("button_mod", "mod");
  BindButtonToAddTextEntry("button_pow", "pow");
  BindButtonToAddTextEntry("button_/", "/");
  BindButtonToAddTextEntry("button_*", "*");
  BindButtonToAddTextEntry("button_-", "-");
  BindButtonToAddTextEntry("button_+", "+");
  BindButtonToAddTextEntry("button_.", ".");
  BindButtonToAddTextEntry("button_e", "e");
  BindButtonToAddTextEntry("button_(", "(");
  BindButtonToAddTextEntry("button_)", ")");
  BindButtonToAddTextEntry("button_sin", "sin");
  BindButtonToAddTextEntry("button_cos", "cos");
  BindButtonToAddTextEntry("button_tan", "tan");
  BindButtonToAddTextEntry("button_asin", "asin");
  BindButtonToAddTextEntry("button_acos", "acos");
  BindButtonToAddTextEntry("button_atan", "atan");
  BindButtonToAddTextEntry("button_sqrt", "sqrt");
  BindButtonToAddTextEntry("button_ln", "ln");
  BindButtonToAddTextEntry("button_log", "log");

  BindButtonToClearEntry("button_C");

  BindButtonToDelCharEntry("button_DEL");

  BindButtonToEvaluate("button_=");

  BindButtonToShowPlotter("button_plot");
  BindButtonToShowCredit("button_credit");


  entry_->signal_activate().connect(
      sigc::mem_fun(*this, &MainWindow::Evaluate));
}

void MainWindow::SwitchToPlotter() {
  PlotterWindow *plotter = new PlotterWindow(controller_);
  plotter->show();
}

void MainWindow::SwitchToCredit() {
  CreditWindow *credit = new CreditWindow(controller_);
  credit->show();
}

void MainWindow::BindButtonToShowPlotter(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::SwitchToPlotter));
}

void MainWindow::BindButtonToShowCredit(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::SwitchToCredit));
}

void MainWindow::BindButtonToAddTextEntry(const char *glade_id,
                                          const char *text) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::bind(sigc::mem_fun(*this, &MainWindow::AddTextToEntry), text));
}

void MainWindow::BindButtonToClearEntry(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::ClearEntry));
}

void MainWindow::BindButtonToDelCharEntry(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::DelCharFromEntry));
}

void MainWindow::BindButtonToEvaluate(const char *glade_id) {
  Gtk::Button *temp_button_ref;
  builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
  temp_button_ref->signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::Evaluate));
}

void MainWindow::AddTextToEntry(const char *text) {
  Glib::ustring string = entry_->get_text();
  string.insert(entry_->get_position(), text);
  entry_->set_text(string);
  int size = 0;
  while (string[size] != '\0') {
    size++;
  }
  entry_->set_position(entry_->get_position() + size);
}

void MainWindow::ClearEntry() {
  entry_->delete_text(0, -1);
  entry_x_->delete_text(0, -1);
}

void MainWindow::DelCharFromEntry() {
  int start_position = entry_->get_position() - 1;
  int end_position = entry_->get_position();
  entry_->delete_text(start_position, end_position);
}

void MainWindow::Evaluate() {
  const Glib::ustring &expression = entry_->get_text();
  const Glib::ustring &x_str = entry_x_->get_text();

  double result = controller_->Evaluate(expression, x_str);
  ClearEntry();
  std::string str_result = std::to_string(result);
  str_result.erase(str_result.find_last_not_of('0') + 1, std::string::npos);
  str_result.erase(str_result.find_last_not_of('.') + 1, std::string::npos);
  AddTextToEntry(str_result.c_str());
}

}  // namespace s21::view
