#include "reverse_polish_notation_former.h"

#include <list>
#include <queue>
#include <stack>

#include "token.h"

namespace s21 {
namespace math {
std::list<Token> ReversePolishNotationFormer::create(std::list<Token> tokens) {
  [[maybe_unused]] bool error_occurred = false;
  std::list<Token> out_tokens;
  std::stack<Token> stack;

  for (const Token &token : tokens) {
    if (token == TokenName::kNumber || token == TokenName::kVariable) {
      out_tokens.push_back(std::move(token));
    } else if (token == TokenName::kFunction) {
      stack.push(std::move(token));
    } else if (token == TokenName::kOperator || token == TokenName::kUnary) {
      while (!stack.empty() && (stack.top() == TokenName::kOperator || stack.top() == TokenName::kUnary) &&
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
      if (stack.empty()) {
        error_occurred = true;
      } else {
        stack.pop();
      }
      if (!stack.empty() && (stack.top() == TokenName::kFunction)) {
        out_tokens.push_back(std::move(stack.top()));
        stack.pop();
      }
    } else {
      error_occurred = true;
    }
  }

  while (!stack.empty() && (stack.top() == TokenName::kOperator || stack.top() == TokenName::kUnary)) {
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
