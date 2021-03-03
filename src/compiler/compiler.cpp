#include "ast.hpp"

#include <fstream>

int main(int argc, char *argv[])
{
   const Expression *parsed=parseAST();

    std::cout<<"its coming"<<std::endl;
    parsed->codegen();
    
}
