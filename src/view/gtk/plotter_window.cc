#include "plotter_window.h"
#include "gtkmm/drawingarea.h"

namespace s21::view {

PlotterArea::PlotterArea() {
  signal_draw().connect(sigc::mem_fun(*this, &PlotterArea::DrawCall));
}

bool PlotterArea::DrawCall(const Cairo::RefPtr<Cairo::Context> &cr) {
  if (function_.Length() == 0)
    return true;

  box_left_ = 100;
  box_right_ = get_allocation().get_width() - 100;
  box_top_ = 25;
  box_bot_ = get_allocation().get_height() - 75;

  x_min_ = properties_.x_min();
  x_max_ = properties_.x_max();
  y_min_ = properties_.y_min();
  y_max_ = properties_.y_max();

  x_stretching_k_ = (box_right_ - box_left_) / (x_max_ - x_min_);
  y_stretching_k_ = (box_top_ - box_bot_) / (y_max_ - y_min_);

  x_start_ = -x_stretching_k_ * x_min_ + box_left_;
  y_start_ = -y_stretching_k_ * y_min_ + box_bot_;

  // background
  draw_background(cr);

  // graph
  draw_graph(cr);

  // box
  draw_box(cr);

  // labels
  draw_labels(cr);

  return false;
}

void PlotterArea::draw_background(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->save();
  cr->set_source_rgb(1, 1, 1);
  cr->paint();
  cr->restore();
}

void PlotterArea::draw_graph(const Cairo::RefPtr<Cairo::Context> &cr) {
  int chunk_size = 5000;
  cr->set_source_rgb(1, 0, 0);
  cr->set_line_width(1);
  cr->move_to(function_.X(0) * x_stretching_k_ + x_start_,
              function_.Y(0) * y_stretching_k_ + y_start_);

  int i = 0;
  while (i < function_.Length()) {
    if (!UDFunction::IsNumber(function_.Y(i))) {
      while ((i < (function_.Length() - 1)) &&
          !UDFunction::IsNumber(function_.Y(i))) {
        ++i;
      }
      cr->move_to(function_.X(i) * x_stretching_k_ + x_start_,
                  function_.Y(i) * y_stretching_k_ + y_start_);
    }
    cr->line_to(function_.X(i) * x_stretching_k_ + x_start_,
                function_.Y(i) * y_stretching_k_ + y_start_);
    // fix crash
    if (i % chunk_size == chunk_size - 1) {
      cr->stroke();
    }
    ++i;
  }
  cr->stroke();
}

void PlotterArea::draw_box(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(0, 0, 0);
  cr->set_line_width(1);
  cr->move_to(box_left_, box_top_);
  cr->line_to(box_right_, box_top_);
  cr->line_to(box_right_, box_bot_);
  cr->line_to(box_left_, box_bot_);
  cr->line_to(box_left_, box_top_);
  cr->stroke();

  for (int i = 0; i <= 6; ++i) {
    cr->move_to(box_left_ - 15, box_top_ + i / 6. * (box_bot_ - box_top_));
    cr->line_to(box_left_, box_top_ + i / 6. * (box_bot_ - box_top_));
  }

  for (int i = 0; i <= 5; ++i) {
    cr->move_to(box_left_ + i / 5. * (box_right_ - box_left_), box_bot_);
    cr->line_to(box_left_ + i / 5. * (box_right_ - box_left_), box_bot_ + 15);
  }
}

void PlotterArea::draw_labels(const Cairo::RefPtr<Cairo::Context> &cr) {
  char str_num[32];
  Cairo::TextExtents extents;
  cr->set_source_rgb(0, 0, 0);
  cr->select_font_face("Helvetica", Cairo::FONT_SLANT_NORMAL,
                       Cairo::FONT_WEIGHT_BOLD);
  cr->set_font_size(24);

  cr->get_text_extents("y", extents);
  cr->move_to(box_left_, box_top_ - extents.height * 0.5);
  cr->show_text("y");

  cr->get_text_extents("x", extents);
  cr->move_to(box_right_ + extents.width * 0.5, box_bot_);
  cr->show_text("x");

  cr->select_font_face("Helvetica", Cairo::FONT_SLANT_NORMAL,
                       Cairo::FONT_WEIGHT_NORMAL);
  cr->set_font_size(12);
  double d_grid_x = (x_max_ - x_min_) / 5;
  double d_grid_y = (y_max_ - y_min_) / 6;

  for (int i = 0; i <= 6; ++i) {
    g_snprintf(str_num, sizeof(str_num), "%.3g", y_max_ - i * d_grid_y);
    cr->get_text_extents(str_num, extents);
    cr->move_to(box_left_ - extents.width - 15,
                box_top_ + i / 6. * (box_bot_ - box_top_) + extents.height / 2);
    cr->show_text(str_num);
  }

  for (int i = 0; i <= 5; ++i) {
    cr->save();
    g_snprintf(str_num, sizeof(str_num), "%.3g", x_min_ + d_grid_x * i);
    cr->get_text_extents(str_num, extents);
    cr->move_to(box_left_ + i / 5. * (box_right_ - box_left_) -
                    extents.width / 2,
                box_bot_ + extents.height + 25);
    cr->rotate(-3.14 / 12);
    cr->show_text(std::to_string(x_min_ + d_grid_x * i));
    cr->restore();
  }

  // x/y
  cr->set_font_size(24);
  double visual_scale_x = (box_right_ - box_left_) / (x_max_ - x_min_);
  double visual_scale_y = (box_bot_ - box_top_) / (y_max_ - y_min_);
  g_snprintf(str_num, sizeof(str_num), "x/y %.3g",
             visual_scale_x / visual_scale_y);
  cr->get_text_extents(str_num, extents);
  cr->move_to(box_right_ - extents.width, box_top_);
  cr->show_text(str_num);
  cr->stroke();

  cr->stroke();
}

void PlotterArea::DrawGraph2D(const UDFunction &function,
                              const GraphProperties &properties) {
  function_ = function;
  properties_ = properties;
  queue_draw();
}

PlotterWindow::PlotterWindow(controller::CalculatorController *controller)
    : controller_(controller) {
  set_title("S21 math plotter");
  set_default_size(600, 500);

  signal_key_press_event().connect(
      sigc::mem_fun(*this, &PlotterWindow::PlotterKeyHandler), false);

  math_expression_entry_.set_max_length(255);
  math_expression_entry_.set_placeholder_text("input math expression");
  math_expression_entry_.set_text("tan(x)");

  draw_button_.signal_clicked().connect(
      sigc::mem_fun(*this, &PlotterWindow::ButtonPlotHandler));
  draw_button_.set_label("plot");

  entry_box_.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  entry_box_.set_spacing(5);
  math_expression_entry_.set_hexpand(true);
  math_expression_entry_.set_vexpand(false);
  entry_box_.add(math_expression_entry_);
  entry_box_.add(draw_button_);

  x_min_entry_.set_max_length(63);
  x_max_entry_.set_max_length(63);
  y_min_entry_.set_max_length(63);
  y_max_entry_.set_max_length(63);

  x_min_entry_.set_placeholder_text("min x value");
  x_min_entry_.set_text("-5");
  x_max_entry_.set_placeholder_text("max x value");
  x_max_entry_.set_text("5");
  y_min_entry_.set_placeholder_text("min Y value");
  y_min_entry_.set_text("-3");
  y_max_entry_.set_placeholder_text("max Y value");
  y_max_entry_.set_text("3");

  window_box_.set_margin_top(5);
  window_box_.set_margin_bottom(5);
  window_box_.set_margin_left(5);
  window_box_.set_margin_right(5);
  window_box_.set_orientation(Gtk::ORIENTATION_VERTICAL);
  window_box_.set_spacing(5);

  axis_entry_grid_.set_row_spacing(5);
  axis_entry_grid_.set_column_spacing(5);
  axis_entry_grid_.set_column_homogeneous(true);
  axis_entry_grid_.attach(x_min_entry_, 0, 0);
  axis_entry_grid_.attach(x_max_entry_, 1, 0);
  axis_entry_grid_.attach(y_min_entry_, 0, 1);
  axis_entry_grid_.attach(y_max_entry_, 1, 1);

  window_box_.add(entry_box_);
  window_box_.add(axis_entry_grid_);
  draw_area_.property_expand() = Gtk::EXPAND;
  draw_area_.set_size_request(600, 400);
  window_box_.add(draw_area_);
  add(window_box_);
  show_all_children();
}

bool PlotterWindow::PlotterKeyHandler(GdkEventKey *event) {
  if (event->keyval == GDK_KEY_Return) {
    Plot();
    return true;
  }
  return false;
}

void PlotterWindow::ButtonPlotHandler() {
  Plot();
}

void PlotterWindow::Plot() {
  GraphProperties properties(x_min_entry_.get_text(), x_max_entry_.get_text(),
                             y_min_entry_.get_text(), y_max_entry_.get_text());

  UDFunction function = controller_->GetFunction(
      math_expression_entry_.get_text(), properties, 125000);

  draw_area_.DrawGraph2D(function, properties);
}

}  // namespace s21::view
