#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>

// Forward declarations
class Decl;
class Expr;
class Stmt;

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

class Node
{
public:
    virtual ~Node() {}
};

#endif
