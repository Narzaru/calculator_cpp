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
  int state = 0;
  for (const char &chr : lexeme) {
    switch (state) {
      case 0:  // not a number is a error state
        if (is_didgit(chr)) {
          state = 1;
        } else {
          state = 7;
        }
        break;
      case 1:  // number is end state
        if (is_didgit(chr)) {
          state = 1;
        } else if (chr == '.') {
          state = 2;
        } else if (chr == 'E' || chr == 'e') {
          state = 3;
        } else {
          state = 7;
        }
        break;
      case 2:  // dot is end state
          if (is_didgit(chr)) {
            state = 2;
          } else if (chr == 'E' || chr == 'e') {
            state = 3;
          } else {
          state = 7;
        }
        break;
      case 3:  // e or E is error state
          if (is_didgit(chr)) {
            state = 5;
          } else if (chr == '+' || chr == '-') {
            state = 4;
          } else {
          state = 7;
        }
        break;
      case 4:  // e+ or E+ is error state
          if (is_didgit(chr)) {
            state = 6;
          } else {
          state = 7;
        }
        break;
      case 5:  // number is end state
          if (is_didgit(chr)) {
            state = 5;
          } else {
          state = 7;
        }
        break;
      case 6:  // number is end state
          if (is_didgit(chr)) {
            state = 6;
          } else {
          state = 7;
        }
        break;
      case 7:
        break;
    }
  }
  return !(state == 0 || state == 3 || state == 4 || state == 7);
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

}  // namespace math
}  // namespace s21
