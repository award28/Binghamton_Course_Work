package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for a if-then-else statement. */
public class IfAst extends AbstractStatementAst {

  /** Construct an Ast for if cond thenPart elsePart.  t should be the
   *  if-token and is merely used to set the source position of this
   *  Ast.  None of cond, thenPart or elsePart can be null, but
   *  thenPart or elsePart can be a NilStatementAst.
   */
  public IfAst(Token t, AbstractExpAst cond,
               AbstractStatementAst thenPart, AbstractStatementAst elsePart)
  {
    super("IF", t);
    addKid(cond);
    addKid(thenPart);
    addKid(elsePart);
  }

  /** Access the condition of this Ast. */
  public AbstractExpAst getCond() { return (AbstractExpAst)getKid(0); }

  /** Return the then-statement for this Ast (can be a NilStatementAst). */
  public AbstractStatementAst getThen() {
    return (AbstractStatementAst)getKid(1);
  }

  /** Return the else-statement for this Ast (can be a NilStatementAst). */
  public AbstractStatementAst getElse() {
    return (AbstractStatementAst)getKid(2);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
