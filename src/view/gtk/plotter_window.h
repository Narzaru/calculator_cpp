#ifndef SRC_VIEW_GTK_PLOTTER_WINDOW_H_
#define SRC_VIEW_GTK_PLOTTER_WINDOW_H_

#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include "../controller/calculator_controller.h"
#include "../controller/axis.h"

namespace s21::view {

class Area : public Gtk::DrawingArea {
 public:
  Area();
  ~Area() override;
  void DrawGraph2D(const s21::UniformlyDiscreteFunction &function,
                   const Glib::ustring &x_min,
                   const Glib::ustring &x_max,
                   const Glib::ustring &y_min,
                   const Glib::ustring &y_max);

 private:
  s21::UniformlyDiscreteFunction function_;
  Glib::ustring x_min_;
  Glib::ustring x_max_;
  Glib::ustring y_min_;
  Glib::ustring y_max_;
  bool need_draw;

 protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
};

class PlotterWindow : public Gtk::Window {
 public:
  explicit PlotterWindow(s21::CalculatorController *controller);
  ~PlotterWindow() override;

 private:
  s21::CalculatorController *controller_;

  Gtk::Entry math_expression_entry_;

  Gtk::Entry x_min_;
  Gtk::Entry x_max_;
  Gtk::Entry y_min_;
  Gtk::Entry y_max_;

  Gtk::Box window_box_;
  Gtk::Grid axis_entry_grid_;
  Area draw_area_;

  void Evaluate();
};

}  // namespace s21::view

#endif  // SRC_VIEW_GTK_PLOTTER_WINDOW_H_
