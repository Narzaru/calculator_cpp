#include "reverse_polish_notation.h"

#include <list>
#include <queue>
#include <stack>

#include "token.h"
#include "token_analyzer.h"

namespace s21 {
namespace math {
ReversePolishNotation::ReversePolishNotation(const ITokenAnalyzer &analyzer)
    : analyzer_(analyzer) {}

std::list<Token> ReversePolishNotation::create(std::list<Token> tokens) {
  [[maybe_unused]] bool may_unary = true;
  [[maybe_unused]] bool error_occurred = false;
  Token token;
  std::list<Token> out_tokens;
  std::stack<Token> stack;

  for (const Token &token : tokens) {
    if (token == TokenName::kNumber || token == TokenName::kVariable) {
      out_tokens.push_back(std::move(token));
    } else if (token == TokenName::kFunction) {
      stack.push(std::move(token));
    } else if (token == TokenName::kOperator || token == TokenName::kUnary) {
      while (!stack.empty() && stack.top() == TokenName::kOperator &&
             ((is_left_associative(token) &&
               (priority(stack.top()) >= priority(token))) ||
              (is_right_associative(token) &&
               priority(stack.top()) > priority(token)))) {
        out_tokens.push_back(std::move(stack.top()));
        stack.pop();
      }
      stack.push(std::move(token));
    } else if (token == TokenName::kOpenBracket) {
      stack.push(std::move(token));
    } else if (token == TokenName::kCloseBracket) {
      while (!stack.empty() && (stack.top() != TokenName::kOpenBracket)) {
        out_tokens.push_back(std::move(stack.top()));
        stack.pop();
      }
      stack.pop();
      if (stack.empty()) {
        error_occurred = true;
      } else {
        if (stack.top() == TokenName::kFunction) {
          out_tokens.push_back(std::move(stack.top()));
          stack.pop();
        }
      }
    } else {
      error_occurred = true;
    }
  }

  while (!stack.empty() && stack.top() == TokenName::kOperator) {
    out_tokens.push_back(std::move(stack.top()));
    stack.pop();
  }

  if (!stack.empty()) {
    error_occurred = true;
  }

  if (error_occurred) {
    out_tokens.clear();
  }

  return out_tokens;
}

}  // namespace math
}  // namespace s21
