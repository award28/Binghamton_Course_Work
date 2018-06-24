package cs572;

import java.util.Objects;

class ArrayType implements TypeI, TypedI {
  private final TypeI _baseType;
  private final int _rank;

  ArrayType(TypeI baseType, int rank) {
    assert(rank > 0);
    _baseType = baseType; _rank = rank;
  }

  TypeI getBaseType() { return _baseType; }
  int getRank() { return _rank; }

  public TypeI getType() { return this; }

  /** Return type of this with rank reduced by 1 */
  public TypeI getResultType() {
    return (_rank == 1) ?  _baseType : new ArrayType(_baseType, _rank - 1);
  }

  public boolean isSubType(TypeI o) {
    return o == BasicType.ERROR || this.equals(o);
  }

  public boolean equals(Object o) {
    if (!(o instanceof ArrayType)) {
      return false;
    }
    ArrayType other = (ArrayType)o;
    return _baseType.equals(other._baseType) && _rank == other._rank;
  }

  public int hashCode() {
    return Objects.hash(_baseType, _rank);
  }

  public String toString() {
    StringBuilder b = new StringBuilder();
    b.append(_baseType);
    for (int i = 0; i < _rank; i++) {
      b.append("[]");
    }
    return b.toString();
  }

}
