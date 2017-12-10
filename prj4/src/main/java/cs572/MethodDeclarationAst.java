package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;


public class MethodDeclarationAst extends AbstractDeclarationAst {

  private final String _name;
  private MethodSymInfo _symInfo;

  /** Construct a method declaration for method name with return type
   *  returnType and specified body and modifiers.  None of the arguments
   *  can be null.
   */
  public MethodDeclarationAst(AbstractTypeAst returnType, Token name,
                              List<VarDeclarationAst> formals,
                              BlockAst body, List<String> modifiers)
  {
    super("METHOD", name, modifiers);
    assert(returnType != null);
    assert(name != null);
    assert(formals != null);
    assert(body != null);
    assert(modifiers != null);
    _name = name.getText();
    addKid(returnType);
    for (Ast formal : formals) { addKid(formal); }
    addKid(body);
  }

  /** Return method return type (cannot be null). */
  public AbstractTypeAst getReturnType() { return (AbstractTypeAst) getKid(0); }

  /** Return name which is declared in this declaration (cannot be null). */
  public String getName() { return _name; }

  /** Return list of declarations for all formals for this method. */
  public List<VarDeclarationAst> getFormals() {
    int nFormals = getNKids() - 2;
    List<VarDeclarationAst> formals = new ArrayList<>(nFormals);
    for (int i = 0; i < nFormals; i++) {
      formals.add((VarDeclarationAst)getKid(i + 1));
    }
    return formals;
  }

  /** Return number of formals */
  public int getNFormals() { return getNKids() - 2; }

  /** Return AST for formal at index i (starting with 0).  Cannot be null. */
  public VarDeclarationAst getFormal(int i) {
    return (VarDeclarationAst)getKid(i + 1);
  }

  /** Return method body (cannot be null). */
  public BlockAst getBody() { return (BlockAst)getKid(getNKids() - 1); }

  /** Get sym-info for method id in this declaration */
  MethodSymInfo getSymInfo() { return _symInfo; }

  /** Set sym-info for method id in this declaration */
  void setSymInfo(MethodSymInfo symInfo) { _symInfo = symInfo; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
