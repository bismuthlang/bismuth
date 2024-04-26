/*
 * Alex Friedman (ahfriedman@wpi.edu)
 * Grammar file for Bismuth
 */
grammar Bismuth;

// Parser rules
compilationUnit   :  (imports+=importStatement | externs+=externStatement | defs+=defineType)* EOF ; 

structCase        :  (ty=type name=VARIABLE) ';' ;


// TODO: how to specify that we need a protocol type, linear type, etc?
genericTemplate     : '<' gen+=genericEntry (',' gen+=genericEntry)* '>' ;

genericEntry        : name=VARIABLE (':' supTy+=type (',' supTy+=type)*)?   # GenericType
                    | 'Session' name=VARIABLE                               # GenericSession
                    ;

genericSpecifier    : LESS subst+=type (',' subst+=type)* GREATER        ;

defineType        : DEFINE ENUM name=VARIABLE genericTemplate? LSQB cases+=type (',' cases+=type)+ RSQB      # DefineEnum
                  | DEFINE STRUCT name=VARIABLE genericTemplate? LSQB (cases+=structCase)*  RSQB             # DefineStruct
                  | DEFINE name=VARIABLE genericTemplate? '::' channelName=VARIABLE ':' ty=type '='? block   # DefineProgram
                  | DEFINE FUNC name=VARIABLE genericTemplate? lam=lambdaConstExpr                           # DefineFunction
                  ; 

//FIXME: THIS ALLOWS FOR (, ...) WHICH ISNT RIGHT NOW THAT WE REQUIRE PARAMLISTS TO BE ABLE TO BE EMPTY!
externStatement : EXTERN FUNC name=VARIABLE LPAR ((paramList=parameterList variadic=VariadicParam?) | ELLIPSIS) RPAR (COLON ret=type)? ';'; 


pathElement     : id=VARIABLE genericSpecifier? ;

path            : eles+=pathElement ('::' eles+=pathElement)* ; 

importStatement : IMPORT path ('as' alias=VARIABLE)? ';'? ; 

inv_args            :  LPAR (args+=expression (',' args+=expression)* )? RPAR   ;

// fieldAccessExpr     : fields+=VARIABLE ('.' fields+=VARIABLE)*  ;

/*
 * Expressions return values. These can be: 
 *      1. Parenthetical expressions of the form: ( expr )
 *      2. Unary Expressions such as: -1 and !false
 *      3. Binary Arithmetic expressions such as: 1 * 2, 6 / 3, 2 + 3, 5 - 6
 *              Note: Separated into two lines for presedence of * and / over + and - 
 *      4. Binary Relational expressions such as: 1 < 2, 1 <= 2, 2 > 1, 2 >= 1
 *      5. Equality expressions such as : 1 = 2, true != false
 *      6. Logical AND such as: true & true
 *      7. Logical OR such as: true | false
 *      8. Invocations of functions (as they have return values)
 *      9. Field Access such as: array.length
 *              Note: this uses an expression instead of a variable because, in theory, 
 *              an extended language could allow for something like (<condition> ? array1 : array2).length
 *      10. Array accesses such as: array[0]. 
 *              Note: While theoreticaly, a language could allow for something like:
 *               (<condition> ? array1 : array2)[(<condition> ? array 1 : array2).length - 1]
 *              because Bismuth does not yet have this functionality, it is easier to require
 *              the use of variables instead of expressions for array access
 *      11-14. Typical boolean and variable constants. 
 */
expression  
    : LPAR ex=expression RPAR                      # ParenExpr
    | <assoc=left>expr=expression inv_args         # CallExpr
    | expr=expression '[' index=expression ']'     # ArrayAccess
    | '[' ((elements+=expression ',')* elements+=expression)? ']'   # ArrayExpression
    | VARIABLE                                     # IdentifierExpr
    | expr=expression ('.' fields+=VARIABLE)+      # FieldAccessExpr
    | path                                         # PathExpr
    | <assoc=right> op=(MINUS | NOT | BIT_NOT) ex=expression                        # UnaryExpr 
    | left=expression op=(MULTIPLY | DIVIDE | MOD) right=expression                 # BinaryArithExpr
    | left=expression op=(PLUS | MINUS) right=expression                            # BinaryArithExpr
    | left=expression shiftOp right=expression                                      # BinaryArithExpr
    | left=expression op=(LESS | LESS_EQ | GREATER | GREATER_EQ) right=expression   # BinaryRelExpr 
    | left=expression op=(BIT_AND | BIT_OR | BIT_XOR) right=expression              # BinaryArithExpr
    | <assoc=right> left=expression op=(EQUAL | NOT_EQUAL) right=expression         # EqExpr
    | exprs+=expression (LOG_AND exprs+=expression)+                                # LogAndExpr 
    | exprs+=expression (LOG_OR  exprs+=expression)+                                # LogOrExpr
    | path '::init' '(' (exprs+=expression (',' exprs+=expression)*)? ')'           # InitProduct
    | MULTIPLY expr=expression                      # Deref
    | 'Box'     LESS ty=type GREATER '::init' '(' expr=expression ')'               # InitBox
    | booleanConst                                  # BConstExpr 
    | i=integerValue                                # IConstExpr
    | s=STRING                                      # SConstExpr 
    | lambdaConstExpr                               # LambdaExpr
    | channel=VARIABLE '.recv' LPAR RPAR            # AssignableRecv
    | channel=VARIABLE '.is_present' LPAR RPAR      # AssignableIsPresent
    | EXEC prog=expression                          # AssignableExec
    | COPY LPAR expr=expression RPAR                # CopyExpr
    | COPY expr=expression                          # CopyExpr
    | 'asChannel' LPAR expr=expression RPAR         # AsChannelExpr
    ;

lambdaConstExpr 
    : LPAR parameterList RPAR (COLON ret=type)? block ;

/* 
 * Keeping block as its own rule so that way we can re-use it as
 * its own statement as well as as parts of functions, programs, 
 * conditions, loops, etc. 
 */
block      : LSQB (stmts+=statement)* RSQB ;


// Parenthesis are optional around a condition
condition           : (LPAR ex=expression RPAR) | ex=expression ; 

//Used to model each alternative in a selection 
selectAlternative   : check=expression ':' eval=statement   ; 
matchAlternative    : check=type name=VARIABLE '=>' eval=statement ;
protoAlternative    : (lbl=VARIABLE | check=protocol) '=>' eval=statement    ;
protoElse           : ELSE '=>' eval=statement              ;


/*
 * Helps to consistently manage parameters. 
 * 
 * ParameterList allows to get a list of one parameter
 *      followed by any number of subsequent parameters that are 
 *      comma separated.
 *
 * Parameter defines a parameter: its just a type and name.
 */
parameterList   : (params+=parameter (',' params+=parameter)*)?;
parameter       : ty=type name=VARIABLE ;
VariadicParam   : ',' [ \t]* '...'; //For some reason, need to match the whitespace so that way we can allow spaces between the two...

/*
 * Assignment fragment: this contains the information about variables
 * that we wish to declare as well as a potential expression to serve as their 
 * value. This is used by the VarDeclStatement to help separate multiple 
 * assigments. Ie those of the form:   var a := 1, b := 2, ... 
 */
// assignment : v+=VARIABLE (',' v+=VARIABLE)* (ASSIGN a=assignable)? ;
assignment  : v+=VARIABLE (',' v+=VARIABLE)* (ASSIGN a=expression)? ;


statement   : defineType                                                                                            # TypeDef
            | variableDeclaration  ';'?                                                                             # VarDeclStatement
            | assignmentStatement  ';'?                                                                             # AssignStatement 
            | IF check=condition trueBlk=block (ELSE falseBlk=block)? (rest+=statement)*                            # ConditionalStatement
            | SELECT LSQB (cases+=selectAlternative)* RSQB (rest+=statement)*                                       # SelectStatement     
            | MATCH check=condition LSQB (matchAlternative)* RSQB (rest+=statement)*                                # MatchStatement   
            | MATCH check=condition ('|' matchAlternative)*    (rest+=statement)*                                   # MatchStatement   
            | RETURN expression? ';'                                                                                # ReturnStatement 
            | EXIT                                                                                                  # ExitStatement // Should we add sugar thatd allow {c.send(..); exit} to be written as exit c.send() ?
            | 'skip'                                                                                                # SkipStatement //FIXME: ENABLE
            | block                                                                                                 # BlockStatement
            | channel=VARIABLE '.send' '(' expr=expression ')' ';'?                                                 # ProgramSend
            | WHILE check=condition block                                                                           # ProgramLoop
            | 'for' '(' (decl=variableDeclaration | assign=assignmentStatement) ';' check=condition ';' expr=statement ')' blk=block   # ForStatement
            | channel=VARIABLE '.case' '(' opts+=protoAlternative (opts+=protoAlternative)+ protoElse? ')' (rest+=statement)*  # ProgramCase  
            | 'offer' channel=VARIABLE  ( '|' opts+=protoAlternative )+ ('|' protoElse?)? (rest+=statement)*                   # ProgramCase   
            | channel=VARIABLE LBRC (lbl=VARIABLE | sel=protocol) RBRC                                                               # ProgramProject
            | 'more' '(' channel=VARIABLE ')'   ';'?                                # ProgramContract 
            | 'unfold' '(' channel=VARIABLE ')'   ';'?                              # ProgramContract 
            | 'weaken' '(' channel=VARIABLE ')' ';'?                                # ProgramWeaken
            | 'accept' '(' channel=VARIABLE ')' block                               # ProgramAccept
            | 'acceptWhile' '(' channel=VARIABLE ',' ex=expression ')' block        # ProgramAcceptWhile
            | 'acceptIf' '(' channel=VARIABLE ',' check=expression ')' trueBlk=block (ELSE falseBlk=block)? (rest+=statement)*  # ProgramAcceptIf
            | 'close' '(' channel=VARIABLE ')'  ';'?                                # ProgramClose  // FIXME: ENABLE
            | 'cancel' '(' channel=VARIABLE ')' ';'?                                # ProgramCancel
            | expression ';'?        # ExpressionStatement
            ; 
                    

assignmentStatement : <assoc=right> to=expression ASSIGN a=expression                                        ;
variableDeclaration : <assoc=right> ty=typeOrVar assignments+=assignment (',' assignments+=assignment)*  ;

shiftOp     :  GREATER GREATER GREATER
            |  GREATER GREATER
            |  LESS LESS
            ;

//Operators
ASSIGN      :       ':='    ; 
MINUS       :       '-'     ;
NOT         :       '!'     ;
MULTIPLY    :       '*'     ;
DIVIDE      :       '/'     ;
MOD         :       '%'     ;
PLUS        :       '+'     ;
LESS        :       '<'     ;
LESS_EQ     :       '<='    ;
GREATER_EQ  :       '>='    ;
GREATER     :       '>'     ;
EQUAL       :       '=='    ;
NOT_EQUAL   :       '!='    ;
BIT_NOT     :       '~'     ;
BIT_AND     :       '&'     ;
BIT_OR      :       '|'     ;
LOG_AND     :       '&&'    ;
LOG_OR      :       '||'    ;
BIT_XOR     :       '^'     ;
// LOG_RSH         :       '>>>'   ;
// ARITH_RSH       :       '>>'    ;
// LSH             :       '<<'    ;
MAPS_TO     :       '->'    ;


//Separators
LPAR        :     '('     ;
RPAR        :     ')'     ;
LBRC        :     '['     ;
RBRC        :     ']'     ;
LSQB        :     '{'     ;
RSQB        :     '}'     ;
SEMICOLON   :     ';'     ;
COLON       :     ':'     ;
QUOTE       :     '"'     ;
COMMA       :     ','     ;
ELLIPSIS    :     '...'   ;

/* 
 * Types
 */

//Used for when we can either provide a type or a variable (needed bc var arrays are not allowed).
typeOrVar       : type | TYPE_VAR  ;

protocol        : <assoc=right> protos+=subProtocol (';' protos+=subProtocol)*?
                | '(' protos+=subProtocol (';' protos+=subProtocol)*? ')'
                | protos+=subProtocol
                ;

subProtocol     :   '+' ty=type                 # RecvType
                |   '-' ty=type                 # SendType
                |   '?' proto=protocol          # WnProto
                |   '!' proto=protocol          # OcProto
                |    EXTERNAL_CHOICE LESS protoOpts+=protoBranch (COMMA protoOpts+=protoBranch)+ GREATER     # ExtChoiceProto
                |    INTERNAL_CHOICE LESS protoOpts+=protoBranch (COMMA protoOpts+=protoBranch)+ GREATER     # IntChoiceProto
                |    CLOSEABLE LESS proto=protocol GREATER   # CloseableProto // TODO: NAME BETTER?
                ;

protoBranch     : protocol                      
                | lbl=VARIABLE ':' protocol
                ; 


//Allows us to have a type of ints, bools, or strings with the option for them to become 1d arrays. 
type    :    ty=type LBRC len=DEC_LITERAL RBRC                                          # ArrayType
        |    ty=type LBRC RBRC                                                      # DynArrayType
        |    ty=(
                  TYPE_INT 
                | TYPE_I32
                | TYPE_BOOL 
                | TYPE_STR 
                | TYPE_UNIT 
                | TYPE_U32 
                | TYPE_I64 
                | TYPE_U64)                       # BaseType
        |    paramTypes+=type (COMMA paramTypes+=type)* MAPS_TO returnType=type     # LambdaType
        |    LPAR (paramTypes+=type (COMMA paramTypes+=type)*)? RPAR MAPS_TO (returnType=type | LPAR RPAR) # LambdaType
        |    LPAR (paramTypes+=type (COMMA paramTypes+=type)*)? MAPS_TO (returnType=type | LPAR RPAR) RPAR # LambdaType
        |    LPAR LPAR (paramTypes+=type (COMMA paramTypes+=type)*)? RPAR MAPS_TO (returnType=type | LPAR RPAR) RPAR # LambdaType
        |    LPAR type (PLUS type)+ RPAR                                            # SumType 
        |    TYPE_CHANNEL LESS proto=protocol GREATER                               # ChannelType
        |    TYPE_PROGRAM LESS proto=protocol GREATER                               # ProgramType
        |    TYPE_BOX     LESS ty=type GREATER                                      # BoxType
        |    ty=type  genericSpecifier                                              # TemplatedType
        |    path                                                                   # CustomType
        ;

// TODO: not convinced about the whole {u,i}{32,64} thing as it kinda seems like needing to know more metaphors.. and lower level?

//Integer 
integerValue        :   (DEC_LITERAL | HEX_LITERAL | BIN_LITERAL) ty=(TYPE_I32 | TYPE_U32 | TYPE_I64 | TYPE_U64)?   ;  //Negative numbers handled by unary minus 

DEC_LITERAL         :  DEC_DIGIT+               ;
fragment DEC_DIGIT  :  [0-9]                    ;

HEX_LITERAL         :  '0x' HEX_DIGIT+          ; 
fragment HEX_DIGIT  :  [0-9A-Fa-f]              ;

BIN_LITERAL         : '0b' BIN_DIGIT+           ;
fragment BIN_DIGIT  : [01]                      ;



TYPE_INT        :   'int'       ; 
TYPE_I32        :   'i32'       ;
TYPE_U32        :   'u32'       ;
TYPE_I64        :   'i64'       ;
TYPE_U64        :   'u64'       ; 
TYPE_BOOL       :   'boolean'   ;
TYPE_STR        :   'str'       ; 
TYPE_UNIT       :   'Unit'      ;
TYPE_VAR        :   'var'       ;
TYPE_BOX        :   'Box'       ;
TYPE_PROGRAM    :   'Program'   ;
TYPE_CHANNEL    :   'Channel'   ;

//Others
FUNC            :   'func'  ;
ENUM            :   'enum'  ;
STRUCT          :   'struct';
IF              :   'if'    ;
ELSE            :   'else'  ;
WHILE           :   'while' ;
RETURN          :   'return';
SELECT          :   'select';
EXTERN          :   'extern';
MATCH           :   'match' ;
DEFINE          :   'define';
EXIT            :   'exit'  ;
EXEC            :   'exec'  ;
COPY            :   'copy'  ;
IMPORT          :   'import';

// Protocols   
EXTERNAL_CHOICE :   'ExternalChoice'    ;
INTERNAL_CHOICE :   'InternalChoice'    ;
CLOSEABLE        :  'Cancelable'        ;



//Booleans
booleanConst        :   TRUE | FALSE ; 
FALSE               :   'false' ; 
TRUE                :   'true'  ; 


/*
 * Strings
 */

//Strings start with a quote and then contain as many 
//Escaped charaters or safe characters for a string to 
//contain (basically anything except for a \ or a " as these designate
//either the end of the string, or an escape character). 
//Finally, the string is ended by a quote. 
STRING      :   QUOTE (ESCAPE_STRING | SAFE_STRING)* QUOTE;

//Variables 
VARIABLE    :     [a-zA-Z][a-zA-Z0-9_]*  ;

//String escapes are a \ that must be followed by any character
fragment ESCAPE_STRING  : '\\'. ; 
//Without an escape, strings cannot include a quote (that represents end of string)
//nor can they include a slash (that would start an escape)
fragment SAFE_STRING : ~["\\]    ;


/*
    Bismuth has two types of comments, inline comments and standard comments. 
    Inline comments start with a '#' character that is not in a string 
    literal, and continue to the end of the line (or end of file if this 
    is the last line of the program).

    Standard comments begin with a "/*" sequence and end with a matching 
    "*\/" sequence.  Standard comments may be nested.

    Whitespace consists of this set of characters `[ \t\r\n\f]` 
    (not including the brackets). Comments and whitespace are not passed 
    to the parser from the scanner.
 */
 
//Inline comments start with a # and go to the end of line. NOTE: ANTLR uses ~ instead of ^ for negation in regex
INLINE_COMMENT  :   '#' .*? ('\n'|EOF)  -> skip;

/*
 * Regular comments start with /* and go until *\/ while supporting nesting comments. 
 * To achieve this, after the start of a nested comment with /*, we allow the comment 
 * to contain another regular comment, and we otherwise do not allow them to contain 
 * /* or *\/. This ensures proper nesting or a syntax error. By then using the non-greedy
 * repitition rule (*?), we make sure that we close out the nested comment on the first valid *\/
 * that we encounter. This step might not be needed given the explicit disallow of /* and *\/
 * in the comment outside of another comment, but I figure that its probably a good practice
 * to leave it in there.  
 */
STD_COMMENT     :   '/*'  (STD_COMMENT | '/'~'*' | ~'*''/' | ~'/')*? '*/' -> skip ;  

//Typical whitespace skip
WS  : [ \t\r\n\f]+ -> skip; 