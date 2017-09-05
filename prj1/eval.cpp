#include "eval.h"

#include "lexer.h"


enum State { want_integer, want_operator };

const EvalResult Eval::NextEvalResult() {
  if (token_.kind == TokenKind::nl) {
    return EvalResult({EvalStatus::empty, 0});
  }
  else if (token_.kind == TokenKind::eof) {
    return EvalResult({EvalStatus::eof, 0});
  }
  auto result = 0;
  auto state = State::want_integer;
  auto sign = 1;
  auto is_error = false;  
  while (!is_error && token_.kind != TokenKind::nl
	 && token_.kind != TokenKind::eof) {
    switch (state) {
      case State::want_integer: {
	state = State::want_operator;
	is_error =
	  (token_.kind != TokenKind::integer);
	if (!is_error) result += sign * token_.value;
	break;
      }
      default: {
	state = State::want_integer;
	if (token_.kind == TokenKind::lparen) {
		
	}
	is_error = (token_.kind != TokenKind::add &&
		    token_.kind != TokenKind::sub);
	if (!is_error) {
	  sign = (token_.kind == TokenKind::sub) ? -1 : +1;
	}
	break;
      }
    } //switch
    if (!is_error) token_ = lexer_.NextToken();
  } //while 
  is_error =
    is_error || (state != State::want_operator);
  return is_error
    ?  EvalResult({EvalStatus::error, 0})
    : EvalResult({EvalStatus::ok, result});
}
