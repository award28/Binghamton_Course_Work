grammar Decaf;

@header {
  import org.antlr.v4.runtime.InputMismatchException;
  import org.antlr.v4.runtime.Token;

  import java.util.ArrayList;	
  import java.util.Collections;	
  import java.util.List;	
}

@parser::members {

  private boolean isError() { return getNumberOfSyntaxErrors() > 0; }

  //Factory methods which construct AST only when no errors		 
  private AccessAst
    newAccessAst(Token t, AbstractExpAst left, AbstractExpAst right)
  {
    return isError() ? null : new AccessAst(t, left, right);
  }

  private AssignAst 
    newAssignAst(Token t, AbstractExpAst left, AbstractExpAst right)
  {
    return isError() ? null : new AssignAst(t, left, right);
  }

  private BinaryExpAst 
    newBinaryExpAst(Token op, AbstractExpAst left, AbstractExpAst right)
  {
    return isError() ? null : new BinaryExpAst(op, left, right);
  }

  private BlockAst newBlockAst(Token lbrace, List<AbstractStatementAst> stmts) {
    return isError() ? null : new BlockAst(lbrace, stmts);
  }

  private CallAst newCallAst(Token id, List<AbstractExpAst> actuals) {
    return isError() ? null : new CallAst(id, actuals);
  }

  private ClassAst 
    newClassAst(Token id, String superClass, 
                List<AbstractDeclarationAst> members) 
  {
    return isError() ? null : new ClassAst(id, superClass, members);
  }

  private ControlAst newControlAst(Token t) {
    return isError() ? null : new ControlAst(t);
  }

  private ExpStatementAst newExpStatementAst(AbstractExpAst exp) {
    return isError() ? null : new ExpStatementAst(exp);
  }

  private FieldDeclarationAst
    newFieldDeclarationAst(TypeAst type, List<InitDeclaratorAst> list,
                           List<String> modifiers)
  {
    return isError() ? null : new FieldDeclarationAst(type, list, modifiers);
  }

  private IfAst newIfAst(Token t, AbstractExpAst cond, 
                         AbstractStatementAst s1, AbstractStatementAst s0)
  {
    return isError() ? null : new IfAst(t, cond, s1, s0);
  }

  private IndexAst
    newIndexAst(Token t, AbstractExpAst left, AbstractExpAst right)
  {
    return isError() ? null : new IndexAst(t, left, right);
  }

  private InitDeclaratorAst
    newInitDeclaratorAst(Token id, int rank, AbstractExpAst initExp) 
  {
    return isError() ? null : new InitDeclaratorAst(id, rank, initExp);
  }

  private LiteralAst newLiteralAst(Token t, PredefType type) {
    return isError() ? null : new LiteralAst(t, type);
  }

  private MethodDeclarationAst
    newMethodDeclarationAst(AbstractTypeAst retType, Token name,
                            List<VarDeclarationAst> formals, BlockAst body, 
                            List<String> modifiers)
  {
    return isError() 
           ? null 
           : new MethodDeclarationAst(retType, name, formals, body, modifiers);
  }

  private NameAst newNameAst(Token id) {
    return isError() ? null : new NameAst(id);
  }

  private NewArrayAst
    newNewArrayAst(Token t, TypeAst type, List<AbstractExpAst> sizes)
  {
    return isError() ? null : new NewArrayAst(t, type, sizes);
  }

  private NewInstanceAst newNewInstanceAst(Token t, CallAst call) {
    return isError() ? null : new NewInstanceAst(t, call);
  }

  private NilExpAst newNilExpAst(Token t) {
    return isError() ? null : new NilExpAst(t);
  }

  private NilStatementAst newNilStatementAst(Token t) {
    return isError() ? null : new NilStatementAst(t);
  }

  private NilTypeAst newNilTypeAst(Token id) {
    return isError() ? null : new NilTypeAst(id);
  }

  private ProgramAst newProgramAst(List<ClassAst> classes) {
    return isError() ? null : new ProgramAst(classes); 
  }

  private ReturnAst newReturnAst(Token t, AbstractExpAst retValue) {
    return isError() ? null : new ReturnAst(t, retValue);
  }

  private SuperAst newSuperAst(Token t) {
    return isError() ? null : new SuperAst(t);
  }

  private SuperConsAst newSuperConsAst(Token t, List<AbstractExpAst> actuals) {
    return isError() ? null : new SuperConsAst(t, actuals);
  }

  private ThisAst newThisAst(Token t) {
    return isError() ? null : new ThisAst(t);
  }

  private TypeAst newTypeAst(Token token, int rank) {
    return isError() ? null : new TypeAst(token, rank); 
  }

  private UnaryExpAst newUnaryExpAst(Token op, AbstractExpAst exp) {
    return isError() ? null : new UnaryExpAst(op, exp);
  }

  private VarDeclarationAst
    newVarDeclarationAst(TypeAst type, List<InitDeclaratorAst> declarators)
  {
    return isError() ? null : new VarDeclarationAst(type, declarators);
  }

  private WhileAst 
    newWhileAst(Token t, AbstractExpAst cond, AbstractStatementAst s)
  {
    return isError() ? null : new WhileAst(t, cond, s);
  }
    
}

//Grammar starts
start returns [ProgramAst ast]
    locals [ List<ClassAst> classes = new ArrayList<>(); ]
  : ( c=classx { $classes.add($c.ast); } )+
    { $ast = newProgramAst($classes); }
  ;
classx returns [ClassAst ast]
    locals [ String sClass = "Object",
             List<AbstractDeclarationAst> members = new ArrayList<>() 
           ]
  : 'class' ID ( s=superx { $sClass = $s.lexeme; } )? 
    '{' ( m = member { $members.add($m.ast); } )* '}'
    {  $ast = newClassAst($ID, $sClass, $members); }
  ;
superx returns [ String lexeme ]
  : 'extends' ID { $lexeme = $ID.getText(); }
  ;
member returns [AbstractDeclarationAst ast]
  : f=field { $ast = $f.ast; }
  | m=method { $ast = $m.ast; }
  | c=ctor { $ast = $c.ast; }
  ;
field returns [FieldDeclarationAst ast]
  : modifiers type v=varDeclaratorIdList ';'
    { $ast = newFieldDeclarationAst($type.ast, $v.list, $modifiers.list); }
  ;
method returns [MethodDeclarationAst ast]
  : m=modifiers t=type ID f=formalArgs b=block
    { $ast = newMethodDeclarationAst($t.ast, $ID, $f.formals, 
                                     $b.ast, $m.list); 
    }
  ;
ctor returns [ MethodDeclarationAst ast ]
  : m=modifiers ID f=formalArgs b=block
    { $ast = newMethodDeclarationAst(newNilTypeAst($ID), $ID, $f.formals, 
                                     $b.ast, $m.list); 
    }
  ;
modifiers returns [ List<String> list ]
  : { $list = new ArrayList<>(); }
    ( m=modifier { $list.add($m.lexeme); } )*
  ;
modifier returns [ String lexeme ]
  : m='static' { $lexeme = $m.getText(); }
  | m='public' { $lexeme = $m.getText(); }
  | m='private' { $lexeme = $m.getText(); }
  | m='protected' { $lexeme = $m.getText(); }
  ;
formalArgs returns [ List<VarDeclarationAst> formals ]
   : '(' ')' { $formals = Collections.emptyList(); } 
   | { $formals = new ArrayList<>(); }
     '(' ( f=formalArg { $formals.add($f.ast); } )
        ( ',' f1=formalArg { $formals.add($f1.ast); } )*
     ')'
  ; 
formalArg returns [ VarDeclarationAst ast ]
  : t=type v=varDeclaratorId
    { $ast = newVarDeclarationAst($t.ast, Collections.singletonList($v.ast)); }
  ;
type returns [ TypeAst ast ]
  : t=typeBase d=dimensions
    { $ast = newTypeAst($t.token, $d.rank); }
  ;
typeBase returns [ Token token ]
  : t=primitiveType { $token = $t.token; }
  | ID {$token = $ID; }
  ;
dimensions returns [ int rank ]
  : { $rank = 0; }
    ( '[' ']' { $rank++; } ) *
  ;
primitiveType returns [ Token token ]
  : t='boolean' { $token = $t; }
  | t='char' { $token = $t; }
  | t='int' { $token = $t; }
  | t='void' { $token = $t; }
  ;
varDeclaratorIdList returns [ List<InitDeclaratorAst> list ]
  : v1=varDeclaratorId
    { $list = new ArrayList<>(); $list.add($v1.ast); }
    ( ',' v=varDeclaratorId { $list.add($v.ast); } )*
  ;
varDeclaratorList returns [ List<InitDeclaratorAst> list ]
  : v1=varDeclarator 
    { $list = new ArrayList<>(); $list.add($v1.ast); }
    ( ','  v2=varDeclarator { $list.add($v2.ast); } )*
  ;
varDeclarator returns [ InitDeclaratorAst ast ]
  : varDeclaratorId
    { $ast = $varDeclaratorId.ast; }
  | ID d=dimensions '=' e=expression
    { $ast = newInitDeclaratorAst($ID, $d.rank, $e.ast); }
  ;
varDeclaratorId returns [ InitDeclaratorAst ast ]
  : ID d=dimensions
    { $ast = newInitDeclaratorAst($ID, $d.rank, newNilExpAst($ID)); }
  ;
block returns [ BlockAst ast ]
    locals [ List<AbstractStatementAst> list = new ArrayList<>(); ]
  : lbrace='{' ( s=statement { $list.add($s.ast); } )* '}'
    { $ast = newBlockAst($lbrace, $list); }
  ;
statement returns [ AbstractStatementAst ast ]
    locals [ AbstractStatementAst eStmt,
             AbstractExpAst ret
           ]
  : semi=';' { $ast = newNilStatementAst($semi); }
  | type1=type v=varDeclaratorList ';'
    { $ast = newVarDeclarationAst($type1.ast, $v.list); }
  | if1='if' '(' cond1=expression ')' 
    then1=statement 
    { $eStmt = newNilStatementAst($then1.stop); }
    ( 'else'  else1=statement { $eStmt = $else1.ast; } )?  
    { $ast = newIfAst($if1, $cond1.ast, $then1.ast, $eStmt); }
  | exp=expression ';'
    { $ast = newExpStatementAst($exp.ast); }
  | w='while' '(' cond=expression ')' s=statement
    { $ast = newWhileAst($w, $cond.ast, $s.ast); }
  | r='return' 
    { $ret = newNilExpAst($r); } 
    ( e=expression { $ret = $e.ast; } )? 
    ';'
    { $ast = newReturnAst($r, $ret); }
  | cont='continue' ';' 
    { $ast = newControlAst($cont); } 
  | brk='break' ';'
    { $ast = newControlAst($brk); }
  | sup='super' actuals=actualArgs ';'
    { $ast = newSuperConsAst($sup, $actuals.list); }
  | blk=block 
    { $ast = $blk.ast; }
  ;
expression returns [ AbstractExpAst ast ]
  : assignExp
    { $ast = $assignExp.ast; }
  ;
assignExp returns [ AbstractExpAst ast ]
  : lowExp
    { $ast = $lowExp.ast; }
  | <assoc=right> e1=assignExp eq='=' e2=assignExp
    { $ast = newAssignAst($eq, $e1.ast, $e2.ast); }
  ;
lowExp returns [ AbstractExpAst ast ]
  : nonAssocExp
    { $ast = $nonAssocExp.ast; }
  | e1=lowExp op='==' e2=lowExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=lowExp op='!=' e2=lowExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=lowExp op='&&' e2=lowExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=lowExp op='||' e2=lowExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  ;
nonAssocExp returns [ AbstractExpAst ast ]
  : e1=opExp op='<' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=opExp op='>' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=opExp op='<=' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=opExp op='>=' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | opExp
    { $ast = $opExp.ast; }
  ;
opExp returns [ AbstractExpAst ast ]
  : primary
    { $ast = $primary.ast; }
  | op='+' e=opExp
    { $ast = newUnaryExpAst($op, $e.ast); }
  | op='-' e=opExp
    { $ast = newUnaryExpAst($op, $e.ast); }
  | op='!' e=opExp
    { $ast = newUnaryExpAst($op, $e.ast); }
  | e1=opExp op='*' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=opExp op='/' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=opExp op='%' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=opExp op='+' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  | e1=opExp op='-' e2=opExp
    { $ast = newBinaryExpAst($op, $e1.ast, $e2.ast); }
  ;
primary returns [ AbstractExpAst ast ]
  : newArrayExpr
    { $ast = $newArrayExpr.ast; }
  | nonNewArrayExpr
    { $ast = $nonNewArrayExpr.ast; }
  | ID
    { $ast = newNameAst($ID); }
  ;
newArrayExpr returns [ AbstractExpAst ast ]
  : n='new' ID s=sizes
     { $ast = newNewArrayAst($n, newTypeAst($ID, 0), $s.list); }
  | n='new' t=primitiveType s=sizes
     { $ast = newNewArrayAst($n, newTypeAst($t.token, 0), $s.list); }
  ;
sizes returns [ List<AbstractExpAst> list ]
  : { $list = new ArrayList<>(); }
    ( e=size  { $list.add($e.ast); } )+
  ;
size returns [ AbstractExpAst ast ]
  : '[' e=expression ']' 
    { $ast = $e.ast; }
  ;
nonNewArrayExpr returns [ AbstractExpAst ast ]
  : literal
    { $ast = $literal.ast; }
  | t='this'
    { $ast = newThisAst($t); }
  | '(' expression ')'
    { $ast = $expression.ast; }
  | n='new' ID actualArgs
    { $ast = newNewInstanceAst($n, newCallAst($ID, $actualArgs.list)); }
  | ID actualArgs
    { $ast = newCallAst($ID, $actualArgs.list); }
  | e1=nonNewArrayExpr d='.' ID actuals=actualArgs
    { $ast = newAccessAst($d, $e1.ast, newCallAst($ID, $actuals.list)); }
//  | newArrayExpr d='.' ID actualArgs
  | id1=ID d='.' id2=ID a=actualArgs
    { $ast = newAccessAst($d, newNameAst($id1), newCallAst($id2, $a.list)); }
  | sup='super' d='.' ID a=actualArgs
    { $ast = newAccessAst($d, newSuperAst($sup), newCallAst($ID, $a.list)); }
  | ID x=indexExp
    { $ast = newIndexAst($x.start, newNameAst($ID), $x.ast); }
  | e=nonNewArrayExpr x=indexExp
    { $ast = newIndexAst($x.start, $e.ast, $x.ast); }
//  | newArrayExpr '.' ID
  | e=nonNewArrayExpr d='.' ID
    { $ast = newAccessAst($d, $e.ast, newNameAst($ID)); }
  | id1=ID d='.' id2=ID
    { $ast = newAccessAst($d, newNameAst($id1), newNameAst($id2)); }
  | sup='super' d='.' ID
    { $ast = newAccessAst($d, newSuperAst($sup), newNameAst($ID)); }
  ;
indexExp returns [ AbstractExpAst ast ]
  : '[' e=expression ']'
    { $ast = $e.ast; }
  ;
literal returns [ AbstractExpAst ast ]
  : t='null' 
    { $ast = newLiteralAst($t, PredefType.OBJECT); }
  | t='true' 
    { $ast = newLiteralAst($t, PredefType.BOOLEAN); }
  | t='false' 
    { $ast = newLiteralAst($t, PredefType.BOOLEAN); }
  | INT_LITERAL 
    { $ast = newLiteralAst($INT_LITERAL, PredefType.INT); }
  | CHAR_LITERAL 
    { $ast = newLiteralAst($CHAR_LITERAL, PredefType.CHAR); }
  | STRING_LITERAL
    { $ast = newLiteralAst($STRING_LITERAL, PredefType.STRING); }
  ;
actualArgs returns [ List<AbstractExpAst> list ]
   : '(' ')' { $list = Collections.emptyList(); } 
   | { $list = new ArrayList<>(); }
     '(' ( e=expression { $list.add($e.ast); } )
        ( ',' e1=expression { $list.add($e1.ast); } )*
     ')'
  ; 

//Lexical grammar
FORBIDDEN
  : ( 'abstract' | 'byte' | 'case' | 'catch' | 'const' 
  | 'default' | 'do' | 'double' | 'final' | 'finally' 
  | 'for' | 'implements' | 'import' | 'instanceof' | 'interface' 
  | 'long' | 'native' | 'goto' | 'package' | 'short' 
  | 'switch' | 'synchronized' | 'throw' | 'throws' | 'transient' 
  | 'try' | 'volatile' | 'byvalue' | 'cast' | 'future' | 'generic' 
  | 'inner' | 'none' | 'operator' | 'outer' | 'rest' | 'var'
  | 'byte' | 'double' | 'float' | 'long' | 'short' 
  | '~' | '?' | ':' | '++' | '--' | '&' | '|' | '^' | '<<' | '>>' | '>>>'
  | '+=' | '-=' | '*=' | '/=' | '&=' | '|=' 
  | '^=' | '%=' | '<<=' | '>>=' | '>>>=' )
    { String msg = String.format("forbidden symbol '%s'", getText());
      getErrorListenerDispatch().syntaxError(this, getText(), getLine(),
                                             getCharPositionInLine(), 
					     msg, null);
    } 
    -> skip
  ;
INT_LITERAL
  : '0'|[1-9][0-9]*
  ;
CHAR_LITERAL
  : '\''~[\\']'\'' 
  | '\'''\\'.'\''
  ;
STRING_LITERAL
  : '"'(~[\\"]|'\\'.)*'"'
  ;
ID
  : [a-zA-Z_][a-zA-Z0-9_]*
  ;
WS
  : [ \t\r\n]+ -> skip
  ;
SINGLE_LINE_COMMENT
  : '/''/'~[\n]+ 
    -> skip
  ;
MULTI_LINE_COMMENT
  : '/''*'.*?'*''/' 
    -> skip
  ;
