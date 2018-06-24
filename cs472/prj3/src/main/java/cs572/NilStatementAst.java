package cs572;

import org.antlr.v4.runtime.Token;

/** An AST for a missing statement (like the empty statement. */
public class NilStatementAst extends AbstractStatementAst {

  public NilStatementAst(Token t) {
    super("NIL_STATEMENT", t);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
