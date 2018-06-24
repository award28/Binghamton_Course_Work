package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for an identifier expression. */
public class NameAst extends AbstractExpAst {

  private final String _name;
  private SymInfo _symInfo;

  /** Construct an AST for identifier name. */
  public NameAst(Token name) {
    super("NAME", name);
    _name = name.getText();
  }

  public String getName() { return _name; }

  SymInfo getSymInfo() { return _symInfo; }

  void setSymInfo(SymInfo symInfo) { _symInfo = symInfo; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
