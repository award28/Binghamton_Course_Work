package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for array indexing expressions. */
public class IndexAst extends AbstractExpAst {


  /** Construct an assignment Ast for left[right].  Token t
   *  is used to set the position and should correspond to the '[' token.
   */
  public IndexAst(Token t, AbstractExpAst left, AbstractExpAst right) {
    super("INDEX", t);
    addKid(left);
    addKid(right);
  }

  /** Access the left Ast of this index AST. */
  public AbstractExpAst getLeft() { return (AbstractExpAst)getKid(0); }

  /** Access the right Ast of this index AST. */
  public AbstractExpAst getRight() { return (AbstractExpAst)getKid(1); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
