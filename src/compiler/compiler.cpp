#include "ast.hpp"

#include <fstream>

int main(int argc, char *argv[])
{
   const Expression *parsed=parseAST();

    //std::cout<<std::endl<<"--- Assembly Code with infinate registers ---"<<std::endl<<std::endl;

    std::map<std::string,double> bindings;
    std::map<std::string,double> context;

    bindings.insert(std::pair<std::string, double>("3", 3));
    bindings.insert(std::pair<std::string, double>("-", 0));
    context.insert(std::pair<std::string, double>("a", 52));

    stackData stack;
	 stack.stackSize = -64; 
	 stack.stackOffset = 0;



    parsed->codegen("$s5", stack, bindings, context);
    
}
