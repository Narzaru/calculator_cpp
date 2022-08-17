#ifndef SRC_VIEW_GTK_PLOTTER_WINDOW_H_
#define SRC_VIEW_GTK_PLOTTER_WINDOW_H_

#include "gtkmm/drawingarea.h"
#include "gtkmm/window.h"

namespace s21 {
namespace view {

class PlotterArea : public Gtk::DrawingArea {
};

class Plotter : public Gtk::Window {
 public:
  Plotter();
  ~Plotter() override = default;

  PlotterArea draw_area_;
 private:
  static int instance_count_;
};

}  // namespace view
}  // namespace s21

#endif  // SRC_VIEW_GTK_PLOTTER_WINDOW_H_
