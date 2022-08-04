#include <algorithm>

#include "lexeme_analyzer.h"

namespace s21 {
namespace math {

bool LexemeAnalyzer::is_didgit(int code) const {
  if (code >= '0' && code <= '9') {
    return true;
  } else {
    return false;
  }
}

// is_number implementation using a state machine idea
bool LexemeAnalyzer::is_number(const std::string &lexeme) const {
  int state = 1;
  for (const char &chr : lexeme) {
    switch (state) {
      case 1:
        if (is_didgit(chr)) {
          state = 1;
        } else if (chr == '.') {
          state = 2;
        } else if (chr == 'e' || chr == 'E') {
          state = 3;
        } else {
          state = 5;
        }
        break;
      case 2:
        if (is_didgit(chr)) {
          state = 2;
        } else if (chr == 'e' || chr == 'E') {
          state = 3;
        } else {
          state = 5;
        }
        break;
      case 3:
        if (is_didgit(chr)) {
          state = 3;
        } else if (chr == '+' || chr == '-') {
          state = 4;
        } else {
          state = 5;
        }
        break;
      case 4:
        if (is_didgit(chr)) {
          state = 4;
        } else {
          state = 5;
        }
        break;
      default:state = 5;
    }
  }
  if (state == 5) {
    return false;
  } else {
    return true;
  }
}

bool LexemeAnalyzer::is_open_bracket(const std::string &lexeme) const {
  if (lexeme.length() == 1 && lexeme[0] == '(') {
    return true;
  } else {
    return false;
  }
}

bool LexemeAnalyzer::is_function(const std::string &lexeme) const {
  for (const std::string &item : functions) {
    if (lexeme == item) {
      return true;
    }
  }
  return false;
}

bool LexemeAnalyzer::is_operator(const std::string &lexeme) const {
  for (const std::string &item : operations) {
    if (lexeme == item) {
      return true;
    }
  }
  return false;
}

bool LexemeAnalyzer::is_close_bracket(const std::string &lexeme) const {
  if (lexeme.length() == 1 && lexeme[0] == ')') {
    return true;
  } else {
    return false;
  }
}

bool LexemeAnalyzer::is_variable(const std::string &lexeme) const {
  if (lexeme.length() == 1 && lexeme[0] == 'x') {
    return true;
  }
  return false;
}

bool LexemeAnalyzer::is_right_associative(const std::string &lexeme) const {
  if (lexeme == "pow" || lexeme == "^") {
    return true;
  }
  return false;
}

}  // namespace math
}  // namespace s21
