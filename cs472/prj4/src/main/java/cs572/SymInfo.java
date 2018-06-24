package cs572;

import java.util.ArrayList;
import java.util.List;

/** Information associated with symbols: this abstract class tracks information
 *  associated with all symbols: the id, source position and type.
 */
abstract class SymInfo implements TypedI {
  private final String _id;             //id corresponding to this SymInfo.
  private final Ast.Position _position; //declaration position of id.
  private TypeI _type;
  SymInfo(String id, Ast.Position position, TypeI type) {
    _id= id; _position= position; _type = type;
  }
  String getId() { return _id; }
  Ast.Position getPosition() { return _position; }

  //hack for ClassSymInfo
  protected void setType(TypeI type) { _type = type; }

  public TypeI getType() { return _type; }

  abstract Kind getKind();

  enum Kind { CLASS, FIELD, FORMAL, LOCAL, METHOD, VAR };

  List<SymInfoAttr> getAttributes() {
    return new ArrayList<SymInfoAttr>() {{
        add(new SymInfoAttr("id", getId()));
        add(new SymInfoAttr("kind", getKind()));
      }};
  }

  static class SymInfoAttr {
    final String name;
    final String value;
    SymInfoAttr(String name, Object value) {
      this.name = name; this.value = value.toString();
    }
  }

}
