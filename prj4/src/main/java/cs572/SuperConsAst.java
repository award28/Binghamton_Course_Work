package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;

/** An Ast for a call to the super-class constructor. */
public class SuperConsAst extends AbstractStatementAst {

  /** Create a Ast for a statement consisting of call to super constructor
   *  with actual arguments actuals.
   */
  public SuperConsAst(Token t, List<AbstractExpAst> actuals) {
    super("SUPER", t);
    for (Ast ast : actuals) { addKid(ast); }
  }

  /** Access actuals for this super constructor call. */
  public List<AbstractExpAst> getActuals() {
    List<AbstractExpAst> actuals = new ArrayList<>();
    for (Ast ast : getKids()) {
      actuals.add((AbstractExpAst)ast);
    }
    return actuals;
  }

  /** Access AST for actual at index i (starting with 0) */
  public AbstractExpAst getActual(int i) {
    return (AbstractExpAst)getKid(i);
  }

  /** Return number of actual parameters. */
  public int getNActuals() { return getNKids(); }



  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
