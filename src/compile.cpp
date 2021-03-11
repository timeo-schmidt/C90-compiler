#include "ast.hpp"

#include <fstream>




int main(int argc, char *argv[])
{
  typedef std::vector< Node *> Program;

    // Parse the AST
    Program ast=parseAST();




    std::map<std::string,double> bindings;
    std::unordered_map<std::string,struct varData> variables;

    struct stackData stack; 
    stack.stackSize = -64; 
	stack.stackOffset = 0;

for(auto const& decl_node: ast) {
         (decl_node->codegen("$s5", stack, bindings, variables));
    }

    
}