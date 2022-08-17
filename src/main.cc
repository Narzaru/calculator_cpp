#include "controller/calculator_controller.h"
#include "models/calculator/calculator.h"
#include "view/gtk/main_window.h"
#include <gtkmm-3.0/gtkmm.h>

int main(int argc, char **argv) {
  auto application = Gtk::Application::create(argc, argv);

  s21::calculator::Calculator calculator_model;
  s21::CalcultatorConstroller calculator_controller(&calculator_model);
  s21::view::MainWindow *calculator_view = s21::view::MainWindow::GetInstance();
  calculator_view->BindController(&calculator_controller);
  int code = application->run(*calculator_view);
  calculator_view->close();
  delete calculator_view;
  return code;
}
