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
  private int _formalsLeft = 0;
  private int _numLocals = 0;
  

  CodeGenVisitor(String destDir) {
    _destDir = destDir;
    _labelGen = new LabelGenerator();
    _labels = new LabelStack();
    _loopLabels = new LabelStack();
  }

  private void genDummyCtor() {
	  _jvmGen.add("\n.method public <init>()V");
	  _jvmGen.add("aload 0");
	  _jvmGen.add("invokespecial java/lang/Object/<init>()V");
	  _jvmGen.add("return\n.end method");
  }

  private String getBaseTypeRep(String type) {
	  switch (type) {
		  case "boolean":
		  case "int":
			  return "I";
		  case "float":
			  return "F";
		  case "void":
			  return "V";
		  case "double":
			  return "D";
		  case "long":
			  return "L";
		  case "Char":
			  return "C";
		  default: 
			  return "Ljava/lang/" + type + ";";
	  }
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
	  doAst(ast);
	  if (_ctorNotFound) genDummyCtor();
	  _jvmGen.emit();
	  _ctorNotFound = true;
  }
  public void visit(AccessAst ast) { doAst(ast); }
  public void visit(AssignAst ast) { 
	  doAst(ast); 
  }
  public void visit(BinaryExpAst ast) { 
	  doAst(ast); 
	  System.out.println(ast.getOp());
	  //_jvmGen.add("");
  }
  public void visit(BlockAst ast) { doAst(ast); }
  public void visit(CallAst ast) { 
	  String buf = "invokevirtual "  + _className + "/" + ast.getName() + "(";
	  System.out.println("Calling " + ast.getName());
	  for(AbstractExpAst actual : ast.getActuals()) {
		  if (actual instanceof NameAst) {
			//TODO
		  } else if (actual instanceof LiteralAst) {
  			buf += getBaseTypeRep(((LiteralAst) actual).getPredefType().lexeme);
		  } else if (actual instanceof BinaryExpAst) {
			buf += "I";
		  } else if (actual instanceof CallAst) {
			//TODO
			System.out.println("Actual call type: " + actual.getType());
		  } else if (actual instanceof ThisAst) {
			buf += getBaseTypeRep(_className);
		  } 
	  }
	  buf += ")" + getBaseTypeRep(ast.getType().toString());
	  _jvmGen.add(buf);
	  doAst(ast); 
  }
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
  public void visit(LiteralAst ast) { 
	  if (ast.getLiteral().equals("null")) _jvmGen.add("aconst_null");
	  else if (ast.getPredefType().lexeme.equals("boolean")) {
		 if (ast.getLiteral().equals("true")) _jvmGen.add("iconst_[01]", 1);
		 else _jvmGen.add("iconst_[01]", 0);
	 } 
	 else _jvmGen.add("ldc", ast.getLiteral()); 

	 doAst(ast); 
  }
  public void visit(MethodDeclarationAst ast) { 
	  boolean retVoid = true; 
	  char retType = ' ';
	  int numMax = 1;
	  int backpatchMax;

	  String buf = "\n.method ";
	  if (_className.equals(ast.getName())) {
	  	  _ctorNotFound = false;
		  buf += "public <init>(";
		  for (VarDeclarationAst formal : ast.getFormals()) {
		  	_formalsLeft++;
			numMax++;
			if (formal.getTypeAst().isArrayType()) buf += "[";
  			buf += getBaseTypeRep(formal.getTypeAst().getBaseType());
	  	  }
		  buf += ")V";

	  } else {
	  	  buf += ast.getAccess().lexeme + " ";
		  if (ast.isStatic()) buf += "static ";
		  buf  += ast.getName() + "(";
	
		  for (VarDeclarationAst formal : ast.getFormals()) {
		  	_formalsLeft++;
			numMax++;
			if (formal.getTypeAst().isArrayType()) buf += "[";
  			buf += getBaseTypeRep(formal.getTypeAst().getBaseType());
		  }
		  if (ast.getReturnType() instanceof TypeAst) {
			TypeAst type = (TypeAst) ast.getReturnType();
			retVoid = (type.getBaseType().equals("void"));
		   	buf += ")" + getBaseTypeRep(type.getBaseType());
			if (getBaseTypeRep(type.getBaseType()).length() > 1) 
				retType = 'a';
			else retType = getBaseTypeRep(type.getBaseType()).toLowerCase().charAt(0);

		  } 
		  else 
		   	buf += ")V";
	  }
	  _jvmGen.add(buf);
	  backpatchMax = _jvmGen.add(".limit stack 20");
	  int backpatchLocal = _jvmGen.add(".limit locals " + numMax);
	  doAst(ast); 
	  _jvmGen.backpatch(".limit stack " + (_numLocals + numMax), backpatchMax);
	  _jvmGen.backpatch(".limit locals " + _numLocals, backpatchLocal);
	  _numLocals = 0;
	  if (retVoid) _jvmGen.add("return\n.end method");
	  else {
		  _jvmGen.add(retType + "return\n.end method");
	  }
  }
  public void visit(NameAst ast) { doAst(ast); }
  public void visit(NewArrayAst ast) { doAst(ast); }
  public void visit(NewInstanceAst ast) { 
	  _jvmGen.add("new " + getBaseTypeRep(ast.getType().toString()));
	  doAst(ast); 
  }
  public void visit(NilExpAst ast) { doAst(ast); }
  public void visit(NilStatementAst ast) { doAst(ast); }
  public void visit(NilTypeAst ast) { doAst(ast); }
  public void visit(ReturnAst ast) { doAst(ast); }
  public void visit(SuperAst ast) { doAst(ast); }
  public void visit(SuperConsAst ast) { doAst(ast); }
  public void visit(ThisAst ast) { doAst(ast); }
  public void visit(TypeAst ast) { doAst(ast); }
  public void visit(UnaryExpAst ast) { doAst(ast); }
  public void visit(VarDeclarationAst ast) { 
	  if (_formalsLeft > 0) --_formalsLeft;
	  else {
		_jvmGen.add(".var " + _numLocals++ + " is " + ast.getInitDeclarator(0).getName() + " "
			+ getBaseTypeRep(ast.getTypeAst().getBaseType()) + " from Label1 to Label2");
	  }
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
