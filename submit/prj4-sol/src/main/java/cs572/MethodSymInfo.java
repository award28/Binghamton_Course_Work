package cs572;

import cs572.AbstractDeclarationAst.Access;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/** Information associated with a method. For convenience, the formals
 *  are also accessible here.
 */
class MethodSymInfo extends SymInfo implements TypedI {
  private final ClassSymInfo _declaringClass;
  private final boolean _isStatic;
  private final boolean _isConstructor;
  private final Access _access;
  private final List<FormalSymInfo> _formals;


  MethodSymInfo(String id, Ast.Position position, TypeI returnType,
                ClassSymInfo declaringClass,
                boolean isStatic, Access access, boolean isConstructor)
  {
    super(id, position, returnType);
    _declaringClass = declaringClass;
    _isStatic = isStatic; _access = access;
    _formals = new ArrayList<>();
    _isConstructor = isConstructor;
  }

  TypeI getReturnType() { return getType(); }

  boolean isStatic() { return _isStatic; }

  Access getAccess() { return _access; }

  void addFormal(FormalSymInfo formal) { _formals.add(formal);  }

  List<FormalSymInfo> getFormals() {
    return Collections.unmodifiableList(_formals);
  }

  FormalSymInfo getFormal(int i) { return _formals.get(i); }

  int getNFormals() { return _formals.size(); }

  boolean isConstructor() { return _isConstructor; }

  ClassSymInfo getDeclaringClass() { return _declaringClass; }

  Kind getKind() { return Kind.METHOD; }

  final static MethodSymInfo ERROR =
    new MethodSymInfo("$error", Ast.Position.UNKNOWN, BasicType.ERROR,
                      null, false, Access.PUBLIC, false);

  List<SymInfoAttr> getAttributes() {
    List<SymInfoAttr> attributes = super.getAttributes();
    attributes.addAll(new ArrayList<SymInfoAttr>() {{
          add(new SymInfoAttr("isConstructor", _isConstructor));
        }});
    return attributes;
  }

  public String toString() {
    StringBuilder b = new StringBuilder();
    b.append(getAccess()).append(" ");
    b.append(isStatic() ? "static " : "");
    b.append(getType()).append(" ");
    b.append(getId()).append("(");
    for (int i = 0; i < _formals.size(); i++) {
      if (i > 0) b.append(",");
      b.append(_formals.get(i));
    }
    b.append(")");
    return b.toString();
  }

}
