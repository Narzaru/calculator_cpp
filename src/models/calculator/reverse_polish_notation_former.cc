#include "reverse_polish_notation_former.h"

#include <list>
#include <queue>
#include <stack>

#include "token.h"

namespace s21::math {
std::list<MathToken>
ReversePolishNotationFormer::Create(const std::list<MathToken> &tokens) {
  if (!IsValidTokens(tokens)) {
    throw ReversePolishNotationFormerException(
        "list of tokens contains a wrong or empty token");
  }

  [[maybe_unused]] bool error_occurred = false;
  std::list<MathToken> out_tokens;
  std::stack<MathToken> stack;

  for (const MathToken &token : tokens) {
    if (token.IsNumber()) {
      out_tokens.push_back(token);
    } else if (token.IsFunction()) {
      stack.push(token);
    } else if (token.IsOperator()) {
      while (!stack.empty() && stack.top().IsOperator() &&
             ((stack.top().Priority() > token.Priority()) ||
              (token.IsLeftAssociative() &&
               (token.Priority() == stack.top().Priority())))) {
        out_tokens.push_back(std::move(stack.top()));
        stack.pop();
      }
      stack.push(token);
    } else if (token.IsOpenBracket()) {
      stack.push(token);
    } else if (token.IsCloseBracket()) {
      while (!stack.empty() && !stack.top().IsOpenBracket()) {
        out_tokens.push_back(std::move(stack.top()));
        stack.pop();
      }
      if (stack.empty()) {
        error_occurred = true;
      } else {
        stack.pop();
      }
      if (!stack.empty() && (stack.top().IsFunction())) {
        out_tokens.push_back(std::move(stack.top()));
        stack.pop();
      }
    } else {
      error_occurred = true;
    }
  }

  while (!stack.empty() && (stack.top().IsOperator())) {
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

bool ReversePolishNotationFormer::IsValidTokens(
    const std::list<MathToken> &tokens) {
  for (const auto &token : tokens) {
    if (token.IsWrong()) {
      return false;
    }
  }
  return true;
}

} // namespace s21::math
