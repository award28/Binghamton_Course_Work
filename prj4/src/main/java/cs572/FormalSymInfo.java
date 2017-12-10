package cs572;

/** Information associated with a function formal */
class FormalSymInfo extends VarSymInfo implements TypedI {

  private int _offset;          //offset where allocated.

  FormalSymInfo(String id, Ast.Position position, TypeI type, int level) {
    super(id, position, type, level);
    _offset = -1;
  }

  int getOffset() { return _offset; }
  void setOffset(int offset) { _offset = offset; }

  Kind getKind() { return Kind.FORMAL; }

  final static FormalSymInfo ERROR =
    new FormalSymInfo("$error", Ast.Position.UNKNOWN, BasicType.ERROR, 0);

  public String toString() {
    return getType() + " " + getId();
  }

}
