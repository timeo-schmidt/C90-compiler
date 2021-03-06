#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_node.hpp"


class Expr
    : public Node
{
public:
    std::string kind;
    Expr *left;
    Expr *right;
    const char *name;
    int integer_value;
    std::string string_literal;

    Expr(std::string kind_in, Expr *left_in, Expr *right_in, const char *name_in, int integer_value_in, std::string string_literal_in) {
        kind=kind_in;
        left=left_in;
        right=right_in;
        name=name_in;
        integer_value=integer_value_in;
        string_literal=string_literal_in;
    }
};

#endif
