package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;

/** Top-level Ast for a program which consists of a list of class
 *  declarations.
 */
public class ProgramAst extends Ast {

  /** Construct a program Ast containing classes. */
  public ProgramAst(List<ClassAst> classes) {
    super("PROGRAM", Position.UNKNOWN);
    for (ClassAst ast : classes) addKid(ast);
  }

  /** Return list of all ClassAst's in this program. */
  public List<ClassAst> getClasses() {
    List<ClassAst> classes = new ArrayList<>();
    for (Ast ast : getKids()) {
      classes.add((ClassAst)ast);
    }
    return classes;
  }

  /** Return class AST at index i (starting with 0). */
  public ClassAst getClass(int i) {
    return (ClassAst)getKid(i);
  }

  /** Return # of class AST's in this program. */
  public int getNClasses() { return getNKids(); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
