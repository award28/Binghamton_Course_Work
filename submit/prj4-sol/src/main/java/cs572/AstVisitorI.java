package cs572;

/** Visitor for Ast's.  Application of classical visitor pattern. */
public interface AstVisitorI {
  void visit(AccessAst ast);
  void visit(AssignAst ast);
  void visit(BinaryExpAst ast);
  void visit(BlockAst ast);
  void visit(CallAst ast);
  void visit(ClassAst ast);
  void visit(ControlAst ast);
  void visit(ExpStatementAst ast);
  void visit(FieldDeclarationAst ast);
  void visit(IfAst ast);
  void visit(IndexAst ast);
  void visit(InitDeclaratorAst ast);
  void visit(LiteralAst ast);
  void visit(MethodDeclarationAst ast);
  void visit(NameAst ast);
  void visit(NewArrayAst ast);
  void visit(NewInstanceAst ast);
  void visit(NilExpAst ast);
  void visit(NilStatementAst ast);
  void visit(NilTypeAst ast);
  void visit(ProgramAst ast);
  void visit(ReturnAst ast);
  void visit(SuperAst ast);
  void visit(SuperConsAst ast);
  void visit(ThisAst ast);
  void visit(TypeAst ast);
  void visit(UnaryExpAst ast);
  void visit(VarDeclarationAst ast);
  void visit(WhileAst ast);
}
