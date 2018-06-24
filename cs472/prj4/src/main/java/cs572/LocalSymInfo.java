package cs572;

/** Information associated with a local variable */
class LocalSymInfo extends VarSymInfo implements TypedI {

  private int _offset;          //offset where allocated.

  LocalSymInfo(String id, Ast.Position position, TypeI type, int level) {
    super(id, position, type, level);
    _offset = -1;
  }

  int getOffset() { return _offset; }
  void setOffset(int offset) { _offset = offset; }

  Kind getKind() { return Kind.LOCAL; }

  final static LocalSymInfo ERROR =
    new LocalSymInfo("$error", Ast.Position.UNKNOWN, BasicType.ERROR, 0);

  public String toString() {
    return getType() + " " + getId();
  }

}
