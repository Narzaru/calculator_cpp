UNAME := $(shell uname)

TARGET = s21_calc

CXX := g++ -std=c++17 -O3

BUILD_DIR := ./build

# Build calculator module
CALC_DIR := ./models/calculator
CALC_BUILD_DIR := $(BUILD_DIR)/calculator
CALC_SRCS := $(shell find $(CALC_DIR) -name "*.cc")
CALC_OBJS := $(addprefix $(CALC_BUILD_DIR)/,$(notdir $(CALC_SRCS:%.cc=%.o)))
CALC_DEPS := $(CALC_OBJS:.o=.d)

TEST_DIR := ./test
TEST_BUILD_DIR := $(BUILD_DIR)/test
TEST_SRCS := $(shell find $(TEST_DIR) -name "*.cc*")
TEST_OBJS := $(addprefix $(TEST_BUILD_DIR)/,$(notdir $(TEST_SRCS:%.cc=%.o)))
TEST_DEPS := $(TEST_OBJS:.o=.d)

-include $(CALC_DEPS)
-include $(TEST_DEPS)

DEBUG = True
ifeq ($(DEBUG), True)
	CXXFLAGS := -Wall -Wextra
	ifeq ($(UNAME), Linux)
		CXXFLAGS := $(CXXFLAGS) -g -fsanitize=address
	else ifeq ($(UNAME), Darwin)
		CXXFLAGS := $(CXXFLAGS) -g
	endif
endif

all: tests
	./tests

install:

uninstall:

clean:
	find -name "*.d" -delete
	find -name "*.o" -delete
	find -name "*.a" -delete
	find -name "*.gcno" -delete
	find -name "*.gcda" -delete
	rm -f tests
	rm -f tests.info
	rm -rf gcov_report

dvi:

dist:

## Model obj
$(CALC_BUILD_DIR)/%.o: $(CALC_DIR)/%.cc
	$(CXX) -MD $(CXXFLAGS) -c $< -o $@


## Model static library
calc-all.a: $(CALC_BUILD_DIR)/calc-all.a
$(CALC_BUILD_DIR)/calc-all.a: $(CALC_OBJS)
	ar rcs $@ $^

## Test obj
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cc
	$(CXX) -MD $(CXXFLAGS) -c $< -o $@

tests: $(TEST_OBJS) calc-all.a
	$(CXX) $(CXXFLAGS) -Itest/ -Imodels/calculator/ $^ -lgtest -o tests -lgcov

## Build calc
s21_calc: calc-all.a
	g++ -g main.c ./view/gtk/calculator.h ./controller/calculator_controller.h ./build/calculator/calc-all.a -fsanitize=address `pkg-config gtkmm-3.0 --cflags --libs`

linter:
	@cp ../materials/linters/CPPLINT.cfg .
	@find . -name "*.cc" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg

gcov_report: tests
	./tests
	lcov --directory . -t "tests" -o tests.info -c --no-external
	genhtml -o gcov_report tests.info
	@echo
	@echo report path is `pwd`/report/index.html

.PHONY: all install uninstall clean dvi dist linter


#g++ main.cc -o simple -g -fsanitize=leak `pkg-config gtkmm-3.0 --cflags --libs` ../../build/calculator/calc-all.a -lgcov && ./simple
