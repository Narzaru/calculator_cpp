#ifndef SRC_VIEW_GTK_FUNCTION_PROPERTIES_H_
#define SRC_VIEW_GTK_FUNCTION_PROPERTIES_H_

#include <string>

namespace s21::view {

class GraphProperties {
  using kstring = const std::string &;

public:
  GraphProperties();
  GraphProperties(kstring x_min, kstring x_max, kstring y_min, kstring y_max);

  [[nodiscard]] const double &x_min() const;

  [[nodiscard]] const double &x_max() const;

  [[nodiscard]] const double &y_min() const;

  [[nodiscard]] const double &y_max() const;

private:
  double x_min_;
  double x_max_;
  double y_min_;
  double y_max_;
};

} // namespace s21::view

#endif // SRC_VIEW_GTK_FUNCTION_PROPERTIES_H_
