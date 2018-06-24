package cs572;

import org.antlr.v4.runtime.Token;

/** An Ast for a return statement with an optional return value. */
public class ReturnAst extends AbstractStatementAst {

  /** Create a Ast for a statement returning value (which cannot be null,
   *  but can be a NilExpAst).
   */
  public ReturnAst(Token t, AbstractExpAst value) {
    super("RETURN", t);
    addKid(value);
  }

  /** Access return value (can be a NilExpAst). */
  public AbstractExpAst getReturnValue() { return (AbstractExpAst)getKid(0); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
