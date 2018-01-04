package cs572;

import cs572.AbstractDeclarationAst.Access;

import java.util.Enumeration;

/** Class which enforces some of decaf semantics while manipulating
 *  symbol-tables.
 */
class JSymTab {
  private SymTab _classes;              //class definitions.
  private ClassSymTab _currentClass;    //current class.
  private MethodSymInfo _currentMethod; //current method.
  private int _scopeLevel;

  static final ClassSymInfo OBJECT =
    new ClassSymTab("Object", Ast.Position.UNKNOWN,  null);

  static final ClassSymInfo STRING =
    new ClassSymTab("String", Ast.Position.UNKNOWN, OBJECT);

  JSymTab() {
    _classes = new SymTab();
    _currentClass = null; _currentMethod = null;
    _scopeLevel = 0;
    _classes.put("Object", OBJECT);
    _classes.put("String", STRING);
  }

  /* Set the current class to classId (which must have been previously
   * defined).
   */
  void setCurrentClass(String classId, Ast ast) {
    _currentClass = getClassSymTab(classId, ast);
  }

  /* Return SymInfo corresponding to currently set class */
  ClassSymInfo getCurrentClass()  {
    return _currentClass;
  }

  /* Unset the current class */
  void unsetCurrentClass() {
    _currentClass = null;
  }


  /* Set the current method to methodId/arity (which must have been
   * previously defined).  The current class must have been previously set.
   */
  void setCurrentMethod(String methodId, Ast ast) {
    _currentMethod = getMethod(methodId, ast, null);
  }

  /* Return SymInfo corresponding to currently set methodn */
  MethodSymInfo getCurrentMethod() {
    return _currentMethod;
  }

  /* Unset the current method */
  void unsetCurrentMethod() {
    _currentMethod = null;
  }

  /* Start a new scope.  _currentClass must have been previously set. */
  void beginScope() {
    _currentClass.getSymTab().beginScope();
    _scopeLevel++;
  }

  /* End a scope.  _currentClass must have been previously set. */
  void endScope() {
    _currentClass.getSymTab().endScope();
    _scopeLevel--;
  }

  int getLevel() { return _scopeLevel; }


  //                     Add Routines

  // These add routines produce diagnostics on stderr if errors are found.

  /* Add class specified by classId as class with superclass superClassId. */
  ClassSymInfo addClass(String classId, Ast ast, String superClassId) {
    SymInfo symInfo = _classes.get(classId);
    if (symInfo != null) {
      ast.error("multiply defined class %s; previous definition at %s",
                classId, symInfo.getPosition());
      return ClassSymInfo.ERROR;
    }
    else {
      ClassSymInfo superClass = getClass(superClassId, ast);
      if (superClass == null) superClass = OBJECT;
      ClassSymInfo classInfo =
        new ClassSymTab(classId, ast.getPosition(), superClass);
      _classes.put(classId, classInfo);
      return classInfo;
    }
  }

  /* Add field fieldId with type given by typeId and static by isStatic.
   * A current class must be set.
   */
  FieldSymInfo addField(String fieldId, Ast ast, TypeI type, Access access) {
    SymTab classSymTab = _currentClass.getSymTab();
    for (Enumeration e = classSymTab.getAll(fieldId); e.hasMoreElements(); ) {
      SymInfo symInfo = (SymInfo)e.nextElement();
      if (symInfo.getKind() == SymInfo.Kind.FIELD) {
        ast.error("multiply defined field %s; previous definition at %s",
                  fieldId, symInfo.getPosition());
        return FieldSymInfo.ERROR;
      }
    }
    FieldSymInfo fieldInfo =
      new FieldSymInfo(fieldId, ast.getPosition(), type, access);
    classSymTab.put(fieldId, fieldInfo);
    return fieldInfo;
  }

  /* Add method methodId with returnType and formals and isStatic.
   * A current class must be set.
   */
  MethodSymInfo addMethod(String methodId, Ast ast,
                          TypeI returnType, boolean isStatic, Access access) {
    SymTab classSymTab = _currentClass.getSymTab();
    for (Enumeration e = classSymTab.getAll(methodId); e.hasMoreElements(); ) {
      SymInfo symInfo = (SymInfo)e.nextElement();
      if (symInfo.getKind() == SymInfo.Kind.METHOD) {
        ast.error("multiply defined method %s; previous definition at %s",
                  methodId, symInfo.getPosition());
        return MethodSymInfo.ERROR;
      }
    }
    boolean isConstructor =
      returnType == BasicType.NIL && methodId.equals(_currentClass.getId());
    MethodSymInfo methodInfo =
      new MethodSymInfo(methodId, ast.getPosition(), returnType,
                        _currentClass, isStatic, access, isConstructor);
    classSymTab.put(methodId, methodInfo);
    return methodInfo;
  }


  /* Add local localId with type given by typeId; A current method
   * must be set.
   */
  LocalSymInfo addLocal(String localId, Ast ast, TypeI type) {
    return (LocalSymInfo)addVar(localId, ast, type, SymInfo.Kind.LOCAL);
  }

  /* Add formal formalId with type given by type; A current method
   * must be set.
   */
  FormalSymInfo addFormal(String localId, Ast ast, TypeI type) {
    return (FormalSymInfo)addVar(localId, ast, type, SymInfo.Kind.FORMAL);
  }

  private VarSymInfo
    addVar(String varId, Ast ast, TypeI type, SymInfo.Kind kind)
  {
    SymTab classSymTab = _currentClass.getSymTab();
    boolean hasError = false;
    for (Enumeration e = classSymTab.getAll(varId); e.hasMoreElements(); ) {
      SymInfo symInfo = (SymInfo)e.nextElement();
      SymInfo.Kind k = symInfo.getKind();
      if (k == SymInfo.Kind.LOCAL || k == SymInfo.Kind.FORMAL) {
        int level = ((VarSymInfo)symInfo).getScopeLevel();
        if (level == _scopeLevel) {
          ast.error("multiply defined variable %s; previous definition at %s",
                    varId, symInfo.getPosition());
          hasError = true;
          break;
        }
      }
    }
    VarSymInfo varInfo = null;
    boolean isLocal = (kind == SymInfo.Kind.LOCAL);
    if (hasError) {
      varInfo = (isLocal) ? LocalSymInfo.ERROR : FormalSymInfo.ERROR;
    }
    else {
      varInfo = (isLocal)
                ? new LocalSymInfo(varId, ast.getPosition(), type, _scopeLevel)
                : new FormalSymInfo(varId, ast.getPosition(), type, _scopeLevel);
    }
    classSymTab.put(varId, varInfo);
    return varInfo;
  }


  /* Add formals specified by array formals to current scope.  This is
   * typically used in pass 3 (the formals are created in pass 2).
   */
  void addFormals(FormalSymInfo formals[]) {
    SymTab classSymTab = _currentClass.getSymTab();
    for (int i = 0; i < formals.length; i++) {
      FormalSymInfo formal = formals[i];
      classSymTab.put(formal.getId(), formal);
    }
  }

  //                     Get Routines

  // These get routines produce diagnostics on stderr if errors are found.

  private ClassSymTab getClassSymTab(String classId, Ast ast) {
    ClassSymTab symInfo = (ClassSymTab) _classes.get(classId);
    if (symInfo == null) {
      ast.error("undefined class %s", classId);
      return ClassSymTab.ERROR;
    }
    else {
      return symInfo;
    }
  }

  ClassSymInfo getClass(String classId, Ast ast) {
    ClassSymTab symInfo = getClassSymTab(classId, ast);
    return (symInfo == ClassSymTab.ERROR) ? ClassSymInfo.ERROR : symInfo;
  }


  /* Return MethodSymInfo associated with methodId.  Looks it up in
   * class specified by containingClassId if containingClassId !=
   * null.  Otherwise looks it up in the currently set class.  For
   * this routine to be called the current method must be set.
   */
  MethodSymInfo getMethod(String methodId, Ast ast,
                          String containingClassId) {

    String classId = (containingClassId == null) ? _currentClass.getId()
                                                 : containingClassId;
    for (ClassSymTab classSymInfo = getClassSymTab(classId, ast);
         classSymInfo != null;
         classSymInfo = (ClassSymTab)classSymInfo.getSuperClass()) {
      SymTab classSymTab = classSymInfo.getSymTab();
      for (Enumeration e = classSymTab.getAll(methodId); e.hasMoreElements(); ) {
        SymInfo symInfo = (SymInfo)e.nextElement();
        if (symInfo.getKind() == SymInfo.Kind.METHOD) {
          return (MethodSymInfo) symInfo;
        }
      }
    }
    ast.error("cannot find method %s() in class %s", methodId, classId);
    return MethodSymInfo.ERROR;
  }

  /* Return field, local, formal, or class SymVal associated with id.
   * If containgClassId is non-null, it looks it up as a field.  If
   * containingClasslassId is null, it looks it up in order as a
   * local/param, field.  In both cases it goes up the class
   * hierarchy.  If isField is set, then it returns only a field.
   * If all else fails and containingClassId is null, then
   * it looks it up as a class.  For this routine to be called the
   * current method must be set.
   */
  SymInfo getVar(String id, Ast ast, String containingClassId, boolean isField) {
    String classId = (containingClassId == null) ? _currentClass.getId()
                                                 : containingClassId;
    for (ClassSymTab classSymInfo = getClassSymTab(classId, ast);
         classSymInfo != null;
         classSymInfo = (ClassSymTab)classSymInfo.getSuperClass()) {
      SymTab classSymTab = classSymInfo.getSymTab();
      for (Enumeration e = classSymTab.getAll(id); e.hasMoreElements(); ) {
        SymInfo symInfo = (SymInfo)e.nextElement();
        SymInfo.Kind kind = symInfo.getKind();
        boolean isDone =
          isField ? kind == SymInfo.Kind.FIELD
                  : kind == SymInfo.Kind.LOCAL ||
                    kind == SymInfo.Kind.FORMAL ||
                    kind == SymInfo.Kind.FIELD;
        if (isDone) return symInfo;
      }
    }
    SymInfo symInfo = null;
    if (!isField && containingClassId == null) symInfo = _classes.get(id);
    if (symInfo == null) {
      ast.error("undefined %s%s", id,
                (containingClassId == null) ? "" : " in " + containingClassId);
      symInfo = LocalSymInfo.ERROR;
    }
    return symInfo;
  }

  SymInfo getVar(String id, Ast ast, String containingClassId) {
    return getVar(id, ast, containingClassId, false);
  }

  //This class is used to prevent cluttering up ClassSymInfo with a
  //a SymTab; this class will disappear once the tree has been
  //annotated, whereas ClassSymInfo will live on in the annotated
  //AST.
  private static class ClassSymTab extends ClassSymInfo {

    private final SymTab _symTab;

    ClassSymTab(String id, Ast.Position position, ClassSymInfo superClass) {
      super(id, position, superClass);
      _symTab = new SymTab();
    }

    SymTab getSymTab() { return _symTab; }

    final static ClassSymTab ERROR =
      new ClassSymTab("$error", Ast.Position.UNKNOWN, JSymTab.OBJECT);

  }

}
