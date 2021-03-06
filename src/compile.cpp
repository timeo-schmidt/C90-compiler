#include "ast.hpp"

#include <fstream>

int main(int argc, char *argv[])
{
   const Node *parsed=parseAST();

    //std::cout<<std::endl<<"--- Assembly Code with infinate registers ---"<<std::endl<<std::endl;

    std::map<std::string,double> bindings;

    bindings.insert(std::pair<std::string, double>("3", 3));
    bindings.insert(std::pair<std::string, double>("-", 0));
    bindings.insert(std::pair<std::string, double>("5", 5));




    parsed->CodeGen("reg0", bindings);
    
}