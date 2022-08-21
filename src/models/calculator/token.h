#ifndef SRC_MODELS_CALCULATOR_TOKEN_H_
#define SRC_MODELS_CALCULATOR_TOKEN_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

namespace s21::math {

template <typename token_name, typename token_value> class IBaseToken {
public:
  virtual ~IBaseToken() = default;

  [[nodiscard]] virtual const token_name &GetName() const = 0;
  [[nodiscard]] virtual const token_value &GetValue() const = 0;
};

template <typename token_name, typename token_value>
class BaseToken : public IBaseToken<token_name, token_value> {
public:
  using name_type = token_name;
  using value_type = token_value;

  BaseToken() : name_(), value_() {}
  BaseToken(name_type name, value_type value)
      : name_(name), value_(std::move(value)) {}
  ~BaseToken() override = default;

  [[nodiscard]] const name_type &GetName() const override { return name_; }

  [[nodiscard]] const value_type &GetValue() const override { return value_; }

  BaseToken &Rename(const name_type &name) {
    name_ = name;
    return *this;
  }

  BaseToken &ChangeValue(const value_type &value) {
    value_ = value;
    return *this;
  }

protected:
  name_type name_;
  value_type value_;
};

enum class Name {
  kNumber,
  kVariable,
  kOperator,
  kUnaryOperator,
  kInfixFunction,
  kOpenBracket,
  kCloseBracket,
  kUnknown,
  kEmpty
};

class MathToken : public BaseToken<Name, std::string> {
public:
  MathToken() : BaseToken() {}
  MathToken(Name name, std::string value) : BaseToken(name, std::move(value)){};

  bool operator==(const MathToken &other) const;

  bool operator==(const Name &name) const;
  bool operator!=(const Name &name) const;

  bool operator==(const std::string &value) const;
  bool operator!=(const std::string &value) const;

  [[nodiscard]] bool IsNumber() const;
  [[nodiscard]] bool IsOperator() const;
  [[nodiscard]] bool IsOpenBracket() const;
  [[nodiscard]] bool IsCloseBracket() const;
  [[nodiscard]] bool IsFunction() const;
  [[nodiscard]] bool IsWrong() const;

  [[nodiscard]] int Priority() const;

  [[nodiscard]] bool IsRightAssociative() const;
  [[nodiscard]] bool IsLeftAssociative() const;
};

} // namespace s21::math

#endif // SRC_MODELS_CALCULATOR_TOKEN_H_
