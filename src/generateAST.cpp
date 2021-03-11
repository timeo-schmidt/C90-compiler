#include "ast.hpp"


void print_tree(Program prog) {
    std::cout << "PRINTING TREE!" << std::endl;
    std::cout << prog.size() << " top-level declarations found." << std::endl;
     for(auto const& decl_node: prog) {
         (decl_node->print(std::cout));
    }
    }


int main()
{

    typedef std::vector< Node *> Program;

    // Parse the AST
     Program ast=parseAST();

    print_tree(ast);

 //
   // std::cout<<std::endl;

    return 0;


}
