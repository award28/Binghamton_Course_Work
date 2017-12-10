package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for a super expression. */
public class SuperAst extends AbstractExpAst {

  /** Construct an AST for a super expression. */
  public SuperAst(Token superTok) {
    super("SUPER", superTok);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
