#ifndef SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_
#define SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_

#include <vector>

#include "token.h"

#include "token_analyzer.h"

class IMathTokenCompiler {
 public:
  virtual TokenName get_token_name(const std::string &lexeme) = 0;
};

class MathTokenCompiler : public IMathTokenCompiler {
 public:
  explicit MathTokenCompiler(s21::ITokenAnalyzer &token_analyzer);
  TokenName get_token_name(const std::string &lexeme) override;
 private:
  s21::ITokenAnalyzer &token_analyzer_;
};

#endif  // SRC_MODELS_CALCULATOR_TOKEN_COMPILER_H_
