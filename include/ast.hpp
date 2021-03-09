#ifndef ast_hpp
#define ast_hpp

#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_statement.hpp"

typedef std::vector<Decl *> Program;

// At the top-level, a program is a sequence of declarations
extern Program parseAST();

#endif
