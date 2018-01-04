package cs572;

/** Visitor for Ast's.  Application of classical visitor pattern.
 *  Implementation which does nothing when visition each AST.
 */
public class EmptyVisitor implements AstVisitorI {
  public void visit(AccessAst ast) { }
  public void visit(AssignAst ast) { }
  public void visit(BinaryExpAst ast) { }
  public void visit(BlockAst ast) { }
  public void visit(CallAst ast) { }
  public void visit(ClassAst ast) { }
  public void visit(ControlAst ast) { }
  public void visit(ExpStatementAst ast) { }
  public void visit(FieldDeclarationAst ast) { }
  public void visit(IfAst ast) { }
  public void visit(IndexAst ast) { }
  public void visit(InitDeclaratorAst ast) { }
  public void visit(LiteralAst ast) { }
  public void visit(MethodDeclarationAst ast) { }
  public void visit(NameAst ast) { }
  public void visit(NewArrayAst ast) { }
  public void visit(NewInstanceAst ast) { }
  public void visit(NilExpAst ast) { }
  public void visit(NilStatementAst ast) { }
  public void visit(NilTypeAst ast) { }
  public void visit(ProgramAst ast) { }
  public void visit(ReturnAst ast) { }
  public void visit(SuperAst ast) { }
  public void visit(SuperConsAst ast) { }
  public void visit(ThisAst ast) { }
  public void visit(TypeAst ast) { }
  public void visit(UnaryExpAst ast) { }
  public void visit(VarDeclarationAst ast) { }
  public void visit(WhileAst ast) { }
}
