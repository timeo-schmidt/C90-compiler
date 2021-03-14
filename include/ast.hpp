#ifndef ast_hpp
#define ast_hpp

#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_type.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_statement.hpp"


#include "ast/unique_name.hpp"

typedef std::vector<Node *> Program;

// At the top-level, a program is a sequence of declarations
extern Program parseAST();

#endif
