#include <string>
#include <utility>
#include <vector>

namespace s21 {
class ITokenAnalyzer {
 public:
  virtual bool is_didgit(int code) = 0;
  virtual bool is_number(const std::string &lexeme) = 0;
  virtual bool is_open_bracket(const std::string &lexeme) = 0;
  virtual bool is_function(const std::string &lexeme) = 0;
  virtual bool is_operator(const std::string &lexeme) = 0;
  virtual bool is_close_bracket(const std::string &lexeme) = 0;
  virtual bool is_variable(const std::string &lexeme) = 0;
  virtual int get_operator_priority(const std::string &lexeme) = 0;
};

class TokenAnalyzer : public ITokenAnalyzer {
 public:
  bool is_didgit(int code) override;
  bool is_number(const std::string &lexeme) override;
  bool is_open_bracket(const std::string &lexeme) override;
  bool is_function(const std::string &lexeme) override;
  bool is_operator(const std::string &lexeme) override;
  bool is_close_bracket(const std::string &lexeme) override;
  bool is_variable(const std::string &lexeme) override;
  int get_operator_priority(const std::string &lexeme) override;

 private:
  std::vector<std::string> functions = {"cos",  "sin",  "tan", "acos", "asin",
                                        "atan", "sqrt", "ln",  "log"};
  std::vector<std::string> operations = {"+", "-", "*", "/", "^", "mod", "%"};
  std::vector<std::pair<int, std::string>> priorities = {{1, "+"}, {1, "-"}, {2, "*"}, {2, "/"}, {3, "pow"}, {}};
};
}  // namespace s21
