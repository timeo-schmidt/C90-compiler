%code requires{
  #include "ast.hpp"
  
  #include <cassert>
  #include <string>

  typedef std::vector<Node *> Program;
  extern Program g_root;

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

}

// Represents the value associated with any kind of AST node.
%union{
    Node *node;
    struct type *type;
    std::string *string;
    double number;
}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF NUMBER
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN


%type <node> external_declaration function_definition declarator identifier_type direct_declarator compound_statement declaration_list statement declaration_specifiers expression_statement statement_list init_declarator_list constant_type primary_expression additive_expression multiplicative_expression postfix_expression unary_expression cast_expression shift_expression  relational_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assignment_expression expression constant_expression declaration init_declarator equality_expression initializer
%type <string> STRING_LITERAL IDENTIFIER type_specifier  string_literal_type unary_operator assignment_operator
%type <number> CONSTANT 

%start program_start

%%

primary_expression
    : identifier_type       { $$ = $1; }
	| constant_type         { $$ = $1; }
	| string_literal_type   { ; }
	| '(' expression ')'    { ; }
	;

constant_type
    : CONSTANT         { $$ = new Number( $1 ); }
    ;

identifier_type
    : IDENTIFIER       { $$ = new Variable( *$1 ); delete $1; }

string_literal_type
    : STRING_LITERAL   { ; }

postfix_expression
    : primary_expression											{ $$=$1; }
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
    : assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
    : postfix_expression									{ $$ = $1; }
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression						{ $$ = new UnaryExpression(*$1, $2); delete $1; }
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
    : '&'													{$$=new std::string("&");}
	| '*'													{$$=new std::string("*");}
	| '+'													{$$=new std::string("+");}
	| '-'													{$$=new std::string("-");}
	| '~'													{$$=new std::string("~");}
	| '!'													{$$=new std::string("!");}
	;

cast_expression
    : unary_expression											{$$ = $1;}
	| '(' type_name ')' cast_expression							
	;

multiplicative_expression
    : cast_expression											{ $$ = $1;}
	| multiplicative_expression '*' cast_expression 			{ $$ = new MulOperator($1, $3); }
	| multiplicative_expression '/' cast_expression				{ $$ = new DivOperator($1, $3); }
	| multiplicative_expression '%' cast_expression				
	;

additive_expression
    : multiplicative_expression									{$$ = $1;}
	| additive_expression '+' multiplicative_expression 		{$$ = new AddOperator($1, $3);}
	| additive_expression '-' multiplicative_expression			{$$ = new SubOperator($1, $3);} 
	;

shift_expression
    : additive_expression										{$$ = $1;}
	| shift_expression LEFT_OP additive_expression				{$$ = new LShiftOperator($1, $3);}
	| shift_expression RIGHT_OP additive_expression				{$$ = new RShiftOperator($1, $3);}
	;

relational_expression
    : shift_expression											{$$ = $1;}
	| relational_expression '<' shift_expression			
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
    : relational_expression										{$$ = $1;}	
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression													
    : equality_expression										{$$ = $1;}	
	| and_expression '&' equality_expression
	;

exclusive_or_expression
    : and_expression											{$$ = $1;}
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
    : exclusive_or_expression									{$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
    : inclusive_or_expression									{$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
    : logical_and_expression									{$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
    : logical_or_expression														{$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
    : conditional_expression													{$$ = $1;}
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
    : '='															{  $$=new std::string("="); }
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
    : assignment_expression											{$$ = $1;}	
	| expression ',' assignment_expression
	;

constant_expression
    : conditional_expression										{$$ = $1;}
	;






declaration
    : declaration_specifiers ';'									 { $$=new VarDecl($1, nullptr, nullptr, nullptr, nullptr); }
	| declaration_specifiers init_declarator_list ';'  { ; }		 { $$=new VarDecl($1, $2, nullptr, nullptr, nullptr);  }
	;

declaration_specifiers
    : storage_class_specifier                           { ; }
	| storage_class_specifier declaration_specifiers    { ; }
	| type_specifier                                    { $$=new Variable( *$1 ); delete $1; }
	| type_specifier declaration_specifiers             { ; }
	| type_qualifier                                    { ; }
	| type_qualifier declaration_specifiers             { ; }
	;

init_declarator_list
    : init_declarator												{$$ = $1;}
	| init_declarator_list ',' init_declarator
	;

init_declarator
    : declarator													{$$ = $1;}
	| declarator '=' initializer									{$$ = new VarDecl(nullptr, $1, $3, nullptr, nullptr); }
	;

storage_class_specifier
    : TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
    : VOID                          { $$=new std::string("void"); }
	| CHAR                          { $$=new std::string("char"); }
	| SHORT                         { $$=new std::string("short"); }
	| INT                           { $$=new std::string("int"); }
	| LONG                          { $$=new std::string("long"); }
	| FLOAT                         { $$=new std::string("float"); }
	| DOUBLE                        { $$=new std::string("double"); }
	| SIGNED                        { $$=new std::string("signed"); }
	| UNSIGNED                      { $$=new std::string("unsigned"); }
	| struct_or_union_specifier     { $$=new std::string("placeholder"); }
	| enum_specifier                { $$=new std::string("placeholder"); }
	| TYPE_NAME                     { $$=new std::string("type_name"); }
	;

struct_or_union_specifier
    : struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
    : STRUCT
	| UNION
	;

struct_declaration_list
    : struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
    : specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
    : struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
    : declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
    : ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
    : enumerator
	| enumerator_list ',' enumerator
	;

enumerator
    : IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
    : CONST
	| VOLATILE
	;

declarator
    : pointer direct_declarator                         { ; }
	| direct_declarator                                 { $$=$1; }
	;

direct_declarator
    : identifier_type                                   { $$= $1; }
    | identifier_type '(' ')'                           { $$= $1; /* Check later! */} 
	| '(' declarator ')'                                { ; }
	| direct_declarator '[' constant_expression ']'     { ; }
	| direct_declarator '[' ']'                         { ; }
	| direct_declarator '(' parameter_type_list ')'     { ; }
	| direct_declarator '(' identifier_list ')'         { ; }
	;

pointer
    : '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
    : type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
    : parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list
    : parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
    : declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
    : IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
    : specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
    : pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
    : '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
    : assignment_expression									{ $$ = $1; }
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
    : initializer
	| initializer_list ',' initializer
	;

statement
    : labeled_statement
	| compound_statement
	| expression_statement									{$$ = $1;}
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
    : IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
    : '{' '}'                                   { $$ = new Variable("{ }"); }
	| '{' statement_list '}'                    { $$ = $2; }
	| '{' declaration_list '}'                  { $$ = $2; }
	| '{' declaration_list statement_list '}'   { ; }
	;

declaration_list
    : declaration                               { $$=$1; }
	| declaration declaration_list              { ; }
	;

statement_list
    : statement                     { $$ = $1; }
    | statement_list statement      { ; }
	;

expression_statement
    : ';'							
	| expression ';'				{$$ = $1;}
	;

selection_statement
    : IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
    : WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
    : GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

program_start
    : external_declaration                  { g_root.push_back($1); }
	| program_start external_declaration    { g_root.push_back($2); }
	;

external_declaration
    : function_definition
	| declaration
	;

function_definition
    : declaration_specifiers declarator declaration_list compound_statement     { ; }
	| declaration_specifiers declarator compound_statement                      { $$= new FuncDecl($1, $2, nullptr, $3, nullptr); }
	| declarator declaration_list compound_statement                            { ; }
	| declarator compound_statement                                             { ; }
	;

%%

Program g_root;

Program parseAST()
{
    yyparse();
    return g_root;
}