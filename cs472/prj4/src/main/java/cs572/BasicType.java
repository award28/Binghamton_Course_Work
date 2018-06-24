package cs572;

class BasicType implements TypeI, TypedI {
  private final String _type;

  private BasicType(String type) { _type = type; }

  final static BasicType BOOLEAN =
    new BasicType(PredefType.BOOLEAN.lexeme);
  final static BasicType CHAR =
    new BasicType(PredefType.CHAR.lexeme);
  final static BasicType INT =
    new BasicType(PredefType.INT.lexeme);
  final static BasicType VOID =
    new BasicType(PredefType.VOID.lexeme);

  /** Used as the type for the null literal */
  final static BasicType NULL = new BasicType("$null");

  /** Used to indicate the total absence of a type */
  final static BasicType NIL = new BasicType("$nil");

  /** Used for error types */
  final static BasicType ERROR = new BasicType("$error");

  static boolean isPrimitiveDataType(TypeI type) {
    return type == BOOLEAN || type == CHAR || type == INT;
  }

  static BasicType getType(PredefType type) {
    switch(type) {
    case BOOLEAN:
      return BOOLEAN;
    case CHAR:
      return CHAR;
    case INT:
      return INT;
    case VOID:
      return VOID;
    }
    return null;
  }

  public TypeI getType() { return this; }

  /** Return true iff this is a sub-type of other; i.e., this may be assigned
   *  to other.
   */
  public boolean isSubType(TypeI o) {
    if (this == NIL && o == VOID) {
      return true;
    }
    else if (this == VOID || o == VOID) {
      return false;
    }
    else if (this == ERROR || o == ERROR) {
      return true;
    }
    else if (this == NULL && o instanceof ClassSymInfo) {
      return true;
    }
    else if (this == CHAR && o == INT) {
      return true;
    }
    else {
      return this.equals(o);
    }
  }

  @Override
  public boolean equals(Object o) {
    return (o instanceof BasicType) && ((BasicType)o)._type.equals(_type);
  }

  @Override
  public int hashCode() { return _type.hashCode(); }

  @Override
  public String toString() { return _type; }

}
