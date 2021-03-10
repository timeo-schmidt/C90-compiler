#ifndef ast_node_constructor_decl_hpp
#define ast_node_constructor_decl_hpp

#include "ast_node.hpp"
#include <string>
#include <iostream>

Node *generate_identifier(std::string *name) {
    return new Node();
}

Node *generate_function_definition(type *type, Node* name, Node *code) {
    //Node* func_def = new Node();
    return new Node();
}

#endif
