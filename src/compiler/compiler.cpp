#include "ast.hpp"

#include <fstream>

int main(int argc, char *argv[])
{
   const Expression *parsed=parseAST();

    std::cout<<std::endl<<"--- Assembly Code with infinate registers ---"<<std::endl<<std::endl;

    parsed->codegen();
    
}
