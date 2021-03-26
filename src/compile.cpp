#include "ast.hpp"

#include <fstream>




int main(int argc, char *argv[]) {

    // Parsing and AST Generation
    typedef std::vector<Node *> Program;
    Program ast=parseAST();

    // Code Generation
    std::map<std::string,double> bindings;
    std::unordered_multimap<std::string,struct varData> variables;
    struct varData a;
    a.scope = -2;
    std::pair <std::string,struct varData> b;
    b = std::make_pair("___filler1___",a);
    variables.insert(b);
    std::pair <std::string,struct varData> c;
    c = std::make_pair("___filler2___",a);
    variables.insert(c);


    struct Data data;

    for(auto const& decl_node: ast) {
        (decl_node->codegen("$s0", data, bindings, variables));
    }

    // extracting variable information
    //for(const auto& u : variables)
   // { std::cout<<u.first << "  " << u.second.memSize << "  " << u.second.offset << " " <<u.second.scope <<std::endl;}


}
