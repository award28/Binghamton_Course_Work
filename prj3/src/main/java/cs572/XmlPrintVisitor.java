package cs572;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/** Visitor for Ast's.  Application of classical visitor pattern. */
public class XmlPrintVisitor extends EmptyVisitor {

  private StringBuilder _buffer;
  private int _indent;

  private static final int INDENT_INC = 2;

  XmlPrintVisitor() {
    _buffer = new StringBuilder("<?xml version=\"1.0\"?>\n");
    _indent = 0;
  }

  public String getXmlPrint() { return _buffer.toString(); }

  private void indent() { _indent += INDENT_INC; }
  private void undent() { _indent -= INDENT_INC; }

  private void doIndent() {
    for (int i = 0; i < _indent; i++) { _buffer.append(" "); }
  }

  private String rubricToTag(String rubric) {
    return rubric.toLowerCase().replaceAll("_", "-");
  }
  private void doAst(Ast t) { doAst(t, Attr.EMPTY_ATTR); }
  private void doAst(Ast t, Attr attr) {
    doIndent();
    _buffer.append("<").append(rubricToTag(t.getRubric()));
    Attr.append("position", t.getPosition().toString(), _buffer);
    Attr.append("type", t.getType().toString(), _buffer);
    attr.append(_buffer);
    if (t.getNKids() == 0) {
      _buffer.append("/>\n");
    }
    else {
      _buffer.append(">\n");
      indent();
      for (Ast kid : t.getKids()) { kid.accept(this); }
      undent();
      doIndent();
      _buffer.append("</").append(rubricToTag(t.getRubric())).append(">\n");
    }
  }

  public void visit(AccessAst ast) { doAst(ast); }
  public void visit(AssignAst ast) { doAst(ast); }
  public void visit(BinaryExpAst ast) {
    doAst(ast, new Attr("op", ast.getOp().toString()));
  }
  public void visit(BlockAst ast) { doAst(ast); }
  public void visit(CallAst ast) {
    Attr attr = new Attr().
      put("name", ast.getName()).
      put(ast.getSymInfo().getAttributes());
    doAst(ast, attr);
  }
  public void visit(ClassAst ast) {
    Attr attr = new Attr().
      put("name", ast.getName()).
      put("super", ast.getSuperClass()).
      put(ast.getSymInfo().getAttributes());
    doAst(ast, attr);
  }
  public void visit(ControlAst ast) { doAst(ast); }
  public void visit(ExpStatementAst ast) { doAst(ast); }
  public void visit(FieldDeclarationAst ast) {
    Attr attr = new Attr().
      put("isStatic", String.valueOf(ast.isStatic())).
      put("access", ast.getAccess().lexeme);
    doAst(ast, attr);
  }
  public void visit(IfAst ast) { doAst(ast); }
  public void visit(IndexAst ast) { doAst(ast); }
  public void visit(InitDeclaratorAst ast) {
    Attr attr = new Attr().
      put("name", ast.getName()).
      put("rank", String.valueOf(ast.getRank())).
      put(ast.getSymInfo().getAttributes());
    doAst(ast, attr);
  }
  public void visit(LiteralAst ast) {
    Attr attr = new Attr().put("value", ast.getLiteral());
    doAst(ast, attr);
  }
  public void visit(MethodDeclarationAst ast) {
    Attr attr = new Attr().
      put("name", ast.getName()).
      put("isStatic", String.valueOf(ast.isStatic())).
      put("access", ast.getAccess().lexeme).
      put(ast.getSymInfo().getAttributes());
    doAst(ast, attr);
  }
  public void visit(NameAst ast) {
    Attr attr = new Attr().
      put("name", ast.getName()).
      put(ast.getSymInfo().getAttributes());
      doAst(ast, attr);
  }
  public void visit(NewArrayAst ast) { doAst(ast); }
  public void visit(NewInstanceAst ast) { doAst(ast); }
  public void visit(NilExpAst ast) { doAst(ast); }
  public void visit(NilStatementAst ast) { doAst(ast); }
  public void visit(ProgramAst ast) { doAst(ast); }
  public void visit(ReturnAst ast) { doAst(ast); }
  public void visit(SuperAst ast) { doAst(ast); }
  public void visit(SuperConsAst ast) { doAst(ast); }
  public void visit(ThisAst ast) { doAst(ast); }
  public void visit(TypeAst ast) {
    Attr attr = new Attr().put("rank", String.valueOf(ast.getRank()));
    doAst(ast, attr);
  }
  public void visit(UnaryExpAst ast) {
    doAst(ast, new Attr("op", ast.getOp().toString()));
  }
  public void visit(VarDeclarationAst ast) { doAst(ast); }
  public void visit(WhileAst ast) { doAst(ast); }

  private static class Attr {
    private final Map<String, String> _attributes;
    Attr() { _attributes = new HashMap<>(); }
    Attr(String name, String value) {
      _attributes = Collections.singletonMap(name, value);
    }
    Attr put(String name, String value) {
      _attributes.put(name, value);
      return this;
    }
    Attr put(List<SymInfo.SymInfoAttr> attributes) {
      for (SymInfo.SymInfoAttr attribute : attributes) {
        _attributes.put(attribute.name, attribute.value);
      }
      return this;
    }
    static void append(String name, String value, StringBuilder b) {
      b.append(" ").append(name).append("=\"");
      b.append(Attr.quote(value)).append("\"");
    }
    public StringBuilder append(StringBuilder b) {
      for (String name : _attributes.keySet()) {
        append(name, _attributes.get(name), b);
      }
      return b;
    }
    private static String quote(String value) {
      return
        value.
        replace("&", "&amp;").
        replace("<", "&lt;").
        replace(">", "&gt;").
        replace("\"", "&quot;");
    }

    private static final Attr EMPTY_ATTR = new Attr();
  }

}
