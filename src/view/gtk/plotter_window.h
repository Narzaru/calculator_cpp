#ifndef SRC_VIEW_GTK_PLOTTER_WINDOW_H_
#define SRC_VIEW_GTK_PLOTTER_WINDOW_H_

#include "controller/calculator_controller.h"
#include "function_properties.h"

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/layout.h>
#include <gtkmm/window.h>

namespace s21::view {

class PlotterArea : public Gtk::Layout {
 public:
  PlotterArea();
  ~PlotterArea() override = default;

  void DrawGraph2D(const UDFunction &function,
                   const GraphProperties &properties);

 private:
  view::UDFunction function_{};
  GraphProperties properties_{};

  double box_left_{};
  double box_right_{};
  double box_top_{};
  double box_bot_{};

  double x_min_{};
  double x_max_{};
  double y_min_{};
  double y_max_{};

  double x_stretching_k_{};
  double y_stretching_k_{};

  double x_start_{};
  double y_start_{};

  bool DrawCall(const Cairo::RefPtr<Cairo::Context> &cr);
  void draw_background(const Cairo::RefPtr<Cairo::Context> &cr);
  void draw_graph(const Cairo::RefPtr<Cairo::Context> &cr);
  void draw_box(const Cairo::RefPtr<Cairo::Context> &cr);
  void draw_labels(const Cairo::RefPtr<Cairo::Context> &cr);
};

class PlotterWindow : public Gtk::Window {
 public:
  explicit PlotterWindow(controller::CalculatorController *controller);
  ~PlotterWindow() override = default;

 private:
  controller::CalculatorController *controller_;

  Gtk::Box window_box_;

  Gtk::Box entry_box_;
  Gtk::Entry math_expression_entry_;

  Gtk::Button draw_button_;
  Gtk::Grid axis_entry_grid_;
  Gtk::Entry x_min_entry_;
  Gtk::Entry x_max_entry_;
  Gtk::Entry y_min_entry_;
  Gtk::Entry y_max_entry_;

  PlotterArea draw_area_;

  bool PlotterKeyHandler(GdkEventKey *event);
  void ButtonPlotHandler();
  void Plot();
};

}  // namespace s21::view

#endif  // SRC_VIEW_GTK_PLOTTER_WINDOW_H_
