package cs572;

import org.antlr.v4.runtime.Token;

import java.util.List;

/** Abstract Ast for all declarations. */
public abstract class AbstractDeclarationAst extends Ast {

  private final boolean _isStatic;
  private final Access _access;

  protected AbstractDeclarationAst(String rubric, Token t,
                                   List<String> modifiers)
  {
    super(rubric, t);
    StaticAccess staticAccess = getStaticAccess(modifiers);
    _isStatic = staticAccess.isStatic;
    _access = staticAccess.access;
  }

  protected AbstractDeclarationAst(String rubric, Ast t,
                                   List<String> modifiers)
  {
    super(rubric, t);
    StaticAccess staticAccess = getStaticAccess(modifiers);
    _isStatic = staticAccess.isStatic;
    _access = staticAccess.access;
  }

  /** Return true iff this declaration had a static modifier. */
  public boolean isStatic() { return _isStatic; }

  /** Return access modifier for thsi declaration (defaults to PUBLIC) */
  public Access getAccess() { return _access; }

  public static enum Access {
    PRIVATE("private"),
    PROTECTED("protected"),
    PUBLIC("public");
    public final String lexeme;
    Access(String lex) { lexeme = lex; }
  };

  private StaticAccess getStaticAccess(List<String> modifiers) {
    boolean isStatic = modifiers.contains("static");
    Access access;
    if (isStatic) {
      modifiers.remove("static");
    }
    if (modifiers.size() == 0) {
      access = Access.PUBLIC;
    }
    else if (modifiers.size() == 1) {
      access = Access.valueOf(modifiers.get(0).toUpperCase());
    }
    else {
      access = null;
      error("invalid access specifiers %s", modifiers);
    }
    return new StaticAccess(isStatic, access);
  }

  private static class StaticAccess {
    boolean isStatic;
    Access access;
    StaticAccess(boolean isStatic, Access access) {
      this.isStatic = isStatic; this.access = access;
    }
  }

}
