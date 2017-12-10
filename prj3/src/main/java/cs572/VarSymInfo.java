package cs572;

/** Abstract class used for fields, formals and locals */
abstract class VarSymInfo extends SymInfo implements TypedI {
  private final int _scopeLevel;

  VarSymInfo(String id, Ast.Position position, TypeI type, int scopeLevel) {
    super(id, position, type);
    _scopeLevel = scopeLevel;
  }

  int getScopeLevel() { return _scopeLevel; }

  public String toString() {
    return getId() + ":" + getPosition() + ":" + getType() + ":" + getKind();
  }


}
