package cs572;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/** Information associated with a class.  For convenience, this class
 *  allows access to the fields and methods of the class.
 *  The constructor will be null if there is no explicit constructor.
 */
class ClassSymInfo extends SymInfo implements TypedI, TypeI {
  private final ClassSymInfo _superClass;
  private final List<FieldSymInfo> _fields;
  private final List<MethodSymInfo> _methods;
  private MethodSymInfo _constructor;

  ClassSymInfo(String id, Ast.Position position, ClassSymInfo superClass) {
    super(id, position, null);
    _superClass = superClass;
    _fields = new ArrayList<>();
    _methods = new ArrayList<>();
    super.setType(this);
  }

  ClassSymInfo getSuperClass() { return _superClass; }

  Kind getKind() { return Kind.CLASS; }

  void addField(FieldSymInfo field) { _fields.add(field);  }
  void addMethod(MethodSymInfo method) { _methods.add(method);  }

  List<FieldSymInfo> getFields() {
    return Collections.unmodifiableList(_fields);
  }

  List<MethodSymInfo> getMethods() {
    return Collections.unmodifiableList(_methods);
  }

  MethodSymInfo getConstructor() { return _constructor; }
  void setConstructor(MethodSymInfo constructor) { _constructor = constructor; }

  /** Return true iff this is a sub-type of other; i.e., this may be assigned
   *  to other.
   */
  public boolean isSubType(TypeI other) {
    if (!(other instanceof ClassSymInfo)) return false;
    String otherId = ((ClassSymInfo)other).getId();
    for (ClassSymInfo c = this; c != null; c = c.getSuperClass()) {
      if (c.getId().equals(otherId)) return true;
    }
    return false;
  }

  final static ClassSymInfo ERROR =
      new ClassSymInfo("$error", Ast.Position.UNKNOWN, JSymTab.OBJECT);

  @Override
  public String toString() { return getId(); }

  @Override
  public boolean equals(Object o) {
    return
      (o instanceof ClassSymInfo) && ((ClassSymInfo)o).getId().equals(getId());
  }

  @Override
  public int hashCode() { return getId().hashCode(); }

  String dump() {
    StringBuilder b = new StringBuilder();
    b.append("ClassSymInfo(name=").append(getId()).append(";");
    b.append("superClass=").append(getSuperClass()).append(";");
    b.append("fields={");
    for (FieldSymInfo field : _fields) {
      b.append(field).append(";");
    }
    b.append("};");
    if (_constructor != null) {
      b.append("constructor={").append(_constructor).append("};");
    }
    b.append("methods={");
    for (MethodSymInfo method : _methods) {
      b.append(method).append(";");
    }
    b.append("};)");
    return b.toString();
  }

}
