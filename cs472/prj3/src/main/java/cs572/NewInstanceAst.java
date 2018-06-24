package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for new CLASS constructor-invocation expression. */
public class NewInstanceAst extends AbstractExpAst {

  /** Build Ast for new constructorCall.  Token t used for
   *  setting source position and should correspond to new.
   */
  public NewInstanceAst(Token t, CallAst constructorCall) {
    super("NEW_INSTANCE", t);
    addKid(constructorCall);
  }

  /** Access constructor call for this new invocation. */
  public CallAst getConstructorCall() {
    return (CallAst)getKid(0);
  }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
