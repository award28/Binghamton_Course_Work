package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/** Ast for a field declaration. */
public class FieldDeclarationAst extends AbstractDeclarationAst {

  /** Construct a field declaration Ast declaring field names having
   *  specified type and modifiers.  Neither names nor type can be null;
   *  names should be non-empty.
   */
  public FieldDeclarationAst(TypeAst type,
                             List<InitDeclaratorAst> initDeclaratorAsts,
                             List<String> modifiers)
  {
    super("FIELD", type, modifiers);
    assert(type != null);
    assert(initDeclaratorAsts != null);
    assert(initDeclaratorAsts.size() > 0);
    addKid(type);
    for (InitDeclaratorAst init : initDeclaratorAsts) { addKid(init); }
  }

  /** Return the type AST for this field (cannot be null). */
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
