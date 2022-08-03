#ifndef __REVERSE_POLISH_NOTATION_H__
#define __REVERSE_POLISH_NOTATION_H__

#include <list>

#include "token.h"

namespace s21 {
class IReversePolishNotation {
 public:
  virtual std::list<Token> create(std::list<Token>) = 0;
  virtual ~IReversePolishNotation() = default;
};

class RPN : public IReversePolishNotation {
  std::list<Token> create(std::list<Token>) override;
  bool is_operator(std::string lexeme);
  bool is_function(std::string lexeme);
};
}  // namespace s21

#endif  // __REVERSE_POLISH_NOTATION_H__
