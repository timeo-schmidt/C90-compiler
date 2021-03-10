#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>

// Auxillary struct types
struct type {
    std::string kind;
    struct type *subtype;
    struct param_list *params;
    type(std::string kind_in, struct type *subtype_in, struct param_list *params_in) {
        kind=kind_in;
        subtype=subtype_in;
        params=params_in;
    }
};
struct param_list {
    std::string *name;
    struct type *type;
    struct param_list *next;
    param_list(std::string *name_in, struct type *type_in, struct param_list *next_in) {
        name=name_in;
        type=type_in;
        next=next_in;
    }
};

class Node;

typedef const Node *NodePtr;

typedef enum {
    FUNCTION_DEFINITION,    // type, name, code
    IDENTIFIER_NAME        // name
} kind_t;


class Node
{
public:

    kind_t kind;
    std::string *name;
    struct type *type;
    Node *next;

    // Stmt
    Node *decl;
    Node *init_expr;
    Node *expr;
    Node *next_expr;
    Node *body;
    Node *else_body;

    // Expr
    Node *left;
    Node *right;

    // Decl
    Node *value;
    Node *code;


    double integer_value;
    std::string *string_literal;

    virtual ~Node() {}

    Node(
        kind_t kind_in,
        std::string *name_in,
        struct type *type_in,
        Node *next_in,
        Node *decl_in,
        Node *init_expr_in,
        Node *expr_in,
        Node *next_expr_in,
        Node *body_in,
        Node *else_body_in,
        Node *left_in,
        Node *right_in,
        Node *value_in,
        Node *code_in,
        double integer_value_in,
        std::string *string_literal_in
    ){
        kind=kind_in;
        name=name_in;
        type=type_in;
        next=next_in;
        decl=decl_in;
        init_expr=init_expr_in;
        expr=expr_in;
        next_expr=next_expr_in;
        body=body_in;
        else_body=else_body_in;
        left=left_in;
        right=right_in;
        value=value_in;
        code=code_in;
        integer_value=integer_value_in;
        string_literal=string_literal_in;
    }
    Node() {}
};

Node *generate_identifier(std::string *name);

Node *generate_function_definition(type *type, Node* name, Node *code);

#endif
