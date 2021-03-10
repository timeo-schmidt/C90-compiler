%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_EXPONENT T_EQUALS
%token T_LBRACKET T_RBRACKET T_OPEN T_CLOSE
%token T_LOG T_EXP T_SQRT 
%token T_NUMBER T_VARIABLE T_TYPE

%type <expr> EXPR TERM UNARY FACTOR VARIABLE TYPE DECLARATION
%type <number> T_NUMBER
%type <string> T_VARIABLE T_LOG T_EXP T_SQRT FUNCTION_NAME T_TYPE 

%start ROOT

// Precidence 

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE
%nonassoc U_MINUS
%right T_EXPONENT

%%

ROOT : EXPR                                 { g_root = $1; }


           
EXPR : EXPR T_PLUS EXPR                     { $$ = new AddOperator($1, $3); }
     | EXPR T_MINUS EXPR                    { $$ = new SubOperator($1, $3); }
     | TERM                                 { $$ = $1; } 
     | DECLARATION                          { $$ = $1; }
     

TERM : TERM T_TIMES TERM                    { $$ = new MulOperator($1, $3); }
     | TERM T_DIVIDE TERM                   { $$ = new DivOperator($1, $3); }
     | UNARY                                { $$ = $1; }
     | T_MINUS TERM  %prec U_MINUS          { $$ = new NegOperator($2); }
     | TERM T_EXPONENT TERM                 { $$ = new ExpOperator($1, $3); }

DECLARATION : TYPE VARIABLE T_EQUALS TERM   { $$ = new VarDeclaration( $1, $2, $4, $4); }
            | VARIABLE T_LBRACKET T_RBRACKET T_OPEN EXPR T_CLOSE  { $$ = new FuncDeclaration($1, $1, $5, $5); }
            | VARIABLE T_LBRACKET T_RBRACKET T_OPEN  T_CLOSE  { $$ = new FuncDeclaration($1, $1, nullptr, nullptr); }
            




UNARY : FACTOR                              { $$ = $1; }


FACTOR : T_NUMBER                           { $$ = new Number( $1 ); }
       | VARIABLE                           { $$ = $1; } 
       | T_LBRACKET EXPR T_RBRACKET         { $$ = $2; }
       | T_LOG T_LBRACKET EXPR T_RBRACKET   { $$ = new LogFunction( $3 ); }  
       | T_SQRT T_LBRACKET EXPR T_RBRACKET  { $$ = new SqrtFunction( $3 ); } 
       | T_EXP T_LBRACKET EXPR T_RBRACKET   { $$ = new ExpFunction( $3 ); } 

VARIABLE : T_VARIABLE                       { $$ = new Variable( *$1 ); delete $1; } 

TYPE : T_TYPE                               { $$ = new Type( *$1 ); delete $1;}

FUNCTION_NAME : T_LOG                       { $$ = new std::string("log"); }
              | T_SQRT                      { $$ = new std::string("sqrt"); }
              | T_EXP                       { $$ = new std::string("exp"); }


%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
