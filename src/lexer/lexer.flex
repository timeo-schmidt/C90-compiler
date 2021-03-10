%option noyywrap

%{
// Avoid error  "error: `fileno' was not declared in this scope"
    extern "C" int fileno(FILE *stream);

#include "../parser/parser.tab.hpp"

%}

%%

[*]                         { return T_TIMES; }
[+]                         { return T_PLUS; }
[\^]                        { return T_EXPONENT; }
[-]                         { return T_MINUS; }
[/]                         { return T_DIVIDE;}

[=]                         { return T_EQUALS;}

[(]                         { return T_LBRACKET; }
[)]                         { return T_RBRACKET; }
[{]                         { return T_OPEN;}
[}]                         { return T_CLOSE;}

log                         { return T_LOG; }
exp                         { return T_EXP; }
sqrt                        { return T_SQRT; }

[0-9]+([.][0-9]*)?          { yylval.number=strtod(yytext, 0); return T_NUMBER; }
[a-z]+                      { yylval.string=new std::string(yytext); return T_VARIABLE; }
[A-Z]+                      { yylval.string=new std::string(yytext); return T_TYPE; }



[ \t\r\n]+		            {;}

.                           { fprintf(stderr, "Invalid token\n"); exit(1); }

%%

void yyerror  (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}