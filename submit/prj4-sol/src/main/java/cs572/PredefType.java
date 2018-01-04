package cs572;

import java.util.HashMap;
import java.util.Map;

public enum PredefType {
  BOOLEAN("boolean", true),
  CHAR("char", true),
  INT("int", true),
  OBJECT("Object", false),
  STRING("String", false),
  VOID("void", true);

  public final String lexeme;
  public final boolean isPrimitive;

  PredefType(String lexeme, boolean isPrimitive) {
    this.lexeme = lexeme; this.isPrimitive = isPrimitive;
  }

  private static Map<String, PredefType> LEXEME_TO_PREDEF = new HashMap<>();
  static {
    for (PredefType p : PredefType.values()) {
      LEXEME_TO_PREDEF.put(p.lexeme, p);
    }
  }

  public static PredefType lexemeToPredef(String lexeme) {
    return LEXEME_TO_PREDEF.get(lexeme);
  }

  public String toString() { return lexeme; }

}
