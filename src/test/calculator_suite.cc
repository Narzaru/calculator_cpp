#include <ctime>
#include <exception>
#include <gtest/gtest.h>

#include "../models/calculator/calculator.h"
#include "../models/calculator/calculator_base_exceptions.h"

std::ostream &operator<<(std::ostream &stream,
                         s21::exception::IMyBaseException &e) {
  stream << "[" << e.who() << "] ";
  stream << e.what() << std::endl;
  return stream;
}

TEST(suite, test_1) {
  s21::calculator::Calculator calc;
  ASSERT_ANY_THROW(calc.push_expression("cas(3)"); calc.compile_expression();
                   [[maybe_unused]] double a = calc.calculate(););
}

TEST(suite, test_2) {
  s21::calculator::Calculator calc;
  ASSERT_ANY_THROW(calc.push_expression("cas("); calc.compile_expression();
                   [[maybe_unused]] double a = calc.calculate(););
}

TEST(suite, test_5) {
  s21::calculator::Calculator calc;
  ASSERT_ANY_THROW(calc.push_expression("cos(x)"); calc.compile_expression();
                   [[maybe_unused]] double a = calc.calculate(););
}

TEST(suite, test_3) {
  s21::calculator::Calculator calculator;
  double x = 1;
  ASSERT_NO_THROW(double a = calculator.calculate(
                      "-cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x", &x);
                  ASSERT_FLOAT_EQ(-9.288854382, a););
}

TEST(suite, test_4) {
  s21::calculator::Calculator calculator;
  ASSERT_NO_THROW(double x = 1; calculator.push_expression(
      "-cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x");
                  calculator.compile_expression();
                  [[maybe_unused]] double a = calculator.calculate(&x);
                  ASSERT_FLOAT_EQ(-9.288854382, a););
}

TEST(suite, test_6) {
  s21::calculator::Calculator calculator;
  ASSERT_NO_THROW(double x = 1; calculator.push_expression(
      "+cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x");
                  calculator.compile_expression();
                  [[maybe_unused]] double a = calculator.calculate(&x););
}

TEST(suite, test_7) {
  s21::calculator::Calculator calculator;
  ASSERT_ANY_THROW(double x = 1; calculator.push_expression("3+");
                   calculator.compile_expression();
                   [[maybe_unused]] double a = calculator.calculate(&x););
}

TEST(suite, test_8) {
  s21::calculator::Calculator calculator;
  ASSERT_FLOAT_EQ(2.686491, calculator.calculate("sin(1)+5*2.71^-1^100"));
}

TEST(suite, test_9) {
  s21::calculator::Calculator calculator;
  ASSERT_FLOAT_EQ(1e6, calculator.calculate("1e6"));
  ASSERT_FLOAT_EQ(1e-6, calculator.calculate("1e-6"));
  ASSERT_FLOAT_EQ(-1e+6, calculator.calculate("-1e+6"));
  ASSERT_FLOAT_EQ(-5.55e+8, calculator.calculate("-5.55e+8"));
}
