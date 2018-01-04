package cs572;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;
import java.util.List;

/** Top-level Ast for a block which consists of a list of statements.
 */
public class BlockAst extends AbstractStatementAst {


  /** Construct a AST for a block containing 0-or-more statements. */
  public BlockAst(Token startToken, List<AbstractStatementAst> statements) {
    super("BLOCK", startToken);
    for (Ast ast : statements) { addKid(ast); }
  }

  /** Return list of all statement AST's in this block. */
  public List<AbstractStatementAst> getStatements() {
    List<AbstractStatementAst> statements = new ArrayList<>();
    for (Ast ast : getKids()) {
      statements.add((AbstractStatementAst)ast);
    }
    return statements;
  }

  /** Return statement at index i (starting with 0). */
  public AbstractStatementAst getStatementAst(int i) {
    return (AbstractStatementAst)getKid(i);
  }

  /** Return # of statements in this block. */
  public int getNStatements() { return getNKids(); }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
