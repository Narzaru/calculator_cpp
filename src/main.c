#include "controller/calculator_controller.h"
#include "gtkmm/main.h"
#include "models/calculator/calculator.h"
#include "view/gtk/calculator.h"

int main(int argc, char **argv) {
  auto application = Gtk::Application::create(argc, argv);

  s21::calculator::Calculator calculator_model;
  s21::CalcultatorConstroller calculator_controller(calculator_model);
  s21::view::Calcultor *calculator_view = s21::view::Calcultor::GetInstance();
  calculator_view->BindController(&calculator_controller);

  return application->run(*calculator_view);
}
