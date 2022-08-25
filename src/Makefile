CXX := g++
CXXFLAGS := -MD

ifeq (true, true)
	CXXFLAGS += -Wall -Wextra
	ifeq ($(shell uname), Linux)
		CXXFLAGS += -g# -fsanitize=address
	else ifeq ($(shell uname), Darwin)
		CXXFLAGS += -g
	endif
endif

FOLDERS = . ./constroller ./models/calculator ./test ./view/gtk
INCLUDE_PATHS = $(addprefix -I,$(FOLDERS))

# Libcalculator.a
CALC_BUILD_DIR = build/calculator
CALC_SRCS = $(shell find ./models/calculator -name "*.cc")
CALC_OBJS = $(addprefix $(CALC_BUILD_DIR)/,$(notdir $(CALC_SRCS:%.cc=%.o)))

$(CALC_BUILD_DIR)/%.o: models/calculator/%.cc
	$(CXX) -O3 $(CXXFLAGS) -c $< -o $@ $(INCLUDE_PATHS)

$(CALC_BUILD_DIR)/libcalculator.a: $(CALC_OBJS)
	ar rcs $@ $^

# Libbank.a
BANK_BUILD_DIR = build/bank
BANK_SRCS = $(shell find ./models/bank -name "*.cc")
BANK_OBJS = $(addprefix $(BANK_BUILD_DIR)/,$(notdir $(BANK_SRCS:%.cc=%.o)))

$(BANK_BUILD_DIR)/%.o: models/bank/%.cc
	$(CXX) -O3 $(CXXFLAGS) -c $< -o $@ $(INCLUDE_PATHS)

$(BANK_BUILD_DIR)/libbank.a: $(BANK_OBJS)
	ar rcs $@ $^

# Tests
TESTS_BUILD_DIR = build/test
TESTS_SRCS = $(shell find ./test -name "*.cc")
TESTS_OBJS = $(addprefix $(TESTS_BUILD_DIR)/,$(notdir $(TESTS_SRCS:%.cc=%.o)))

$(TESTS_BUILD_DIR)/%.o: test/%.cc
	$(CXX) -O3 $(CXXFLAGS) -c $< -o $@ $(INCLUDE_PATHS)

CALC_COV_BUILD_DIR = build/test
CALC_COV_SRCS = $(shell find ./models/calculator -name "*.cc")
CALC_COV_OBJS = $(addprefix $(CALC_COV_BUILD_DIR)/,$(notdir $(CALC_COV_SRCS:%.cc=%.o)))

$(CALC_COV_BUILD_DIR)/%.o: models/calculator/%.cc
	$(CXX) -O3 $(CXXFLAGS) --coverage -c $< -o $@ $(INCLUDE_PATHS)

tests: $(TESTS_OBJS) $(CALC_COV_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgcov $(INCLUDE_PATHS)

# Views
VIEW_BUILD_DIR = build/view
VIEW_SRCS = $(shell find ./view/gtk -name "*.cc")
VIEW_OBJS = $(addprefix $(VIEW_BUILD_DIR)/,$(notdir $(VIEW_SRCS:%.cc=%.o)))

$(VIEW_BUILD_DIR)/%.o: view/gtk/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ `pkg-config gtkmm-3.0 --libs --cflags` $(INCLUDE_PATHS)

# Controllers
CNTRL_BUILD_DIR = build/controller
CNTRL_SRCS = $(shell find ./controller -name "*.cc")
CNTRL_OBJS = $(addprefix $(CNTRL_BUILD_DIR)/,$(notdir $(CNTRL_SRCS:%.cc=%.o)))

$(CNTRL_BUILD_DIR)/%.o: controller/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE_PATHS)

# Calculator
build/main.o: main.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ `pkg-config gtkmm-3.0 --libs --cflags` $(INCLUDE_PATHS)

programm.gresource.xml: ui.glade

resources.c: programm.gresource.xml
	glib-compile-resources --target=resources.c --generate-source $^

calculator: build/main.o resources.c $(VIEW_OBJS) $(CNTRL_OBJS) $(CALC_BUILD_DIR)/libcalculator.a $(BANK_BUILD_DIR)/libbank.a
	$(CXX) $(CXXFLAGS) $^ -o $@ `pkg-config gtkmm-3.0 --libs --cflags` $(INCLUDE_PATHS)

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
	@rm -f tests calculator tests.info resources.c
	@rm -rf gcov_report
	@rm -rf src



PROJECT_ROOT_FOLDER := src
PROJECT_FOLDERS := \
	$(PROJECT_ROOT_FOLDER) \
	$(PROJECT_ROOT_FOLDER)/build \
	$(PROJECT_ROOT_FOLDER)/build/bank \
	$(PROJECT_ROOT_FOLDER)/build/calculator \
	$(PROJECT_ROOT_FOLDER)/build/controller \
	$(PROJECT_ROOT_FOLDER)/build/tests \
	$(PROJECT_ROOT_FOLDER)/build/view \
	$(PROJECT_ROOT_FOLDER)/controller \
	$(PROJECT_ROOT_FOLDER)/models \
	$(PROJECT_ROOT_FOLDER)/models/calculator \
	$(PROJECT_ROOT_FOLDER)/models/bank \
	$(PROJECT_ROOT_FOLDER)/test \
	$(PROJECT_ROOT_FOLDER)/view \
	$(PROJECT_ROOT_FOLDER)/view/gtk

dist:
	@for dir in $(PROJECT_FOLDERS); \
		do \
			if [ ! -d $$dir ]; \
			then \
				mkdir $$dir; \
			fi; \
		done;
	@cp ./controller/* ./src/controller/
	@cp ./models/bank/* ./src/models/bank/
	@cp ./models/calculator/* ./src/models/calculator/
	@cp ./test/* ./src/test/
	@cp ./view/gtk/* ./src/view/gtk/
	@cp main.cc Makefile programm.gresource.xml ui.glade ./src/
	@tar -zcf src.tar src
	@gzip src.tar
	@rm -rf src

all: calculator

install: calculator
	@if [ ! -d ../s21_calc ]; \
	then \
		mkdir ../s21_calc; \
	fi;
	@cp calculator ../s21_calc

uninstall:
	@if [ -d ../s21_calc ]; \
	then \
		rm -rf ../s21_calc; \
	fi;

run: calculator
	./calculator

.PHONY: clean dist linter install uninstall all run

-include $(shell find ./build -name "*.d")
