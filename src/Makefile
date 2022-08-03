UNAME := $(shell uname)

TARGET = s21_calc

CXX := g++

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

dvi:

dist:

## Model obj
$(CALC_BUILD_DIR)/%.o: $(CALC_DIR)/%.cc
	$(CXX) -MD $(CXXFLAGS) -c $< -o $@

## Model static library
$(CALC_BUILD_DIR)/calc-all.a: $(CALC_OBJS)
	ar rcs $@ $^

## Test obj
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cc
	$(CXX) -MD $(CXXFLAGS) -c $< -o $@

tests: $(TEST_OBJS) $(CALC_BUILD_DIR)/calc-all.a
	$(CXX) $(CXXFLAGS) -Itest/ -Imodels/calculator/ $^ -lgtest -o tests

models/calculator/calculator.cc:

.PHONY: all install uninstall clean dvi dist
