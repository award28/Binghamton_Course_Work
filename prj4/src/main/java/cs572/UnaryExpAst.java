package cs572;

import org.antlr.v4.runtime.Token;

import java.util.HashMap;
import java.util.Map;

/** Ast for unary expressions. */
public class UnaryExpAst extends AbstractExpAst {

  private final Op _op;

  /** Build Ast for unary expression  op rand.  Token t used for
   *  setting source position and should correspond to op.
   */
  public UnaryExpAst(Token op, AbstractExpAst rand) {
    super("UNARY_EXP", op);
    _op = OPS.get(op.getText());
    addKid(rand);
  }

  /** Access operator of unary expression. */
  public Op getOp() { return _op; }

  /** Access operand of unary expression. */
  public AbstractExpAst getOperand() { return (AbstractExpAst)getKid(0); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

  public static enum Op { NOT, UMINUS, UPLUS }

  private static Map<String, Op> OPS = new HashMap<String, Op>() {{
      put("!", Op.NOT);
      put("-", Op.UMINUS);
      put("+", Op.UPLUS);
    }};
}
