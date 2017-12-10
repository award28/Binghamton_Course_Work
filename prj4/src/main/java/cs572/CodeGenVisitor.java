package cs572;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

class CodeGenVisitor extends EmptyVisitor implements AstVisitorI {

  /** Directory where jasmin files generated */
  private final String _destDir;

  /** Use for generating labels */
  private final LabelGenerator _labelGen;

  /** Stack used for tracking current false/true labels for current visit */
  private final LabelStack _labels;

  /** Stack used for tracking current false/true labels for loops */
  private final LabelStack _loopLabels;

  /** Generator for a class; create at start of class visit and emit
   *  code at end of class visit.
   */
  private JvmGen _jvmGen = null;
  private String _className = "";
  private boolean _ctorNotFound = true;

  CodeGenVisitor(String destDir) {
    _destDir = destDir;
    _labelGen = new LabelGenerator();
    _labels = new LabelStack();
    _loopLabels = new LabelStack();
  }

  private void genDummyCtor() {
	  _jvmGen.add(".method public <init>()V");
	  _jvmGen.add("aload 0");
	  _jvmGen.add("invokespecial java/lang/Object/<init>()V");
	  _jvmGen.add("return");
	  _jvmGen.add(".end method");
  }

  private String getBaseTypeRep(String type) {
	  switch (type) {
		  case "int":
			  return "I";
		  case "float":
			  return "F";
		  case "String":
			  return "Ljava/lang/String;";
		  case "void":
			  return "V";
	  }
	return "";
  }

  public void doAst(Ast t) {
	  for(Ast kid : t.getKids()) { kid.accept(this); }
  }
  public void visit(ProgramAst ast) {
	  doAst(ast);
  }
  public void visit(ClassAst ast) {
	  _jvmGen = new JvmGen(_destDir, ast.getName());
	  _className = ast.getName();
	  System.out.println("Class name: " + _className);
	  doAst(ast);
	  if (_ctorNotFound) genDummyCtor();
	  _jvmGen.emit();
	  _ctorNotFound = true;
  }
  public void visit(AccessAst ast) { doAst(ast); }
  public void visit(AssignAst ast) { 
	  doAst(ast); 
  }
  public void visit(BinaryExpAst ast) { doAst(ast); }
  public void visit(BlockAst ast) { doAst(ast); }
  public void visit(CallAst ast) { doAst(ast); }
  public void visit(ControlAst ast) { doAst(ast); }
  public void visit(ExpStatementAst ast) { doAst(ast); }
  public void visit(IfAst ast) {
	  //_jvmGen.add("if");
	doAst(ast);
  }
  public void visit(FieldDeclarationAst ast) { 
	  String buf = ".field " + ast.getAccess().lexeme + " " + ast.getType() + " ";
	  if (ast.getNInitDeclarators() == 1) _jvmGen.add(buf + ast.getInitDeclarator(0).getName());
  	  else {
	  for(InitDeclaratorAst init : ast.getInitDeclarators())
		  _jvmGen.add(buf + init.getName());
	  }
	  doAst(ast); 
  }
  public void visit(IndexAst ast) { doAst(ast); }
  public void visit(InitDeclaratorAst ast) { doAst(ast); }
  public void visit(LiteralAst ast) { doAst(ast); }
  public void visit(MethodDeclarationAst ast) { 
	  /*
	  boolean retVoid = true; 
	  String buf = ".method ";
	  if (_className.equals(ast.getName())) {
	  	  _ctorNotFound = false;
		  buf += "public <init>(";
		  for (VarDeclarationAst formal : ast.getFormals()) {
  			buf += getBaseTypeRep(formal.getTypeAst().getBaseType());
	  	  }
		  buf += ")V";

	  } else {
	  	  buf += ast.getAccess().lexeme + " ";
		  if (ast.isStatic()) buf += "static ";
		  buf  += ast.getName() + " (";
	
		  for (VarDeclarationAst formal : ast.getFormals()) {
  			buf += getBaseTypeRep(formal.getTypeAst().getBaseType());
		  }
		  if (ast.getReturnType() instanceof TypeAst) {
			TypeAst type = (TypeAst) ast.getReturnType();
			retVoid = (type.getBaseType().equals("void"));
		   	buf += ")" + getBaseTypeRep(type.getBaseType());
		  } 
		  else 
		   	buf += ")V";
		  System.out.println(buf);
	  }
	  _jvmGen.add(buf);
	  */
	  doAst(ast); 
	  /*
	  if (_className.equals(ast.getName())) _jvmGen.add("invokespecial java/lang/Object/<init>()V");
	  if (retVoid) _jvmGen.add("return");
	  _jvmGen.add(".end method");
	  */
  }
  public void visit(NameAst ast) { doAst(ast); }
  public void visit(NewArrayAst ast) { doAst(ast); }
  public void visit(NewInstanceAst ast) { doAst(ast); }
  public void visit(NilExpAst ast) { doAst(ast); }
  public void visit(NilStatementAst ast) { doAst(ast); }
  public void visit(NilTypeAst ast) { doAst(ast); }
  public void visit(ReturnAst ast) { 
	  doAst(ast); }
  public void visit(SuperAst ast) { doAst(ast); }
  public void visit(SuperConsAst ast) { doAst(ast); }
  public void visit(ThisAst ast) { doAst(ast); }
  public void visit(TypeAst ast) { doAst(ast); }
  public void visit(UnaryExpAst ast) { doAst(ast); }
  public void visit(VarDeclarationAst ast) { 
	  doAst(ast); 
  }
  public void visit(WhileAst ast) { doAst(ast); }

  private static class LabelGenerator {
    private int labelN = 1;
    Integer next() { return new Integer(labelN++); }
  }

  private static class LabelStack {
    private Stack<Integer> _trueLabels = new Stack<Integer>();
    private Stack<Integer> _falseLabels = new Stack<Integer>();
    Integer peekTrue() { return _trueLabels.peek(); }
    Integer peekFalse() { return _falseLabels.peek(); }
    void push(Integer trueLabel, Integer falseLabel) {
      _trueLabels.push(trueLabel); _falseLabels.push(falseLabel);
    }
    void push(Integer label) { push(label, label); }
    void pop() { _trueLabels.pop(); _falseLabels.pop(); }
  }
}
