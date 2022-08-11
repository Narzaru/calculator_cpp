#ifndef SRC_MODELS_CALCULATOR_CALCULATOR_BASE_EXCEPTIONS_H_
#define SRC_MODELS_CALCULATOR_CALCULATOR_BASE_EXCEPTIONS_H_

#include <exception>
namespace s21::exception {
class IMyBaseException : public std::exception {
 public:
  [[nodiscard]] virtual const char *who() const noexcept = 0;
};
}  // namespace s21::exception

#endif  // SRC_MODELS_CALCULATOR_CALCULATOR_BASE_EXCEPTIONS_H_
