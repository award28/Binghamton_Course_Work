package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for a this expression. */
public class ThisAst extends AbstractExpAst {

  /** Construct an AST for a this expression. */
  public ThisAst(Token thisTok) {
    super("THIS", thisTok);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
