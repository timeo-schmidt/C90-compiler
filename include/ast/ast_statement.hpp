#ifndef ast_statement_hpp
#define ast_statement_hpp

#include "ast_node.hpp"

class Stmt
    : public Node
{
public:
    std::string kind;
    Decl *decl;
    Expr *init_expr;
    Expr *expr;
    Expr *next_expr;
    Stmt *body;
    Stmt *else_body;
    Stmt *next;

    Stmt(std::string kind_in, Decl *decl_in, Expr *init_expr_in, Expr *expr_in, Expr *next_expr_in, Stmt *body_in, Stmt *else_body_in, Stmt *next_in) {
        kind=kind_in;
        decl=decl_in;
        init_expr=init_expr_in;
        expr=expr_in;
        next_expr=next_expr_in;
        body=body_in;
        else_body=else_body_in;
        next=next_in;
    }
};

#endif