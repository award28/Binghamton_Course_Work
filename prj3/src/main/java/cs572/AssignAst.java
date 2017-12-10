package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for assignment expressions. */
public class AssignAst extends AbstractExpAst {

  /** Construct an assignment Ast for left = right.  Token t
   *  is used to set the position and should correspond to the '=' token.
   */
  public AssignAst(Token t, AbstractExpAst left, AbstractExpAst right) {
    super("ASSIGN", t);
    addKid(left);
    addKid(right);
  }

  /** Access the LEFT Ast of this assignment. */
  public AbstractExpAst getLeft() { return (AbstractExpAst)getKid(0); }

  /** Access the RIGHT Ast of this assignment. */
  public AbstractExpAst getRight() { return (AbstractExpAst)getKid(1); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
