#ifndef EVAL_H_
#define EVAL_H_

#include "lexer.h"

enum class EvalStatus {
  ok, empty, error, eof
};

enum State { want_integer, want_operator };

struct EvalResult {
  const EvalStatus status;
  const int result;
};

struct RecursionResult {
  const Token token;
  const EvalResult evalResult;
};

class Eval {
 public:
  Eval(Lexer& lexer) :
    lexer_(lexer), token_(lexer.NextToken()), state_(State::want_integer), sign_(1) {}
  const EvalResult NextEvalResult();
  const EvalResult Rec(int stackCount);
 private:
  Lexer &lexer_;
  Token token_;       //lookahead token
  State state_;
  int sign_;
};

#endif //ifndef EVAL_H_
