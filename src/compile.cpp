#include "ast.hpp"

#include <fstream>




int main(int argc, char *argv[]) {

    // Parsing and AST Generation
    typedef std::vector<Node *> Program;
    Program ast=parseAST();

    // Code Generation
    std::map<std::string,double> bindings;
    std::unordered_multimap<std::string,struct varData> variables;

    struct Data data;

    for(auto const& decl_node: ast) {
        (decl_node->codegen("$s0", data, bindings, variables));
    }

    // extracting variable information
    for(const auto& u : variables)
    { std::cout<<u.first << "  " << u.second.memSize << "  " << u.second.offset << " " <<u.second.scope <<std::endl;}


}
