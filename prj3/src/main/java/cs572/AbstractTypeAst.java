package cs572;

import org.antlr.v4.runtime.Token;

/** Abstract Ast for types. */
public abstract class AbstractTypeAst extends Ast {

  public AbstractTypeAst(String rubric, Token token) { super(rubric, token); }
  public AbstractTypeAst(String rubric, Ast ast) { super(rubric, ast); }

}
