package cs572;

import static cs572.AbstractDeclarationAst.Access.PUBLIC;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.HashMap;

/** Visitor which checks decaf semantics */
class JCheckVisitor extends EmptyVisitor implements AstVisitorI {

  /* Makes 3 passes (tracked using _passIndex).  In the first pass,
     it merely visits top-level classes.  In the 2nd pass, it visits
     field and method declarations but does not go into method bodies.
     In the third pass, it processes the entire AST and annotates it.
   */

  private final JSymTab _jSymTab;
  private int _passIndex;
  private int _whileLevel;
  private List<ClassSymInfo> _classesWithMain;
  private final boolean _doDebug = false;

  JCheckVisitor() {
    _jSymTab = new JSymTab();
    _passIndex = -1;
    _whileLevel = 0;
    _classesWithMain = new ArrayList<>();
  }

  /*       Visitor Functions Ordered Alphabetically */

  public void visit(AccessAst ast) {
    assert(_passIndex == 2);
    AbstractExpAst left = ast.getLeft();
    AbstractExpAst right = ast.getRight();
    left.accept(this);
    TypeI leftType = left.getType();
    if (leftType instanceof ArrayType) {
      if (!(right instanceof NameAst) ||
          !"length".equals(((NameAst)right).getName())) {
        ast.error("only accessor for array is length");
      }
      else {
        ((NameAst)right).setSymInfo(FieldSymInfo.LENGTH);
      }
      ast.setType(BasicType.INT);
    }
    else if (!(leftType instanceof ClassSymInfo)) {
      if (leftType != BasicType.ERROR) {
        ast.error("%s is not a class type", leftType);
      }
      ast.setType(BasicType.ERROR);
    }
    else {
      ClassSymInfo leftClass = (ClassSymInfo)leftType;
      if (right instanceof CallAst) {
        CallAst callAst = (CallAst)right;
        String name = callAst.getName();
        MethodSymInfo method = _jSymTab.getMethod(name, ast, leftClass.getId());
        if (left instanceof NameAst) { //hack to check static call error
          String leftName = ((NameAst)left).getName();
          if (leftName.equals(leftClass.getId()) && !method.isStatic()) {
            ast.error("attempt to call a instance method %s as static " +
                      "method of class %s", name, leftName);
          }
        }
        checkMethodCall(callAst, callAst.getActuals(), method);
        callAst.setSymInfo(method);
        ast.setType(method.getReturnType());
      }
      else {
        assert(right instanceof NameAst);
        NameAst nameAst = (NameAst)right;
        String name = nameAst.getName();
        if (left instanceof NameAst) {
          String leftName = ((NameAst)left).getName();
          if (leftName.equals(leftClass.getId())) {
            ast.error("attempt to access a non-static field %s as static " +
                      "field of class %s", name, leftName);
          }
        }
        SymInfo nameSymInfo =
          _jSymTab.getVar(name, ast, leftClass.getId(), true);
        if (nameSymInfo instanceof FieldSymInfo) {
          FieldSymInfo field = (FieldSymInfo) nameSymInfo;
          ((NameAst)right).setSymInfo(field);
          right.setType(field.getType());
          ast.setType(field.getType());
        }
        else {
          //getVar() would have reported missing field error
        }
      }
    }
  }

  public void visit(AssignAst ast) {
    assert(_passIndex == 2);
    AbstractExpAst left = ast.getLeft();
    AbstractExpAst right = ast.getRight();
    left.accept(this); right.accept(this);
    TypeI leftType = left.getType();
    TypeI rightType = right.getType();
    if (!rightType.isSubType(leftType)) {
      ast.error("%s may not be assigned to %s", rightType, leftType);
    }
    if (!(left instanceof NameAst) && !(left instanceof AccessAst) &&
        !(left instanceof IndexAst)) {
      ast.error("invalid lvalue in assignment");
    }
    ast.setType(rightType);
  }

  public void visit(BinaryExpAst ast) {
    assert(_passIndex == 2);
    BinaryExpAst.Op op = ast.getOp();
    AbstractExpAst left = ast.getLeft();
    AbstractExpAst right = ast.getRight();
    left.accept(this); right.accept(this);
    TypeI leftType = left.getType();
    TypeI rightType = right.getType();
    TypeI resultType = checkBinaryOp(ast, op, leftType, rightType);
    ast.setType(resultType);
  }

  public void visit(BlockAst ast) {
    _jSymTab.beginScope();
    MethodSymInfo method = _jSymTab.getCurrentMethod();
    boolean isConstructor = method.isConstructor();
    MethodSymInfo superCons =
      _jSymTab.getCurrentClass().getSuperClass().getConstructor();
    int superConsArity = (superCons == null) ? 0 : superCons.getNFormals();
    int nStatements = ast.getNStatements();
    boolean isTopLevelBlock = (_jSymTab.getLevel() == 2);
    TypeI retType = method.getReturnType();
    boolean needsReturn =
      isTopLevelBlock && retType != BasicType.VOID && retType != BasicType.NIL;
    if (needsReturn && nStatements == 0) {
      ast.error("missing return statement at end of function");
    }
    if (nStatements == 0 && isTopLevelBlock && isConstructor &&
        superConsArity > 0) {
        ast.error("missing call to super()");
    }
    for (int i = 0; i < nStatements; i++) {
      AbstractStatementAst statement = ast.getStatementAst(i);
      boolean isSuperConsCall = (statement instanceof SuperConsAst);
      if (isSuperConsCall && (i > 0 || !isTopLevelBlock)) {
        statement.error("call to super constructor must be first statement");
      }
      if (i == 0 && isTopLevelBlock && isConstructor &&
          superConsArity > 0 && !isSuperConsCall) {
        statement.error("missing call to super()");
      }
      if (i == nStatements - 1 && needsReturn &&
          !(statement instanceof ReturnAst)) {
        statement.error("missing return statement at end of function");
      }
      statement.accept(this);
    }
    _jSymTab.endScope();
  }

  public void visit(CallAst ast) {
    assert(_passIndex == 2);
    String name = ast.getName();
    MethodSymInfo method = _jSymTab.getMethod(name, ast, null);
    if (!method.isStatic()) {
      MethodSymInfo currentMethod = _jSymTab.getCurrentMethod();
      if (currentMethod.isStatic()) {
        ast.error("cannot call instance method %s from a static context",
                  method.getId());
      }
    }
    checkMethodCall(ast, ast.getActuals(), method);
    ast.setSymInfo(method);
    ast.setType(method.getReturnType());
  }

  public void visit(ClassAst ast) {
    if (_passIndex == 0) {
      _jSymTab.addClass(ast.getName(), ast, ast.getSuperClass());
    }
    else { //_passIndex in [1, 2]
      _jSymTab.setCurrentClass(ast.getName(), ast);
      for (AbstractDeclarationAst decl : ast.getDeclarations()) {
        decl.accept(this);
      }
      if (_passIndex == 2) {
        ClassSymInfo classInfo = _jSymTab.getCurrentClass();
        ast.setType(classInfo);
        ast.setSymInfo(classInfo);
        if (classInfo.getConstructor() == null) {
          MethodSymInfo superCons = classInfo.getSuperClass().getConstructor();
          if (superCons != null && superCons.getNFormals() > 0) {
            ast.error("must define constructor with explicit call to super");
          }
        }
        if (_doDebug) {
          System.out.println(_jSymTab.getCurrentClass().dump());
        }
      }
    }
  }

  public void visit(ControlAst ast) {
    if (_whileLevel == 0) {
      ast.error("%s not valid outside a loop", ast.getControl());
    }
  }

  public void visit(ExpStatementAst ast) {
    ast.getExp().accept(this);
  }

  public void visit(FieldDeclarationAst ast) {
    assert(_passIndex > 0);
    if (_passIndex == 1) {
      TypeI type = getType(ast.getTypeAst());
      int rank = (type instanceof ArrayType) ? ((ArrayType)type).getRank() : 0;
      for (InitDeclaratorAst declarator : ast.getInitDeclarators()) {
        String fieldName = declarator.getName();
        TypeI fieldType = getDeclaratorType(type, declarator);
        _jSymTab.addField(fieldName, ast, fieldType, ast.getAccess());
      }
    }
    else {
      assert(_passIndex == 2);
      TypeAst typeAst = ast.getTypeAst();
      typeAst.setType(getType(typeAst));
      ClassSymInfo classSymInfo = _jSymTab.getCurrentClass();
      for (InitDeclaratorAst declarator : ast.getInitDeclarators()) {
        String name = declarator.getName();
        FieldSymInfo field =
          (FieldSymInfo)_jSymTab.getVar(name, ast, null, true);
        classSymInfo.addField(field);
        declarator.setSymInfo(field);
        declarator.setType(field.getType());
        ast.setType(field.getType());
      }
    }
  }

  public void visit(IfAst ast) {
    assert(_passIndex == 2);
    AbstractExpAst cond = ast.getCond();
    AbstractStatementAst thenStmt = ast.getThen();
    AbstractStatementAst elseStmt = ast.getElse();
    cond.accept(this);
    if (cond.getType() != BasicType.BOOLEAN) {
      ast.error("expected if condition to be of boolean type; found %s type",
                cond.getType());
    }
    thenStmt.accept(this); elseStmt.accept(this);
  }

  public void visit(IndexAst ast) {
    AbstractExpAst left = ast.getLeft();
    AbstractExpAst right = ast.getRight();
    left.accept(this); right.accept(this);
    TypeI leftType = left.getType();
    TypeI rightType = right.getType();
    TypeI resultType = BasicType.ERROR;
    if (leftType instanceof ArrayType) {
      resultType = ((ArrayType)leftType).getResultType();
    }
    else {
      ast.error("expected indexing an array, but found %s", leftType);
    }
    if (rightType != BasicType.INT && rightType != BasicType.CHAR) {
      ast.error("expected index expression to be int, but found %s", rightType);
    }
    ast.setType(resultType);
  }

  //Entirely processed by parent
  public void visit(InitDeclaratorAst ast) { }

  public void visit(LiteralAst ast) {
    assert(_passIndex == 2);
    PredefType predefType = ast.getPredefType();
    if (predefType == PredefType.STRING) {
      ast.setType(_jSymTab.STRING);
    }
    else if (predefType == PredefType.OBJECT) {
      assert(ast.getLiteral().equals("null"));
      ast.setType(BasicType.NULL);
    }
    else {
      ast.setType(BasicType.getType(ast.getPredefType()));
    }
  }

  public void visit(MethodDeclarationAst ast) {
    assert(_passIndex > 0);
    if (_passIndex == 1) {
      MethodSymInfo method =
        _jSymTab.addMethod(ast.getName(), ast, getType(ast.getReturnType()),
                           ast.isStatic(), ast.getAccess());
      _jSymTab.setCurrentMethod(ast.getName(), ast);
      ast.setSymInfo(method);
      _jSymTab.beginScope();
      processFormals(ast, method);
      _jSymTab.endScope();
    }
    else {
      assert(_passIndex == 2);
      ClassSymInfo classSymInfo = _jSymTab.getCurrentClass();
      _jSymTab.setCurrentMethod(ast.getName(), ast);
      MethodSymInfo method = _jSymTab.getCurrentMethod();
      if (method.isConstructor()) {
        classSymInfo.setConstructor(method);
      }
      else {
        classSymInfo.addMethod(method);
      }
      _jSymTab.beginScope();
      processFormals(ast, method);
      ast.getBody().accept(this);
      if (isMain(method)) _classesWithMain.add(classSymInfo);
      _jSymTab.endScope();
    }
  }

  public void visit(NameAst ast) {
    assert(_passIndex == 2);
    SymInfo symInfo = _jSymTab.getVar(ast.getName(), ast, null);
    ast.setType(symInfo.getType());
    ast.setSymInfo(symInfo);
  }

  public void visit(NewArrayAst ast) {
    assert(_passIndex == 2);
    TypeI baseType = getType(ast.getBaseType());
    /* remove check to allow interesting programs */
    if (!BasicType.isPrimitiveDataType(baseType)) {
      ast.error("invalid base-type %s; decaf requires a primitive base-type " +
                "for new array creation", baseType);
    }
    for (AbstractExpAst size : ast.getSizes()) {
      size.accept(this);
      TypeI type = size.getType();
      if (type != BasicType.INT && type != BasicType.CHAR) {
        ast.error("expected size expression to be int but got %s", type);
      }
    }
    ast.setType(new ArrayType(baseType, ast.getRank()));
  }

  public void visit(NewInstanceAst ast) {
    assert(_passIndex == 2);
    CallAst constructorCall = ast.getConstructorCall();
    String name = constructorCall.getName();
    ClassSymInfo klass = _jSymTab.getClass(name, constructorCall);
    if (klass == ClassSymInfo.ERROR) {
      ast.error("unknown class %s", name);
    }
    MethodSymInfo constructor = klass.getConstructor();
    if (constructor == null) {
      if (constructorCall.getNActuals() != 0) {
        ast.error("no matching constructor found for %s", name);
      }
    }
    else {
      checkMethodCall(ast, constructorCall.getActuals(), constructor, true);
    }
    if (constructor == null) {
      constructor = new MethodSymInfo(name, ast.getPosition(), klass, klass,
                                      false, PUBLIC, true);
    }
    constructorCall.setSymInfo(constructor);
    ast.setType(klass);
  }

  public void visit(NilExpAst ast) {
    assert(_passIndex == 2);
    ast.setType(BasicType.NIL);
  }

  //Nop visit
  public void visit(NilStatementAst ast) { }

  //Nop visit
  public void visit(NilTypeAst ast) { }

  public void visit(ProgramAst ast) {
    Ast errorAst = ast;
    for (_passIndex = 0; _passIndex < 3; _passIndex++) {
      for (ClassAst classAst : ast.getClasses()) {
        if (errorAst == ast) errorAst = classAst;
        classAst.accept(this);
      }
    }
    if (_classesWithMain.size() == 0) {
      errorAst.error("no main() method defined");
    }
    else if (_classesWithMain.size() > 1) {
      errorAst.error("multiple main() methods defined in classes %s",
                     _classesWithMain);
    }
  }

  public void visit(ReturnAst ast) {
    assert(_passIndex == 2);
    AbstractExpAst retValueAst = ast.getReturnValue();
    retValueAst.accept(this);
    TypeI retValueType = retValueAst.getType();
    TypeI methodType = _jSymTab.getCurrentMethod().getReturnType();
    if ((methodType == BasicType.VOID && retValueType != BasicType.NIL) ||
        !retValueType.isSubType(methodType)) {
      ast.error("incompatible return type; found %s, expected %s",
                retValueType, methodType);
    }
  }

  public void visit(SuperAst ast) {
    assert(_passIndex == 2);
    MethodSymInfo method = _jSymTab.getCurrentMethod();
    if (method.isStatic()) {
      ast.error("cannot refer to super in a static context");
    }
    ast.setType(_jSymTab.getCurrentClass().getSuperClass());
  }

  public void visit(SuperConsAst ast) {
    assert(_passIndex == 2);
    MethodSymInfo currentMethod = _jSymTab.getCurrentMethod();
    if (!currentMethod.isConstructor()) {
      ast.error("cannot call super() outside constructor");
    }
    ClassSymInfo superClass = _jSymTab.getCurrentClass().getSuperClass();
    MethodSymInfo constructor = superClass.getConstructor();
    if (constructor == null) {
      if (ast.getNActuals() != 0) {
        ast.error("no matching constructor found for %s", superClass.getId());
      }
    }
    else {
      checkMethodCall(ast, ast.getActuals(), constructor, true);
    }
  }

  public void visit(ThisAst ast) {
    assert(_passIndex == 2);
    MethodSymInfo method = _jSymTab.getCurrentMethod();
    if (method.isStatic()) {
      ast.error("cannot refer to this in a static context");
    }
    ast.setType(_jSymTab.getCurrentClass());
  }

  //Entirely processed by parent
  public void visit(TypeAst ast) { }

  public void visit(UnaryExpAst ast) {
    assert(_passIndex == 2);
    UnaryExpAst.Op op = ast.getOp();
    AbstractExpAst rand = ast.getOperand();
    rand.accept(this);
    TypeI randType = rand.getType();
    boolean hasError = false;
    if (op == UnaryExpAst.Op.NOT) {
      hasError = (randType != BasicType.BOOLEAN);
      ast.setType(BasicType.BOOLEAN);
    }
    else {
      hasError =
        (randType != BasicType.CHAR && randType != BasicType.INT);
      ast.setType(BasicType.INT);
    }
    if (hasError) {
      ast.error("incompatible type %s for unary operator %s", randType, op);
      ast.setType(BasicType.ERROR);
    }
  }

  public void visit(VarDeclarationAst ast) {
    assert(_passIndex == 2);
    TypeAst typeAst = ast.getTypeAst();
    TypeI type = getType(typeAst);
    typeAst.setType(type);
    int rank = (type instanceof ArrayType) ? ((ArrayType)type).getRank() : 0;
    for (InitDeclaratorAst declarator : ast.getInitDeclarators()) {
      String varName = declarator.getName();
      TypeI varType = getDeclaratorType(type, declarator);
      declarator.setType(varType);
      LocalSymInfo localSymInfo = _jSymTab.addLocal(varName, ast, varType);
      declarator.setSymInfo(localSymInfo);
      AbstractExpAst init = declarator.getInitializer();
      init.accept(this);
      TypeI initType = init.getType();
      if (initType != BasicType.NIL && !initType.isSubType(varType)) {
        declarator.error("incompatible type %s assigned to %s var %s",
                         initType, varType, varName);
      }
    }
  }

  public void visit(WhileAst ast) {
    assert(_passIndex == 2);
    _whileLevel++;
    AbstractExpAst cond = ast.getCond();
    AbstractStatementAst body = ast.getBody();
    cond.accept(this);
    if (cond.getType() != BasicType.BOOLEAN) {
      ast.error("expected while condition to be of boolean type; found %s type",
                cond.getType());
    }
    body.accept(this);
    _whileLevel--;
  }

  /* Utility methods used by multiple visitors */

  private void processFormals(MethodDeclarationAst ast, MethodSymInfo method) {
    for (VarDeclarationAst declaration : ast.getFormals()) {
      InitDeclaratorAst declarator = declaration.getInitDeclarator(0);
      TypeAst declarationTypeAst = declaration.getTypeAst();
      TypeI declarationType = getType(declarationTypeAst);
      declarationTypeAst.setType(declarationType);
      TypeI type = getDeclaratorType(declarationType, declarator);
      String name = declarator.getName();
      FormalSymInfo formal = _jSymTab.addFormal(name, declarator, type);
      if (_passIndex == 1) {
        method.addFormal(formal);
      }
      else {
        declarator.setSymInfo(formal);
        declarator.setType(type);
      }
    }
  }

  private void
    checkMethodCall(Ast ast, List<AbstractExpAst> actuals, MethodSymInfo method)
  {
    checkMethodCall(ast, actuals, method, false);
  }
  private void
    checkMethodCall(Ast ast, List<AbstractExpAst> actuals, MethodSymInfo method,
                    boolean allowConstructor)
  {
    for (AbstractExpAst actual : actuals) {
      actual.accept(this);
    }
    if (method != MethodSymInfo.ERROR) {
      if (method.isConstructor() && !allowConstructor) {
        ast.error("invalid call to constructor %s", method.getId());
      }
      int nFormals = method.getNFormals();
      int nActuals = actuals.size();
      if (nFormals != nActuals) {
        ast.error("# of arguments for call to %s does not match declaration: " +
                  "found %d, expected %d", method.getId(), nActuals, nFormals);
      }
      int nCheck = (nFormals < nActuals) ? nFormals : nActuals;
      for (int i = 0; i < nCheck; i++) {
        TypeI formalType = method.getFormal(i).getType();
        TypeI actualType = actuals.get(i).getType();
        if (!actualType.isSubType(formalType)) {
          ast.error("type mismatch for parameter %d for call to %s: " +
                    "formal type is %s, but actual type is %s",
                    i + 1, method.getId(), formalType, actualType);
        }
      }
    }
  }

  private static TypeI
    getDeclaratorType(TypeI type, InitDeclaratorAst declarator)
  {
    int rank = declarator.getRank();
    if (rank > 0) {
      if (type instanceof ArrayType) {
        ArrayType arrayType = (ArrayType)type;
        return new ArrayType(arrayType.getBaseType(),
                             arrayType.getRank() + rank);
      }
      else {
        return new ArrayType(type, rank);
      }
    }
    else {
      return type;
    }
  }

  private TypeI getType(AbstractTypeAst ast) {
    if (ast instanceof NilTypeAst) {
      return BasicType.NIL;
    }
    else {
      TypeAst typeAst = (TypeAst)ast;
      PredefType predef = typeAst.getPrimitiveBaseType();
      TypeI baseType =
        (predef != null) ? BasicType.getType(predef)
                         : _jSymTab.getClass(typeAst.getBaseType(), ast);
      return
        (baseType == ClassSymInfo.ERROR)
        ? BasicType.ERROR
        : (typeAst.getRank() == 0)
        ? baseType
        : new ArrayType(baseType, typeAst.getRank());
    }
  }

  private boolean isMain(MethodSymInfo method) {
    boolean ret = false;
    if ("main".equals(method.getId()) && method.isStatic() &&
        method.getNFormals() == 1 && method.getReturnType() == BasicType.VOID) {
      TypeI argType = method.getFormal(0).getType();
      if (argType instanceof ArrayType) {
        ArrayType arrayType = (ArrayType)argType;
        ret = arrayType.getBaseType() == _jSymTab.STRING &&
              arrayType.getRank() == 1;
      }
    }
    return ret;
  }

  /*                    Binary Operator Type Checking              */
  private TypeI
    checkBinaryOp(Ast ast, BinaryExpAst.Op op, TypeI leftType, TypeI rightType)
  {
    boolean hasError = false;
    TypeI resultType = null;
    if (op == BinaryExpAst.Op.EQ || op == BinaryExpAst.Op.NE) {
      if (leftType != rightType) {
        if (!leftType.isSubType(rightType) && !rightType.isSubType(leftType)) {
          hasError = true;
        }
      }
      resultType = BasicType.BOOLEAN;
    }
    else {
      BinaryOpType opType = BINARY_OPS_MAP.get(op);
      List<TypeI> randTypes = opType.randTypes;
      hasError =
        (!randTypes.contains(leftType) || !randTypes.contains(rightType));
      resultType = opType.resultType;
    }
    if (hasError) {
      ast.error("incompatible types %s and %s for binary operator %s",
                leftType, rightType, op);
    }
    return resultType;
  }

  private static class BinaryOpType {
    private final List<TypeI> randTypes;
    private final TypeI resultType;
    BinaryOpType(List<TypeI> randTypes, TypeI resultType) {
      this.randTypes = randTypes; this.resultType = resultType;
    }
  }
  private static Map<BinaryExpAst.Op, BinaryOpType> BINARY_OPS_MAP;
  static {
    List<TypeI> intTypes =
      Arrays.asList(new TypeI[] { BasicType.CHAR, BasicType.INT });
    List<TypeI> boolTypes = Arrays.asList(new TypeI[] { BasicType.BOOLEAN });
    BinaryOpType relOpType = new BinaryOpType(intTypes, BasicType.BOOLEAN);
    BinaryOpType arithOpType = new BinaryOpType(intTypes, BasicType.INT);
    BinaryOpType boolOpType =
      new BinaryOpType(boolTypes, BasicType.BOOLEAN);
    BINARY_OPS_MAP = new HashMap<BinaryExpAst.Op, BinaryOpType>() {{
        put(BinaryExpAst.Op.ADD, arithOpType);
        put(BinaryExpAst.Op.AND, boolOpType);
        put(BinaryExpAst.Op.DIV, arithOpType);
        //Op.EQ, Op.NE handled in code
        put(BinaryExpAst.Op.GE, relOpType);
        put(BinaryExpAst.Op.GT, relOpType);
        put(BinaryExpAst.Op.MOD, arithOpType);
        put(BinaryExpAst.Op.MUL, arithOpType);
        put(BinaryExpAst.Op.OR, boolOpType);
        put(BinaryExpAst.Op.LE, relOpType);
        put(BinaryExpAst.Op.LT, relOpType);
        put(BinaryExpAst.Op.SUB, arithOpType);
      }};
  }


}
