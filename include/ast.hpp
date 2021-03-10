#ifndef ast_hpp
#define ast_hpp

#include <vector>

#include "ast/ast_node.hpp"
#include "ast/node_constructor_decl.cpp"
#include "ast/node_constructor_expr.cpp"
#include "ast/node_constructor_stmt.cpp"

typedef std::vector<Node *> Program;

// At the top-level, a program is a sequence of declarations
extern Program parseAST();

#endif
