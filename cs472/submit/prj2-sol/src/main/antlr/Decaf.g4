grammar Decaf;

start
  : (c_class | comment)+
  ;
WS 
  : (' '+ | '\n') -> skip
  ;
c_class
  : 'class' ID s_super? '{' member* '}'
  ;
s_super
  : 'extends' ID
  ;
member
  :  comment? field comment?
  |  comment? method comment?
  |  comment? ctor comment?
  | comment
  ;
field
  : modifier* type varDeclaratorList ';'
  ;
method
  : modifier* type ID formalArgs block
  ;
ctor
  : modifier* ID formalArgs block
  ;
modifier
  : 'static'
  | 'public'
  | 'private'
  | 'protected'
  ;
formalArgs
  : '(' formalArgList? ')'
  ; 
formalArgList
  : formalArg 
  | formalArg ',' formalArgList
  ;
formalArg
  : type varDeclaratorId
  ;
type
  : primitiveType
  | ID
  | type '[' ']'
  ;
primitiveType
  : 'boolean'
  | 'char'
  | 'int'
  | 'void'
  ;
varDeclaratorList
  : varDeclarator ',' varDeclaratorList
  | varDeclarator
  ;
varDeclarator
  : varDeclaratorId
  | varDeclaratorId '=' expression
  ;
varDeclaratorId
  : ID
  | varDeclaratorId '[' ']'
  ;
block
  : '{' comment? statement* comment? '}'
  ;
statement
  : ';'
  | type varDeclaratorList ';'
  | 'if' enclosedExpr statement
  | 'if' enclosedExpr block 
  | 'if' enclosedExpr block e_else
  | 'if' enclosedExpr statement e_else
  | expression ';'
  | 'while' enclosedExpr block
  | 'while' enclosedExpr statement
  | 'return' expression? ';'
  | 'continue' ';'
  | 'break' ';'
  | 'super' actualArgs ';'
  ;
e_else
  : 'else' block
  | 'else' statement
  ;
enclosedExpr
  : '(' expression ')' 
  ;
expression
  : expression binaryOp expression
  | unaryOp expression
  | primary
  ;
binaryOp
  : '=' | '||' | '&&' | '==' | '!=' | '<' | '>' | '<=' | '>='
  | '+' | '-' | '*' | '/' | '%'
  ;
unaryOp
  : '+' | '-' | '!'
  ;
primary
  : newArrayExpr
  | nonNewArrayExpr
  | ID
  ;
addAttr
  : '.' ID actualArgs addAttr
  | /* epsilon */
  ;
nonNewArrayLabels
  : literal
  | 'this'
  | enclosedExpr
  | 'new' ID actualArgs
  | ID actualArgs
  | ID '.' ID actualArgs
  ;
newArrayExpr
  : 'new' ID dimension+
  | 'new' primitiveType dimension+
  ;
dimension
  : '[' expression ']'
  ;
nonNewArrayFields
  : nonNewArrayLabels
  | arrayExpr
  | fieldExpr
  | newArrayExpr '.' ID actualArgs
  ;
nonNewArrayExpr
  : nonNewArrayLabels addAttr
  | nonNewArrayFields addAttr
  ;
fieldExpr
  : nonNewArrayLabels '.' ID
  | ID '.' ID
  | 'super' '.' ID
  | fieldExprP
  ;
fieldExprP
  : nonNewArrayLabels '.' ID fieldExprPP
  | ID '.' ID fieldExprPP
  | 'super' '.' ID fieldExprPP
  ;
fieldExprPP
  : '.' ID fieldExprPP
  | /* epsilon */
  ;
arrayExpr
  : ID dimension
  | nonNewArrayLabels dimension
  | arrayExprP
  ;
arrayExprP
  : ID dimension arrayExprPP
  | nonNewArrayLabels arrayExprPP
  ;
arrayExprPP
  : dimension arrayExprPP
  | /* epsilon */
  ;
literal
  : 'null' | 'true' | 'false' | INT_LITERAL | CHAR_LITERAL | STRING_LITERAL
  ;
actualArgs
  : '(' exprList? ')'
  ;
exprList
  : expression
  | expression ',' exprList
  ;
  comment 
  : COMMENT
  ;

ID : ([a-zA-Z_][0-9a-zA-Z_]*) ;
INT_LITERAL : ([0]|[1-9][0-9]*) ;
CHAR_LITERAL : '\'' ~[\\n'0-9] '\'' | '\'\\' ~[nt] '\'' |  '\'\\t' | '\'\\n' ;
STRING_LITERAL : '"' (~[\n"]* | '\\' ('\\\\' | '"') )* '"' ;

COMMENT
  : ( '//' ~[\r\n]* '\r'?
  | '/*' .*? '*/'
    )
  ;
