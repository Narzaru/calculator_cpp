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
  ASSERT_ANY_THROW(calc.PushExpression("cas(3)"); calc.CompileExpression();
                       [[maybe_unused]] double a = calc.Calculate(););
}

TEST(suite, test_2) {
  s21::calculator::Calculator calc;
  ASSERT_ANY_THROW(calc.PushExpression("cas("); calc.CompileExpression();
                       [[maybe_unused]] double a = calc.Calculate(););
}

TEST(suite, test_5) {
  s21::calculator::Calculator calc;
  ASSERT_ANY_THROW(calc.PushExpression("cos(x)"); calc.CompileExpression();
                       [[maybe_unused]] double a = calc.Calculate(););
}

TEST(suite, test_3) {
  s21::calculator::Calculator calculator;
  double x = 1;
  ASSERT_NO_THROW(double a = calculator.Calculate(
      "-cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x", &x);
                      ASSERT_FLOAT_EQ(-9.288854382, a););
}

TEST(suite, test_4) {
  s21::calculator::Calculator calculator;
  ASSERT_NO_THROW(double x = 1; calculator.PushExpression(
      "-cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x");
                      calculator.CompileExpression();
                      [[maybe_unused]] double a = calculator.Calculate(&x);
                      ASSERT_FLOAT_EQ(-9.288854382, a););
}

TEST(suite, test_6) {
  s21::calculator::Calculator calculator;
  ASSERT_NO_THROW(double x = 1; calculator.PushExpression(
      "+cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x");
                      calculator.CompileExpression();
                      [[maybe_unused]] double a = calculator.Calculate(&x););
}

TEST(suite, test_7) {
  s21::calculator::Calculator calculator;
  ASSERT_ANY_THROW(double x = 1; calculator.PushExpression("3+");
                       calculator.CompileExpression();
                       [[maybe_unused]] double a = calculator.Calculate(&x););
}

TEST(suite, test_8) {
  s21::calculator::Calculator calculator;
  ASSERT_FLOAT_EQ(2.686491, calculator.Calculate("sin(1)+5*2.71^-1^100"));
}

TEST(suite, test_9) {
  s21::calculator::Calculator calculator;
  ASSERT_FLOAT_EQ(1e6, calculator.Calculate("1e6"));
  ASSERT_FLOAT_EQ(1e-6, calculator.Calculate("1e-6"));
  ASSERT_FLOAT_EQ(-1e+6, calculator.Calculate("-1e+6"));
  ASSERT_FLOAT_EQ(-5.55e+8, calculator.Calculate("-5.55e+8"));
}

TEST(suite, test_10) {
  s21::calculator::Calculator calculator;
  ASSERT_FLOAT_EQ(2.4178516e+24, calculator.Calculate("2^3^4"));
}

TEST(suite, test_11) {
  s21::calculator::Calculator calculator;
  ASSERT_FLOAT_EQ(0, calculator.Calculate("2^-3^4"));
}
