package cs572;

import org.antlr.v4.runtime.Token;

/** An AST for a missing expression (like return without a return-value) */
public class NilExpAst extends AbstractExpAst {

  public NilExpAst(Token token) {
    super("NIL_EXP", token);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
