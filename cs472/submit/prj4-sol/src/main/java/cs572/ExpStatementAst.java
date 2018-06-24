package cs572;

import org.antlr.v4.runtime.Token;

/** An Ast for an expression statement. */
public class ExpStatementAst extends AbstractStatementAst {

  /** Create a Ast for a statement consisting of exp. */
  public ExpStatementAst(AbstractExpAst exp) {
    super("EXP", exp);
    addKid(exp);
  }

  /** Access expression in this statement. */
  public AbstractExpAst getExp() { return (AbstractExpAst)getKid(0); }


  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
