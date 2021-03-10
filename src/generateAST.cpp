#include "ast.hpp"

void print_tree(Program prog) {
    std::cout << "PRINTING TREE!" << std::endl;
    std::cout << prog.size() << " top-level declarations found." << std::endl;
    for(auto const& decl_node: prog) {
        std::cout << *(decl_node->name);
    }
}


int main()
{

    typedef std::vector<Node *> Program;

    // Parse the AST
    Program ast=parseAST();

    print_tree(ast);


    return 0;

}
