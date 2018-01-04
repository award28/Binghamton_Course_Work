package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for a while statement. */
public class WhileAst extends AbstractStatementAst {

  /** Construct a Ast for a while cond body statement.  Token t (which should
   *  correspond to the WHILE token) is merely used to set the source
   *  position of this Ast.  None of the arguments can be null, but
   *  body can be a NilStatementAst.
   */
  public WhileAst(Token t, AbstractExpAst cond, AbstractStatementAst body) {
    super("WHILE", t);
    assert(t != null);
    assert(cond != null);
    assert(body != null);
    addKid(cond);
    addKid(body);
  }

  /** Access the condition for this while Ast (cannot be null). */
  public AbstractExpAst getCond() { return (AbstractExpAst)getKid(0); }

  /** Access the body of this while Ast (cannot be null, but can be
   *  a NilStatementAst).
   */
  public AbstractStatementAst getBody() {
    return (AbstractStatementAst)getKid(1);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
