#include <ctime>
#include <exception>
#include <gtest/gtest.h>

#include <list>
#include <locale>
#include <new>
#include <ostream>

#include "../models/calculator/calculator.h"
#include "../models/calculator/calculator_base_exceptions.h"

std::ostream &operator<<(std::ostream &stream, s21::exception::IMyBaseException &e) {
  stream << "[" << e.who() << "] ";
  stream << e.what() << std::endl;
  return stream;
}

TEST(suite, test_1) {
  s21::Calculator calc;
  ASSERT_ANY_THROW(
    calc.push_expression("cas(3)");
    calc.compile_expression();
    [[maybe_unused]] double a = calc.calculate();
  );
}

TEST(suite, test_2) {
  s21::Calculator calc;
  ASSERT_ANY_THROW(
    calc.push_expression("cas(");
    calc.compile_expression();
    [[maybe_unused]] double a = calc.calculate();
  );
}

TEST(suite, test_5) {
  s21::Calculator calc;
  ASSERT_ANY_THROW(
    calc.push_expression("cos(x)");
    calc.compile_expression();
    [[maybe_unused]] double a = calc.calculate();
  );
}

TEST(suite, test_3) {
  s21::Calculator calculator;
  double x = 1;
  ASSERT_NO_THROW(
    [[maybe_unused]] double a = calculator.calculate("-cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x", &x);
  );
}

TEST(suite, test_4) {
  s21::Calculator calculator;
  ASSERT_NO_THROW(
    double x = 1;
    calculator.push_expression("-cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x");
    calculator.compile_expression();
    [[maybe_unused]] double a = calculator.calculate(&x);
  );
}

TEST(suite, test_6) {
  s21::Calculator calculator;
  ASSERT_NO_THROW(
    double x = 1;
    calculator.push_expression("+cos(sin(asin(atan(0.5))))^1*2-3/4%2*1e+1-1.e+0+x");
    calculator.compile_expression();
    [[maybe_unused]] double a = calculator.calculate(&x);
  );
}

TEST(suite, test_7) {
  s21::Calculator calculator;
  ASSERT_ANY_THROW(
    double x = 1;
    calculator.push_expression("3+");
    calculator.compile_expression();
    [[maybe_unused]] double a = calculator.calculate(&x);
  );
}
