package cs572;

import org.antlr.v4.runtime.Token;

/** Ast for a declarator name = initializer */
public class InitDeclaratorAst extends Ast {

  private final String _name;
  private final int _rank;
  private VarSymInfo _varSymInfo;

  /** Construct an AST for name = expr initializer.  None of the arguments
   *  can be null, though initializer may be a NulExpAst.
   */
  public InitDeclaratorAst(Token name, int rank, AbstractExpAst initializer) {
    super("INIT_DECLARATOR", name);
    assert(name != null);
    assert(initializer != null);
    assert(rank >= 0);
    _name = name.getText();
    _rank = rank;
    addKid(initializer);
  }

  /** Return name being declared */
  public String getName() { return _name; }

  /** Return # of dimensions (rank) of name being declared (0 for scalar). */
  public int getRank() { return _rank; }

  /** Return intializer (cannot be null). */
  public AbstractExpAst getInitializer() { return (AbstractExpAst)getKid(0); }

  VarSymInfo getSymInfo() { return _varSymInfo; }
  void setSymInfo(VarSymInfo varSymInfo) { _varSymInfo = varSymInfo; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
