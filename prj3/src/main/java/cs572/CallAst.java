package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;

/** An application of an expression which represents a function call to a
 *  list of arguments.
 */
public class CallAst extends AbstractExpAst {

  private final String _name;
  private MethodSymInfo _symInfo;

  /** Construct an AST for calling name. */
  public CallAst(Token name, List<AbstractExpAst> actuals) {
    super("CALL", name);
    _name = name.getText();
    for (Ast ast : actuals) { addKid(ast); }
  }

  /** Access Ast for method used in application. */
  public String getName() { return _name; }

  /** Access actuals for this function call. */
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

  /** Get sym-info for method id in this call */
  MethodSymInfo getSymInfo() { return _symInfo; }

  /** Set sym-info for method id in this call */
  void setSymInfo(MethodSymInfo symInfo) { _symInfo = symInfo; }

  /** Accept visitor. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
