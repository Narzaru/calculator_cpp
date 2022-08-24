#include "controller/calculator_controller.h"
#include "models/calculator/calculator.h"
#include "view/gtk/main_window.h"
#include <gtkmm-3.0/gtkmm.h>

int main(int argc, char **argv) {
  auto application = Gtk::Application::create(argc, argv);
  int code = 0;

  s21::calculator::Calculator calculator_model;
  s21::bank::CreditCalc credit_calc_model;
  s21::controller::CalculatorController calculator_controller(&calculator_model, &credit_calc_model);
  s21::view::MainWindow *calculator_view = s21::view::MainWindow::GetInstance();
  calculator_view->BindCalculatorController(&calculator_controller);
  code = application->run(*calculator_view);
  calculator_view->close();

  delete calculator_view;

  return code;
}
