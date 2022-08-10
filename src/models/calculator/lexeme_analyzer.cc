#include "lexeme_analyzer.h"

#include <algorithm>

namespace s21::math {

bool LexemeAnalyzer::IsDigit(int code) const {
  if (code >= '0' && code <= '9') {
    return true;
  } else {
    return false;
  }
}

// IsNumber implementation using a state machine idea
bool LexemeAnalyzer::IsNumber(const std::string &lexeme) const {
  int state = 0;
  for (const char &chr : lexeme) {
    switch (state) {
      case 0:
        if (IsDigit(chr)) {
          state = 1;
        } else {
          state = 6;
        }
        break;
      case 1:
        if (IsDigit(chr)) {
          state = 1;
        } else if (chr == '.') {
          state = 2;
        } else if (chr == 'e' || chr == 'E') {
          state = 3;
        } else {
          state = 6;
        }
        break;
      case 2:
        if (IsDigit(chr)) {
          state = 2;
        } else if (chr == 'e' || chr == 'E') {
          state = 3;
        }
        break;
      case 3:
        if (IsDigit(chr)) {
          state = 5;
        } else if (chr == '+' || chr == '-') {
          state = 4;
        } else {
          state = 6;
        }
        break;
      case 4:
        if (IsDigit(chr)) {
          state = 5;
        } else {
          state = 6;
        }
        break;
      case 5:
        if (IsDigit(chr)) {
          state = 5;
        } else {
          state = 6;
        }
        break;
      default:break;
    }
  }
  return state == 1 || state == 2 || state == 5;
}

bool LexemeAnalyzer::IsOpenBracket(const std::string &lexeme) const {
  if (lexeme.length() == 1 && lexeme[0] == '(') {
    return true;
  } else {
    return false;
  }
}

bool LexemeAnalyzer::IsFunction(const std::string &lexeme) const {
  for (const std::string &item : functions) {
    if (lexeme == item) {
      return true;
    }
  }
  return false;
}

bool LexemeAnalyzer::IsOperator(const std::string &lexeme) const {
  for (const std::string &item : operators) {
    if (lexeme == item) {
      return true;
    }
  }
  return false;
}

bool LexemeAnalyzer::IsCloseBracket(const std::string &lexeme) const {
  if (lexeme.length() == 1 && lexeme[0] == ')') {
    return true;
  } else {
    return false;
  }
}

bool LexemeAnalyzer::IsVariable(const std::string &lexeme) const {
  if (lexeme.length() == 1 && lexeme[0] == 'x') {
    return true;
  }
  return false;
}

}  // namespace s21
