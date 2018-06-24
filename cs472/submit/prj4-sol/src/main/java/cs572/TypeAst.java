package cs572;

import org.antlr.v4.runtime.Token;

/** Decaf AST types are either a identifier representing a primitive
 *  or class or an array type.
 */
public class TypeAst extends AbstractTypeAst {
  private final String _baseType;
  private final int _rank;
  private final PredefType _primitive;

  TypeAst(Token baseType, int rank) {
    super("TYPE", baseType);
    _baseType = baseType.getText(); _rank = rank;
    PredefType predef = PredefType.lexemeToPredef(_baseType);
    _primitive = (predef != null && predef.isPrimitive) ? predef : null;
  }

  /** Return base-type for this type */
  public String getBaseType() { return _baseType; }

  /** Return # of array dimensions (0 for scalar). */
  public int getRank() { return _rank; }

  /** Return true iff type is an array (rank greater than 0).
   *  Precisely one of isArrayType(), isPrimitiveType() or
   *  isClassType() will return true.
   */
  public boolean isArrayType() { return _rank > 0; }

  /** Return true iff this type represents a primitive.  Precisely one of
   *  isArrayType(), isPrimitiveType() or isClassType() will return
   *  true.
   */
  public boolean isPrimitiveType() { return _rank == 0 && _primitive != null; }

  /** Return true iff this type represents a class type.  Precisely one of
   *  isArrayType(), isPrimitiveType() or isClassType() will return
   *  true.
   */
  public boolean isClassType() { return _rank == 0 && _primitive == null; }

  /** Return PrimitiveType base type if base type is primitive, otherwise
   *  return null.
   */
  public PredefType getPrimitiveBaseType() { return _primitive; }

  /** Accept visitor v. */
  public void accept(AstVisitorI v) { v.visit(this); }

}
