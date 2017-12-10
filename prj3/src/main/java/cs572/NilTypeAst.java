package cs572;

import org.antlr.v4.runtime.Token;

/** An AST for a missing types (like return type of a constructor) */
public class NilTypeAst extends AbstractTypeAst {

  public NilTypeAst(Token token) {
    super("NIL_TYPE", token);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
