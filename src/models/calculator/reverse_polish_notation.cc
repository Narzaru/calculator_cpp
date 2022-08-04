#include "reverse_polish_notation.h"

#include <list>
#include <queue>
#include <stack>

#include "token.h"

namespace s21 {
namespace math {
ReversePolishNotation::ReversePolishNotation(const ILexemeAnalyzer &analyzer)
    : analyzer_(analyzer) {}

std::list<Token> ReversePolishNotation::create(std::list<Token> tokens) {
  [[maybe_unused]] bool may_unary = true;
  Token token;
  std::list<Token> postfix_tokens;
  std::stack<std::string> stack;

  return tokens;
}

}  // namespace math
}  // namespace s21
