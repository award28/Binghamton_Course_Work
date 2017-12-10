package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;

/** Ast for new Type[exp][exp]... array-construction expression. */
public class NewArrayAst extends AbstractExpAst {

  /** Build Ast for new Type[size][size]...[size].  Token t used for
   *  setting source position and should correspond to new.
   */
  public NewArrayAst(Token t, TypeAst baseType, List<AbstractExpAst> sizes) {
    super("NEW_ARRAY", t);
    addKid(baseType);
    for (Ast ast : sizes) { addKid(ast); }
  }

  /** Return base type of array being constructed. */
  public TypeAst getBaseType() { return (TypeAst)getKid(0); }

  /** Return list of AST's for array sizes. */
  public List<AbstractExpAst> getSizes() {
    int rank = getNKids() - 1;
    List<AbstractExpAst> sizes = new ArrayList<>(rank);
    for (int i = 0; i < rank; i++) {
      sizes.add((AbstractExpAst)getKid(i + 1));
    }
    return sizes;
  }

  /** Return i'th size ast (starting with index 0). */
  public AbstractExpAst getSizeAst(int i) {
    return (AbstractExpAst)getKid(i + 1);
  }

  /** Return number of dimensions for array being constructed. */
  public int getRank() { return getNKids() - 1; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
