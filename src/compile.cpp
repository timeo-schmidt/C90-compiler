#include "ast.hpp"

#include <fstream>




int main(int argc, char *argv[])
{
typedef std::vector<Node *> Program;

    // Parse the AST
    Program ast=parseAST();




    std::map<std::string,double> bindings;
    std::unordered_map<std::string,struct varData> variables;

   int stack;

for(auto const& decl_node: ast) {
         (decl_node->codegen("$s0", stack, bindings, variables));
}

// extracting variable information
//for(const auto& u : variables)
//{ std::cout<<u.first << "  " << u.second.memSize << "  " << u.second.offset <<std::endl;}

    
}