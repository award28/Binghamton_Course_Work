package cs572;

import cs572.AbstractDeclarationAst.Access;

/** Information associated with a field */
class FieldSymInfo extends VarSymInfo implements TypedI {

  private final Access _access;

  FieldSymInfo(String id, Ast.Position position, TypeI type, Access access) {
    super(id, position, type, 0);
    _access = access;
  }
  Kind getKind() { return Kind.FIELD; }


  Access getAccess() { return _access; }

  static final FieldSymInfo ERROR =
    new FieldSymInfo("$error", Ast.Position.UNKNOWN, BasicType.ERROR,
                     Access.PUBLIC);

  static final FieldSymInfo LENGTH =
    new FieldSymInfo("length", Ast.Position.UNKNOWN, BasicType.INT,
                     Access.PUBLIC);

  public String toString() {
    StringBuilder b = new StringBuilder();
    b.append(getAccess()).append(" ");
    b.append(getType()).append(" ").append(getId());
    return b.toString();
  }

}
