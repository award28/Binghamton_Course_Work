import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class Jpp extends DecafBaseListener {
  CommonTokenStream tokens;

  public Jpp(CommonTokenStream tokens) {this.tokens = tokens;}
  private int indent = 0;

  void printIndents() {
    for(int i = 0; i < indent; i++) {
      System.out.print("  ");
    }
  }

  @Override
  public void enterComment(DecafParser.CommentContext ctx) {
    printIndents();
    System.out.println(ctx.COMMENT());
  }

  @Override
  public void enterMethod(DecafParser.MethodContext ctx) {
    printIndents();
  }

  @Override
  public void enterModifier(DecafParser.ModifierContext ctx) {
    System.out.print(ctx.getText() + " ");
  }

  @Override
  public void enterFormalArgs(DecafParser.FormalArgsContext ctx) {
	  ParseTree parent = ctx.getParent();
	  int child = 0;

	  for (int i = 0; i < parent.getChildCount(); i++) {
	    if (!(parent.getChild(i).getText().contains("static")
	     || parent.getChild(i).getText().contains("public")
	     || parent.getChild(i).getText().contains("private") 
	     || parent.getChild(i).getText().contains("protected"))) {
		    child = i;
		    break;
	    }
	  }
	  System.out.print(ctx.getParent().getChild(child).getText() + " (");
  }

  @Override
  public void exitFormalArgs(DecafParser.FormalArgsContext ctx) {
    System.out.print(")");
  }

  @Override
  public void exitFormalArg(DecafParser.FormalArgContext ctx) {
    ParserRuleContext parent = ctx.getParent();
    System.out.print(" " + ctx.varDeclaratorId().getText());
    if (ctx != parent.getChild(parent.getChildCount() - 1))
	    System.out.print(", ");
  }

  @Override
  public void enterStatement(DecafParser.StatementContext ctx) {
    switch(ctx.getStart().getText()) {
      case("if") : 
        printIndents();
	System.out.print("if ");
	break;
      case("while") : 
        printIndents();
	System.out.print("while ");
	break;
      case("return") : 
        printIndents();
	System.out.print("return ");
	break;
      case("continue") :
        printIndents();
	System.out.print("continue\n");
	break;
      case("break") : 
        printIndents();
	System.out.print("break;\n");
	break;
      case("super") : 
        printIndents();
	System.out.print("super ");
	break;
      case(";") : 
	System.out.print(";\n");
	break;
      default :
	  printIndents();
	break;
    }
  }

  @Override
  public void exitStatement(DecafParser.StatementContext ctx) {
    switch(ctx.getStart().getText()) {
      case("while") : 
	System.out.print("while (");
	break;
      case("return") : 
	System.out.print(";\n");
	break;
      case("super") : 
	System.out.print(";\n");
	break;
    }
  }

  @Override
  public void enterEnclosedExpr(DecafParser.EnclosedExprContext ctx) {
	  System.out.print("(");
  }

  @Override
  public void exitEnclosedExpr(DecafParser.EnclosedExprContext ctx) {
	  System.out.print(")");
  }

  @Override
  public void enterType(DecafParser.TypeContext ctx) {
    System.out.print(ctx.getText() + " ");
  }

  @Override
  public void enterLiteral(DecafParser.LiteralContext ctx) {
    System.out.print(ctx.getText());
  }

  @Override
  public void enterUnaryOp(DecafParser.UnaryOpContext ctx) {
    System.out.print(ctx.getText());
  }

  @Override
  public void enterBinaryOp(DecafParser.BinaryOpContext ctx) {
    System.out.print(" " + ctx.getText() + " ");
  }

  @Override
  public void enterE_else(DecafParser.E_elseContext ctx) {
	  printIndents();
	  System.out.println("else");
  }

  @Override
  public void enterC_class(DecafParser.C_classContext ctx) {
    if (ctx.s_super() != null) 
      System.out.println("class " + ctx.ID() + " extends " + ctx.s_super().ID() + " {");
    else
      System.out.println("class " + ctx.ID() + " {");
    indent++;
  }


  @Override
  public void enterVarDeclarator(DecafParser.VarDeclaratorContext ctx) {
   if (ctx.getChildCount() == 1)
     System.out.print(ctx.getStart().getText());
   else
     System.out.print(ctx.getChild(0).getText() + " = ");
  }

  @Override
  public void exitVarDeclarator(DecafParser.VarDeclaratorContext ctx) {
     System.out.print(";\n");
  }

  @Override
  public void enterBlock(DecafParser.BlockContext ctx) {
   System.out.println(" {");
   indent++;
  }
  
  @Override
  public void exitBlock(DecafParser.BlockContext ctx) {
   indent--;
   printIndents();
   System.out.println("}");
  }

  
  @Override
  public void exitC_class(DecafParser.C_classContext ctx) {
   indent--;
   printIndents();
   System.out.println("}");
  }

  public static void main(String[] args) throws Exception {
    ANTLRInputStream input = new ANTLRInputStream(System.in);
    DecafLexer lexer = new DecafLexer(input);
    lexer.removeErrorListeners();
    CountingErrorListener errors = CountingErrorListener.INSTANCE;
    lexer.addErrorListener(errors);
    CommonTokenStream tokens = new CommonTokenStream(lexer);
    DecafParser parser = new DecafParser(tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(errors);

    //
    Jpp listener = new Jpp(tokens); //Jpp must extend DecafBaseListener
    ParseTree tree = parser.start();
    System.out.println(tree.toStringTree(parser));
    ParseTreeWalker walker = new ParseTreeWalker();
    walker.walk(listener, tree);
  }

}
