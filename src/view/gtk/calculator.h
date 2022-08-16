#ifndef __CALCULATOR_VIEW_H__
#define __CALCULATOR_VIEW_H__

// #include <gtkmm.h>

#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>

#include "../../controller/calculator_controller.h"

namespace s21 {
namespace view {
class Calcultor : public Gtk::Window {
  using Builder = Gtk::Builder;
  using Window = Gtk::Window;
  template <typename T>
  using RefPtr = Glib::RefPtr<T>;

 public:
  Calcultor(GtkWindow *c_object, const Glib::RefPtr<Builder> &builder)
      : Window(c_object), builder_(builder) {
    bind_buttons();
  }
  ~Calcultor() = default;

  void BindController(s21::CalcultatorConstroller *controller) {
    controller_ = controller;
  }

  static Calcultor *GetInstance() {
    Calcultor *calculator_instance;
    RefPtr<Builder> builder = Builder::create_from_file("ui.glade");
    builder->get_widget_derived("calculator_view", calculator_instance);
    return calculator_instance;
  }

 private:
  const RefPtr<Builder> &builder_;
  Gtk::Entry *entry_;

  s21::CalcultatorConstroller *controller_;

    inline void bind_buttons() {
      bind_button_to_add_text_in_entry("button_1", "1");
      bind_button_to_add_text_in_entry("button_2", "2");
      bind_button_to_add_text_in_entry("button_3", "3");
      bind_button_to_add_text_in_entry("button_4", "4");
      bind_button_to_add_text_in_entry("button_5", "5");
      bind_button_to_add_text_in_entry("button_6", "6");
      bind_button_to_add_text_in_entry("button_7", "7");
      bind_button_to_add_text_in_entry("button_8", "8");
      bind_button_to_add_text_in_entry("button_9", "9");
      bind_button_to_add_text_in_entry("button_0", "0");
      bind_button_to_add_text_in_entry("button_mod", "mod");
      bind_button_to_add_text_in_entry("button_pow", "pow");
      bind_button_to_add_text_in_entry("button_/", "/");
      bind_button_to_add_text_in_entry("button_*", "*");
      bind_button_to_add_text_in_entry("button_-", "-");
      bind_button_to_add_text_in_entry("button_+", "+");
      bind_button_to_add_text_in_entry("button_.", ".");
      bind_button_to_add_text_in_entry("button_(", "(");
      bind_button_to_add_text_in_entry("button_)", ")");
      bind_button_to_add_text_in_entry("button_sin", "sin");
      bind_button_to_add_text_in_entry("button_cos", "cos");
      bind_button_to_add_text_in_entry("button_tan", "tan");
      bind_button_to_add_text_in_entry("button_asin", "asin");
      bind_button_to_add_text_in_entry("button_acos", "acos");
      bind_button_to_add_text_in_entry("button_atan", "atan");
      bind_button_to_add_text_in_entry("button_sqrt", "sqrt");
      bind_button_to_add_text_in_entry("button_ln", "ln");
      bind_button_to_add_text_in_entry("button_log", "log");

      bind_button_to_clear_entry("button_C");

      bind_button_to_del_char_entry("button_DEL");

      bind_button_to_evaluate("button_=");

      builder_->get_widget("entry", entry_);
    }

    inline void bind_button_to_add_text_in_entry(const char *glade_id, const
    char *text) {
      Gtk::Button *temp_button_ref;
      builder_->get_widget(glade_id, temp_button_ref);
      temp_button_ref->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &Calcultor::add_text_to_entry), text));
    }

    inline void bind_button_to_clear_entry(const char *glade_id) {
      Gtk::Button *temp_button_ref;
      builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
      temp_button_ref->signal_clicked().connect(sigc::mem_fun(*this,
      &Calcultor::clear_entry));
    }

    inline void bind_button_to_del_char_entry(const char *glade_id) {
      Gtk::Button *temp_button_ref;
      builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
      temp_button_ref->signal_clicked().connect(sigc::mem_fun(*this,
      &Calcultor::del_char_from_entry));
    }

    inline void bind_button_to_evaluate(const char *glade_id) {
      Gtk::Button *temp_button_ref;
      builder_->get_widget<Gtk::Button>(glade_id, temp_button_ref);
      temp_button_ref->signal_clicked().connect(sigc::mem_fun(*this,
      &Calcultor::evaluate_handler));
    }

    inline void add_text_to_entry(const char *text) {
      Glib::ustring gstring = entry_->get_text();
      gstring.insert(entry_->get_position(), text);
      entry_->set_text(gstring);
      int size = 0;
      while (gstring[size] != '\0') size++;
      entry_->set_position(entry_->get_position() + size);
    }

    inline void clear_entry() {
      entry_->delete_text(0, -1);
    }

    inline void del_char_from_entry() {
      entry_->delete_text(entry_->get_position() - 1,
      entry_->get_position());
    }

    inline void evaluate_handler() {
      entry_->set_text(std::to_string(controller_->evaluate(entry_->get_text())));
    }
};

}  // namespace view
}  // namespace s21

#endif  // __CALCULATOR_VIEW_H__
