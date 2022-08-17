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
CALC_DEPS = $(CALC_OBJS:%.o=%.c)

vpath %.cc models/calculator/
$(CALC_BUILD_DIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(CALC_BUILD_DIR)/libcalculator.a: $(CALC_OBJS)
	ar rcs $@ $^
vpath

# Tests
TESTS_BUILD_DIR = build/test
TESTS_SRCS = $(shell find ./test -name "*.cc")
TESTS_OBJS = $(addprefix $(TESTS_BUILD_DIR)/,$(notdir $(TESTS_SRCS:%.cc=%.o)))
TESTS_DEPS = $(TESTS_OBJS:%.o=%.c)

vpath %.cc test/
$(TESTS_BUILD_DIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
vpath

CALC_COV_BUILD_DIR = build/test
CALC_COV_SRCS = $(shell find ./models/calculator -name "*.cc")
CALC_COV_OBJS = $(addprefix $(CALC_COV_BUILD_DIR)/,$(notdir $(CALC_COV_SRCS:%.cc=%.o)))
CALC_COV_DEPS = $(CALC_COV_OBJS:%.o=%.c)

vpath %.cc models/calculator/
$(CALC_COV_BUILD_DIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) --coverage -c $< -o $@

tests: $(TESTS_OBJS) $(CALC_COV_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgcov
vpath

main: $(CALC_BUILD_DIR)/libcalculator.a

clean:
	@find -name "*.d" -delete
	@find -name "*.o" -delete
	@find -name "*.a" -delete
	@find -name "*.gcno" -delete
	@find -name "*.gcda" -delete
	@rm -f tests
	@rm -f tests.info
	@rm -rf gcov_report
