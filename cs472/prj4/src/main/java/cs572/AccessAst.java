package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for field access left.right. */
public class AccessAst extends AbstractExpAst {

  /** Construct an access Ast for left.right.  Token t is used to set the
   *  position and should correspond to the '.' token.
   */
  public AccessAst(Token t, AbstractExpAst left, AbstractExpAst right) {
    super("ACCESS", t);
    addKid(left);
    addKid(right);
  }

  /** Access the LHS Ast of this assignment. */
  public AbstractExpAst getLeft() { return (AbstractExpAst)getKid(0); }

  /** Access the RHS Ast of this assignment. */
  public AbstractExpAst getRight() { return (AbstractExpAst)getKid(1); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
