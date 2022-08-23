#ifndef SRC_VIEW_GTK_FUNCTION_H_
#define SRC_VIEW_GTK_FUNCTION_H_

namespace s21::view {

class UDFunction final {
 public:
  UDFunction();
  explicit UDFunction(int number_of_dots);
  UDFunction(int number_of_dots, double x_begin, double x_end);
  UDFunction(const UDFunction &other);
  ~UDFunction();

  UDFunction &operator=(const UDFunction &other);

  void SetDomain(double y_min, double y_max);

  [[nodiscard]] double &X(int i);
  [[nodiscard]] double &Y(int i);
  [[nodiscard]] const double &X(int i) const;
  [[nodiscard]] const double &Y(int i) const;

  [[nodiscard]] const int &Length() const;

  static bool IsNumber(const double &number);

 private:
  int number_of_dots_;

  double *x_values_;
  double *y_values_;
};
}  // namespace s21::view

#endif  // SRC_VIEW_GTK_FUNCTION_H_
