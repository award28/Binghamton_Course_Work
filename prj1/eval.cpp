#include "eval.h"
#include "lexer.h"

const EvalResult Eval::NextEvalResult() {
  if (token_.kind == TokenKind::nl) {
    return EvalResult({EvalStatus::empty, 0});
  }
  else if (token_.kind == TokenKind::eof) {
    return EvalResult({EvalStatus::eof, 0});
  }

  //recursion
  return this->Rec(0);
}

const EvalResult Eval::Rec(int stackCount) {
  auto result = 0;
  while (token_.kind != TokenKind::nl && token_.kind != TokenKind::eof) {
     switch (state_) {
      case State::want_integer: {
        if (token_.kind == TokenKind::lparen) {
	  auto outerSign = sign_;
	  sign_ = 1;
          token_ = lexer_.NextToken();
	  auto innerRes = this->Rec(stackCount + 1);
          auto is_error = innerRes.status != EvalStatus::ok;
	  if (!is_error) {
             result += outerSign * innerRes.result;
	  }
	  else
            return EvalResult({EvalStatus::error, 0});
	}
	else if (token_.kind == TokenKind::rparen) {
            return EvalResult({EvalStatus::error, 0});
	}
	else {
	  state_ = State::want_operator;
	  if (token_.kind == TokenKind::integer) 
	    result += sign_ * token_.value;
	  else
            return EvalResult({EvalStatus::error, 0});
	}
	break;
      }
      default: {
	if (token_.kind == TokenKind::rparen) {
            state_ = State::want_operator;
	    if (stackCount > 0) 
              return EvalResult({EvalStatus::ok, result});
	    else
              return EvalResult({EvalStatus::error, 0});
	}
	
	state_ = State::want_integer;

        if (token_.kind == TokenKind::add || token_.kind == TokenKind::sub)
	  sign_ = (token_.kind == TokenKind::sub) ? -1 : +1;
	else
            return EvalResult({EvalStatus::error, 0});
	}
    }
    token_ = lexer_.NextToken();
  }

  return (stackCount != 0)
    ? EvalResult({EvalStatus::error, 0})
    : EvalResult({EvalStatus::ok, result});
}
