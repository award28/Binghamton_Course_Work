package cs572;

import org.antlr.v4.runtime.Token;

/** Abstract Ast for statements. */
public abstract class AbstractExpAst extends Ast {

  public AbstractExpAst(String rubric, Token token) { super(rubric, token); }
  public AbstractExpAst(String rubric, Ast ast) { super(rubric, ast); }

}
