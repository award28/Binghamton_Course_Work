package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;

/** Ast for a variable declarations. */
class VarDeclarationAst extends AbstractStatementAst {

  /** Create a Ast for a variable declaration having specified type
   *  and initializer.  None of the argument can be null, but
   *  initializer can be a NilExpAst.
   */
  public
    VarDeclarationAst(TypeAst type, List<InitDeclaratorAst> initDeclaratorAsts)
  {
    super("VAR_DEC", type);
    assert(type != null);
    assert(initDeclaratorAsts != null);
    assert(initDeclaratorAsts.size() > 0);
    addKid(type);
    for (InitDeclaratorAst init : initDeclaratorAsts) { addKid(init); }
  }

  /** Return type for declaration (cannot be null). */
  public TypeAst getTypeAst() { return (TypeAst)getKid(0); }

  public InitDeclaratorAst getInitDeclarator(int index) {
    return (InitDeclaratorAst) getKid(index + 1);
  }

  public List<InitDeclaratorAst> getInitDeclarators() {
    int nDeclarators = getNKids() - 1;
    List<InitDeclaratorAst> declarators = new ArrayList<>(nDeclarators);
    for (int i = 0; i < nDeclarators; i++) {
      declarators.add((InitDeclaratorAst)getKid(i + 1));
    }
    return declarators;
  }

  public int getNInitDeclarators() { return getNKids() - 1; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
