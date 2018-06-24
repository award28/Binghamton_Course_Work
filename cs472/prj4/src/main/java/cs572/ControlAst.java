package cs572;

import org.antlr.v4.runtime.Token;

/** AST representing a control statement like break or continue. */
public class ControlAst extends AbstractStatementAst {
  private final Control _control;

  /** Construct control AST.  t should be set to break/continue token. */
  public ControlAst(Token t) {
    super("CONTROL", t);
    _control = Control.valueOf(t.getText().toUpperCase());
  }

  /** Return enum containing BREAK or CONTINUE. */
  public Control getControl() { return _control; }

  /** Accept visitor. */
  public void accept(AstVisitorI v) { v.visit(this); }

  public static enum Control { BREAK, CONTINUE };

}
