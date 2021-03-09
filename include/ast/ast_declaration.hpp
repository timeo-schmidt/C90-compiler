#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include "ast_node.hpp"


class Decl
    : public Node
{
public:
    std::string *name;
    type *type;
    Expr *value;
    Stmt *code;
    Decl *next;

    Decl(std::string *name_in, struct type *type_in, Expr *value_in, Stmt *code_in, Decl *next_in) {
        name=name_in;
        type=type_in;
        value=value_in;
        code=code_in;
        next=next_in;
    }

    Decl() {
        name=new std::string("placeholder");
        type=nullptr;
        value=nullptr;
        code=nullptr;
        next=nullptr;
    }
};

#endif
