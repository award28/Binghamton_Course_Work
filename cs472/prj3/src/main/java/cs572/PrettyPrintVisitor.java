package cs572;

/** Visitor for Ast's.  Application of classical visitor pattern. */
public class PrettyPrintVisitor extends EmptyVisitor {

  private StringBuilder _buffer;
  private int _indent;

  private static final int INDENT_INC = 2;

  PrettyPrintVisitor() {
    _buffer = new StringBuilder();
    _indent = 0;
  }

  public String getPrettyPrint() { return _buffer.toString(); }

  private void indent() { _indent += INDENT_INC; }
  private void undent() { _indent -= INDENT_INC; }

  private void doIndent() {
    for (int i = 0; i < _indent; i++) { _buffer.append(" "); }
  }
  private static final String BEGIN = "BEGIN ";
  private static final String END = "END ";

  private void doBegin(Ast t) { doBegin(t, ""); }
  private void doBegin(Ast t, String format, Object...args) {
    doAst(BEGIN, t, true, format, args);
    doAst(END, t, false, format, args);
  }
  private void doAst(Ast t) { doAst("", t, true, ""); }
  private void doAst(Ast t, String format, Object...args) {
    doAst("", t, true, format, args);
  }
  private void doAst(String start, Ast t, boolean doKids,
                     String format, Object...args)
  {
    doIndent();
    _buffer.append(start).append(t.getRubric());
    _buffer.append("@").append(t.getPosition());
    if (format.length() > 0) {
      _buffer.append(" [");
      _buffer.append(String.format(format, args));
      _buffer.append("]");
    }
    _buffer.append("\n");
    if (doKids) {
      indent();
      for (Ast kid : t.getKids()) { kid.accept(this); }
      undent();
    }
  }

  public void visit(AccessAst ast) { doAst(ast); }
  public void visit(AssignAst ast) { doAst(ast); }
  public void visit(BinaryExpAst ast) { doAst(ast, ast.getOp().toString()); }
  public void visit(BlockAst ast) { doBegin(ast); }
  public void visit(CallAst ast) { doAst(ast, ast.getName()); }
  public void visit(ClassAst ast) {
    doBegin(ast, "%s:%s", ast.getName(), ast.getSuperClass());
  }
  public void visit(ControlAst ast) { doAst(ast); }
  public void visit(ExpStatementAst ast) { doAst(ast); }
  public void visit(FieldDeclarationAst ast) {
    doBegin(ast, "isStatic=%s, access=%s", ast.isStatic(), ast.getAccess());
  }
  public void visit(IfAst ast) { doAst(ast); }
  public void visit(IndexAst ast) { doAst(ast); }
  public void visit(InitDeclaratorAst ast) {
    doAst(ast, doRank(ast.getName(), ast.getRank()));
  }
  public void visit(LiteralAst ast) {
    doAst(ast, "%s: %s", ast.getLiteral(), ast.getPredefType());
  }
  public void visit(MethodDeclarationAst ast) {
    doBegin(ast, "%s: isStatic=%s, access=%s", ast.getName(),
            ast.isStatic(), ast.getAccess());
  }
  public void visit(NameAst ast) { doAst(ast, ast.getName()); }
  public void visit(NewArrayAst ast) { doAst(ast); }
  public void visit(NewInstanceAst ast) { doAst(ast); }
  public void visit(NilExpAst ast) { doAst(ast); }
  public void visit(NilStatementAst ast) { doAst(ast); }
  public void visit(ProgramAst ast) { doBegin(ast); }
  public void visit(ReturnAst ast) { doAst(ast); }
  public void visit(SuperAst ast) { doAst(ast); }
  public void visit(SuperConsAst ast) { doAst(ast); }
  public void visit(ThisAst ast) { doAst(ast); }
  public void visit(TypeAst ast) {
    doAst(ast, doRank(ast.getBaseType(), ast.getRank()));
  }
  public void visit(UnaryExpAst ast) { doAst(ast, ast.getOp().toString()); }
  public void visit(VarDeclarationAst ast) { doAst(ast); }
  public void visit(WhileAst ast) { doAst(ast); }

  private static String doRank(String base, int rank) {
    StringBuilder b = new StringBuilder(base);
    for (int i = 0; i < rank; i++) {
      b.append("[]");
    }
    return b.toString();
  }

}
