package cs572;

import org.antlr.v4.runtime.Token;

import java.util.HashMap;
import java.util.Map;

/** Ast for binary expressions. */
public class BinaryExpAst extends AbstractExpAst {

  private final Op _op;

  /** Build Ast for binary expression left op right.
   */
  public BinaryExpAst(Token op, AbstractExpAst left, AbstractExpAst right) {
    super("BINARY_EXP", op);
    _op = OPS.get(op.getText());
    addKid(left);
    addKid(right);
  }

  /** Access operator of binary expression. */
  public Op getOp() { return _op; }

  /** Access left operand of binary expression. */
  public AbstractExpAst getLeft() { return (AbstractExpAst)getKid(0); }

  /** Access right operand of binary expression. */
  public AbstractExpAst getRight() { return (AbstractExpAst)getKid(1); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

  public static enum Op {
    ADD, AND, DIV, EQ, NE, GE, GT, MOD, MUL, OR, LE, LT, SUB
  }

  private static Map<String, Op> OPS = new HashMap<String, Op>() {{
      put("+", Op.ADD);
      put("&&", Op.AND);
      put("/", Op.DIV);
      put("==", Op.EQ);
      put("!=", Op.NE);
      put(">=", Op.GE);
      put(">", Op.GT);
      put("%", Op.MOD);
      put("*", Op.MUL);
      put("||", Op.OR);
      put("<=", Op.LE);
      put("<", Op.LT);
      put("-", Op.SUB);
    }};

}
