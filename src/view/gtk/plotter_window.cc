#include "plotter_window.h"
#include "gtkmm/drawingarea.h"

namespace s21::view {

Area::Area() : need_draw(false) {}

bool Area::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  std::cerr << "wow" << std::endl;
  if (!need_draw)
    return true;

  int X = get_allocation().get_width();
  int Y = get_allocation().get_height();

  double box_left = 75;
  double box_right = X - 75;
  double box_top = 25;
  double box_bot = Y - 25;

  double xmin = std::stod(x_min_);
  double xmax = std::stod(x_max_);

  double ymin = std::stod(y_min_);
  double ymax = std::stod(y_max_);

  double x_stretching_koef = (box_right - box_left) / (xmax - xmin);
  double y_stretching_koef = (box_top - box_bot) / (ymax - ymin);

  double xstart = -x_stretching_koef * xmin + box_left;
  double ystart = -y_stretching_koef * ymin + box_bot;

  cr->set_source_rgb(1, 0, 0);
  cr->set_line_width(1);
  cr->set_line_join(Cairo::LINE_JOIN_ROUND);
  cr->move_to(function_.x(0) * x_stretching_koef + xstart,
              function_.y(0) * y_stretching_koef + ystart);

  int i = 0;
  while (i < function_.GetNumberOfDots()) {
    if (std::isinf(function_.x(i)) || std::isnan(function_.y(i))) {
      while (i < function_.GetNumberOfDots() - 1 && (std::isinf(function_.x(i)) || std::isnan(function_.y(i)))) {
        ++i;
      }
      cr->move_to(function_.x(i) * x_stretching_koef + xstart,
                  function_.y(i) * y_stretching_koef + ystart);
    }
    cr->line_to(function_.x(i) * x_stretching_koef + xstart,
                function_.y(i) * y_stretching_koef + ystart);
    ++i;
  }
  cr->stroke();

  need_draw = false;
  std::cerr << "owo" << std::endl;
  return true;
}

void Area::DrawGraph2D(const s21::UniformlyDiscreteFunction &function,
                       const Glib::ustring &x_min,
                       const Glib::ustring &x_max,
                       const Glib::ustring &y_min,
                       const Glib::ustring &y_max) {
  if (!need_draw) {
    need_draw = true;
    function_ = function;
    x_min_ = x_min;
    x_max_ = x_max;
    y_min_ = y_min;
    y_max_ = y_max;
    queue_draw();
  }
}

Area::~Area() = default;

PlotterWindow::PlotterWindow(s21::CalculatorController *controller) : controller_(controller) {
  set_title("S21 math plotter");
  set_default_size(800, 400);
  set_resizable(false);

  math_expression_entry_.set_max_length(255);
  math_expression_entry_.set_placeholder_text("input math expression");
  math_expression_entry_.signal_activate().connect(
      sigc::mem_fun(*this, &PlotterWindow::Evaluate));

  x_min_.set_max_length(63);
  x_max_.set_max_length(63);
  y_min_.set_max_length(63);
  y_max_.set_max_length(63);

  x_min_.set_placeholder_text("min x value");
  x_max_.set_placeholder_text("max x value");
  y_min_.set_placeholder_text("min y value");
  y_max_.set_placeholder_text("max y value");

  window_box_.set_orientation(Gtk::ORIENTATION_VERTICAL);
  window_box_.set_spacing(5);

  axis_entry_grid_.set_row_spacing(5);
  axis_entry_grid_.set_column_spacing(5);
  axis_entry_grid_.set_column_homogeneous(true);
  axis_entry_grid_.attach(x_min_, 0, 0);
  axis_entry_grid_.attach(x_max_, 1, 0);
  axis_entry_grid_.attach(y_min_, 0, 1);
  axis_entry_grid_.attach(y_max_, 1, 1);

  window_box_.add(math_expression_entry_);
  window_box_.add(axis_entry_grid_);
  draw_area_.property_expand() = Gtk::EXPAND;
  window_box_.add(draw_area_);
  add(window_box_);
  show_all_children();
}

void PlotterWindow::Evaluate() {

  s21::UniformlyDiscreteFunction function = controller_->GetFunction(math_expression_entry_.get_text(),
                                                                     x_min_.get_text(),
                                                                     x_max_.get_text(),
                                                                     y_min_.get_text(),
                                                                     y_max_.get_text(),
                                                                     100000);

  draw_area_.DrawGraph2D(function,
                         x_min_.get_text(),
                         x_max_.get_text(),
                         y_min_.get_text(),
                         y_max_.get_text());
}

PlotterWindow::~PlotterWindow() = default;

}  // namespace s21::view
