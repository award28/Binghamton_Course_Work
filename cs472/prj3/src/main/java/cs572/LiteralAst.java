package cs572;

import org.antlr.v4.runtime.Token;

/** Ast represeting a constant literal like an integer, true, false or
 *  null.
 */
public class LiteralAst extends AbstractExpAst {

  private final String _value;
  private final PredefType _type;

  /** Build a literal Ast for t having specified type ("int", "boolean",
   *  "char").
   */
  public LiteralAst(Token t, PredefType type) {
    super("LITERAL", t);
    _value = t.getText(); _type = type;
  }

  /** Access literal value. */
  public String getLiteral() { return _value; }

  /** Access type of literal. */
  public PredefType getPredefType() { return _type; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
