#include "lexical_analyzer.h"

#include <algorithm>
#include <cstddef>

#include "token.h"
#include "syntactical_analyzer.h"

namespace s21::math {

const std::array<std::string_view, 11> LexicalAnalyzer::delimiters(
    {" ", "(", ")", "+", "-", "*", "/", "^", "%", "mod", "pow"});

std::list<std::string> LexicalAnalyzer::ParseString(string expression) {
  list<string> lexemes;
  ClearSpaces(&expression);

  size_type sequence_length = 0;
  for (size_type i = 0; i < expression.length(); i += sequence_length) {
    if (IsDelimiter(expression, i)) {
      sequence_length = GetDelimiterLength(expression, i);
    } else {
      sequence_length = GetSequenceLength(expression, i);
    }
    const string &str_lexeme = expression.substr(i, sequence_length);
    lexemes.emplace_back(str_lexeme);
  }

  return lexemes;
}

void LexicalAnalyzer::ClearSpaces(string *expr_str) {
  auto string_begin = std::remove(expr_str->begin(), expr_str->end(), ' ');
  auto string_end = expr_str->end();
  expr_str->erase(string_begin, string_end);
}

bool LexicalAnalyzer::IsDelimiter(const string &expr_str, size_type position) {
  for (const auto &delim : delimiters) {
    if (expr_str.length() - position >= delim.length()) {
      if (expr_str.find(delim, position) == position) {
        return true;
      }
    }
  }
  return false;
}

std::size_t LexicalAnalyzer::GetDelimiterLength(const string &string,
                                                size_type position) {
  std::basic_string<char> previous_character;
  for (const auto &delim : delimiters) {
    if (string.length() - position >= delim.length()) {
      if (string.find(delim, position) == position) {
        return delim.length();
      }
    }
  }
  return 0;
}

std::size_t LexicalAnalyzer::GetSequenceLength(const string &string,
                                               size_type position) {
  size_type length = 0;
  char previous_character = string[position];

  while ((!IsDelimiter(string, position) || previous_character == 'e')
      && position < string.length()) {
    previous_character = string[position];
    ++position;
    ++length;
  }
  return length;
}

}  // namespace s21::math
