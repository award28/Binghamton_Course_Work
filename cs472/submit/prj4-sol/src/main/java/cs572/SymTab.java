package cs572;

import cs572.AbstractDeclarationAst.Access;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.List;

/* Maintains a mapping between Ids and SymInfos, where Ids are assumed
 * to be strings.  The mapping is scoped.
 *
 * This module provides mechanism, not policy.  In particular, it does
 * not check for duplicate ids being added to the same scope.  It is
 * up to the caller to do such checks.
 */
class SymTab {
  private List<Map<String, List<SymInfo>>> _tables;

  SymTab() {
    _tables = new ArrayList<Map<String, List<SymInfo>>>();
    beginScope();
  }

  /* Return last SymInfo inserted for id.  null if none. */
  SymInfo get(String id)
  {
    for (int i = _tables.size(); i > 0; i--) {
      Map<String, List<SymInfo>> table = _tables.get(i - 1);
      List<SymInfo> infos = table.get(id);
      if (infos != null) return infos.get(infos.size() - 1);
    }
    return null;
  }

  /* Insert symInfo as SymInfo for id in current scope.  No error checking. */
  void put(String id, SymInfo symInfo) {
    Map<String, List<SymInfo>> currentTable = _tables.get(_tables.size() - 1);
    List<SymInfo> entries = currentTable.get(id);
    if (entries  == null) {
      currentTable.put(id, entries = new ArrayList<SymInfo>());
    }
    entries.add(symInfo);
  }

  /* Get current scope level */
  int getScopeLevel() { return _tables.size() - 1; }

  /* Start a new scope. */
  void beginScope() {
    _tables.add(new HashMap<String, List<SymInfo>>());
  }

  /* Forget all symbols added since last beginScope() (assumes there is
   * one).
   */
  void endScope() {
    _tables.remove(_tables.size() - 1);
  }

  /* Return enumeration of all SymInfo's inserted for id, in LIFO order
   * of insertion.
   */
  Enumeration getAll(final String id) {
    class EnumState {
      List entry;       //current entry.
      int tablesIndex;  //index of table containing entry.
      int entryIndex;   //index of next element to be delivered.
      EnumState() {
        tablesIndex = _tables.size(); entry = null; entryIndex = 0;
        advance();
      }
      void advance() {
        entryIndex--;
        if (entryIndex < 0) {
          while (tablesIndex > 0) {
            entry  = _tables.get(--tablesIndex).get(id);
            if (entry != null) {
              entryIndex =  entry.size() - 1;
              break;
            }
          }
        }
      }
    }
    final EnumState enumState = new EnumState();
    return new Enumeration() {
      public boolean hasMoreElements() {
        return enumState.entryIndex >= 0;
      }
      public Object nextElement() {
        Object next  = enumState.entry.get(enumState.entryIndex);
        enumState.advance();
        return next;
      }
    };
  }

  /*
  static public void main(String args[]) {
    SymTab symTab = new SymTab();
    symTab.put("a", new LocalSymInfo("a", Ast.Position.UNKNOWN, "int"));
    symTab.put("a", new MethodSymInfo("a", Ast.Position.UNKNOWN, "int", true,
                                      Access.PUBLIC, new FormalSymInfo[] { }));
    symTab.put("b", new ClassSymInfo("b", Ast.Position.UNKNOWN, "x"));
    symTab.beginScope();
    symTab.put("a", new FormalSymInfo("a", Ast.Position.UNKNOWN, "boolean"));
    symTab.put("b", new LocalSymInfo("b", Ast.Position.UNKNOWN, "int"));
    for (Enumeration e = symTab.getAll("a"); e.hasMoreElements();) {
      System.out.println(e.nextElement().toString());
    }
    for (Enumeration e = symTab.getAll("b"); e.hasMoreElements();) {
      System.out.println(e.nextElement().toString());
    }
    symTab.endScope();
    System.out.println("");
    for (Enumeration e = symTab.getAll("a"); e.hasMoreElements();) {
      System.out.println(e.nextElement().toString());
    }
    for (Enumeration e = symTab.getAll("b"); e.hasMoreElements();) {
      System.out.println(e.nextElement().toString());
    }
    for (Enumeration e = symTab.getAll("c"); e.hasMoreElements();) {
      System.out.println(e.nextElement().toString());
    }
  }
  */
}
