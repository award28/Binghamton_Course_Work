package cs572;

import org.antlr.v4.runtime.Token;

/** Abstract Ast for statements. */
public abstract class AbstractStatementAst extends Ast {

  public AbstractStatementAst(String rubric, Token token) {
    super(rubric, token);
  }
  public AbstractStatementAst(String rubric, Ast ast) { super(rubric, ast); }

}
