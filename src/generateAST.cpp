#include "ast.hpp"
#include <fstream>

/*
void print_tree(Program prog) {
    std::cout << "PRINTING TREE!" << std::endl;
    std::cout << prog.size() << " top-level declarations found." << std::endl;
    for(auto const& decl_node: prog) {
        (decl_node->print(std::cout));
    }
}

// The goal of this function is to output a tree in the .dot format
void draw_tree(Program prog, std::string file_name="program_ast.dot") {

    std::ofstream dotfile(file_name);

    dotfile << "digraph ast_graph" << std::endl;
    dotfile << "{" << std::endl;
    dotfile << "node[shape=record];" << std::endl;

    for(const auto& node: prog) {
        node->draw_tree_node(dotfile);
    }

    dotfile << std::endl << "}";
    dotfile.close();
}
*/
int main()
{

    typedef std::vector< Node *> Program;

    // Parse the AST
    Program ast=parseAST();

    //draw_tree(ast);
    //std::cout << ast[0]->getDeclerator() << std::endl;
    std::cout << ast[0]->getDeclarationSpecifiers() << std::endl;
    std::cout << ast[0]->getInitDeclarator()  << std::endl;
    std::cout << ast[0]->getCompoundStatement() << std::endl;
//    print_tree(ast);
   

    return 0;


}
