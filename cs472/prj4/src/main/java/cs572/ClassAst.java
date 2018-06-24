package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;

/** Ast for a class definition. */
public class ClassAst extends Ast {
  private final String _name;
  private final String _superClass;
  private ClassSymInfo _symInfo;

  /** Build Ast for class name, super-class superClass,
   *  and containing declarations. Note of the arguments can be null.
   */
  public ClassAst(Token name, String superClass,
                  List<AbstractDeclarationAst> decls)
  {
    super("CLASS", name);
    _name = name.getText();
    _superClass = superClass;
    for (Ast ast : decls) addKid(ast);
  }


  /** Access class name. */
  public String getName() { return _name; }

  /** Return super-class (cannot be null). */
  public String getSuperClass() { return _superClass; }

  /** Access declarations within class. */
  public List<AbstractDeclarationAst> getDeclarations() {
    List<AbstractDeclarationAst> declarations = new ArrayList<>();
    for (Ast ast : getKids()) {
      declarations.add((AbstractDeclarationAst)ast);
    }
    return declarations;
  }

  /** Return declaration indexed by i (starting with 0). */
  public AbstractDeclarationAst getDeclaration(int i) {
    return (AbstractDeclarationAst)getKid(i);
  }

  /** Return total # of declarations in this AST. */
  public int getNDeclarations() { return getNKids(); }

  ClassSymInfo getSymInfo() { return _symInfo; }
  void setSymInfo(ClassSymInfo symInfo) { _symInfo = symInfo; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
