CXX := g++
CXXFLAGS := -MD

ifeq (true, true)
	CXXFLAGS += -Wall -Wextra
	ifeq ($(shell uname), Linux)
		CXXFLAGS += -g -fsanitize=address
	else ifeq ($(shell uname), Darwin)
		CXXFLAGS += -g
	endif
endif

# Libcalculator.a
CALC_BUILD_DIR = build/calculator
CALC_SRCS = $(shell find ./models/calculator -name "*.cc")
CALC_OBJS = $(addprefix $(CALC_BUILD_DIR)/,$(notdir $(CALC_SRCS:%.cc=%.o)))

$(CALC_BUILD_DIR)/%.o: models/calculator/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(CALC_BUILD_DIR)/libcalculator.a: $(CALC_OBJS)
	ar rcs $@ $^

# Tests
TESTS_BUILD_DIR = build/test
TESTS_SRCS = $(shell find ./test -name "*.cc")
TESTS_OBJS = $(addprefix $(TESTS_BUILD_DIR)/,$(notdir $(TESTS_SRCS:%.cc=%.o)))

$(TESTS_BUILD_DIR)/%.o: test/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

CALC_COV_BUILD_DIR = build/test
CALC_COV_SRCS = $(shell find ./models/calculator -name "*.cc")
CALC_COV_OBJS = $(addprefix $(CALC_COV_BUILD_DIR)/,$(notdir $(CALC_COV_SRCS:%.cc=%.o)))

$(CALC_COV_BUILD_DIR)/%.o: models/calculator/%.cc
	$(CXX) $(CXXFLAGS) --coverage -c $< -o $@

tests: $(TESTS_OBJS) $(CALC_COV_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgcov

# Views
VIEW_BUILD_DIR = build/view
VIEW_SRCS = $(shell find ./view/gtk -name "*.cc")
VIEW_OBJS = $(addprefix $(VIEW_BUILD_DIR)/,$(notdir $(VIEW_SRCS:%.cc=%.o)))

$(VIEW_BUILD_DIR)/%.o: view/gtk/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ `pkg-config gtkmm-3.0 --libs --cflags`

# Controllers
CNTRL_BUILD_DIR = build/controller
CNTRL_SRCS = $(shell find ./controller -name "*.cc")
CNTRL_OBJS = $(addprefix $(CNTRL_BUILD_DIR)/,$(notdir $(CNTRL_SRCS:%.cc=%.o)))

$(CNTRL_BUILD_DIR)/%.o: controller/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Calculator
build/main.o: main.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ `pkg-config gtkmm-3.0 --libs --cflags`

calculator: build/main.o $(VIEW_OBJS) $(CNTRL_OBJS) $(CALC_BUILD_DIR)/libcalculator.a
	$(CXX) $(CXXFLAGS) $^ -o $@ `pkg-config gtkmm-3.0 --libs --cflags`

# Gcov report
gcov_report: tests
	./tests
	lcov --directory . -t "tests" -o tests.info -c --no-external
	genhtml -o gcov_report tests.info
	@echo
	@echo report path is `pwd`/report/index.html

linter:
	@cp ../materials/linters/CPPLINT.cfg .
	@find . -name "*.cc" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg


clean:
	@find -name "*.d" -delete
	@find -name "*.o" -delete
	@find -name "*.a" -delete
	@find -name "*.gcno" -delete
	@find -name "*.gcda" -delete
	@rm -f tests
	@rm -f calculator
	@rm -f tests.info
	@rm -rf gcov_report

-include $(shell find ./build -name "*.d")
