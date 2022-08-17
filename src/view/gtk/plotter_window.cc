#include "plotter_window.h"
#include "gtkmm/drawingarea.h"

namespace s21 {
namespace view {
int Plotter::instance_count_ = 0;

Plotter::Plotter() {
  ++instance_count_;

  set_title("S21 math plotter");
  add(draw_area_);
  set_default_size(500, 500);
  set_resizable(false);
  show_all_children();
}


}  // namespace view
}  // namespace s21
