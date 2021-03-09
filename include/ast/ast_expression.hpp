#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_node.hpp"

/*

Usage of the Expr class:

    --> document the use of various expression types here.

    Examples:
        !x
        f(a,b,c)
        a==b
        a++
        5
        "abc"

    Kinds:
        EXPR_ADD
        EXPR_SUB
        EXPR_MUL
        EXPR_DIV
        EXPR_NOT
        EXPR_NAME
        EXPR_CONSTANT
        EXPR_STRING_LITERAL

*/

class Expr
    : public Node
{
public:
    std::string *kind;
    Expr *left;
    Expr *right;
    std::string *name;
    double integer_value;
    std::string *string_literal;

    Expr(std::string *kind_in, Expr *left_in, Expr *right_in, std::string *name_in, double integer_value_in, std::string *string_literal_in) {
        kind=kind_in;
        left=left_in;
        right=right_in;
        name=name_in;
        integer_value=integer_value_in;
        string_literal=string_literal_in;
    }
};

#endif
