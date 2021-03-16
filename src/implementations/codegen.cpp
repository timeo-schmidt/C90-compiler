#include "ast.hpp"

// This file contains all function definitions for the code generation functionality.


// ast_declaration.hpp

void FuncDecl::codegen(
     std::string destReg,
     stackData stack,
     std::map<std::string,double> &bindings,
     std::unordered_map<std::string,struct varData> &variables
) const {
    name->print(std::cout);
    std::cout << ":" <<std::endl;
    std::cout<< "addiu " << "$sp, " << "$sp, " << stack.stackSize << std::endl;
    std::cout<<"nop"<<std::endl;
    std::cout << "sw $ra, " << (-stack.stackSize-4) << "($sp)" <<std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $fp, " << (-stack.stackSize-8) << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s0, 4($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s1, 8($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s2, 12($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, 16($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s4, 20($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s5, 24($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s6, 28($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s7, 32($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "move $fp, $sp" << std::endl;

    // store location & name of argument variables //
    // this will need to be updated when argument variables can be other types
    std::cout << "nop" << std::endl;
    std::cout << "sw $a0, 36($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $a1, 40($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $a2, 44($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $a3, 48($sp)" << std::endl;

    // storing argument variables to memory
    // will need to change when arguments can be of different types
    struct varData a; a.offset = 36; a.memSize = 1;
          variables["argument_0"] = a;
            a.offset = 40; a.memSize = 1;
          variables["argument_1"] = a;
            a.offset = 44; a.memSize = 1;
          variables["argument_2"] = a;
            a.offset = 48; a.memSize = 1;
          variables["argument_3"] = a;

          stack.stackOffset = 52;

    // check if a code is nullptr for f(){} case
            if(code != nullptr)
            { code->codegen(destReg, stack, bindings, variables); }

    std::cout << "nop" << std::endl;
    std::cout << "lw $s0, 4($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s1, 8($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s2, 12($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s3, 16($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s4, 20($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s5, 24($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s6, 28($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s7, 32($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $ra, " << (-stack.stackSize-4) << "($sp)" <<std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $fp, " << (-stack.stackSize-8) << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "move $sp, $fp" << std::endl;
    std::cout << "jr $ra" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << ".global ";
    name->print(std::cout);
    std::cout << std::endl;

 }


void VarDecl::codegen(
     std::string destReg,
     stackData stack,
     std::map<std::string,double> &bindings,
     std::unordered_map<std::string,struct varData> &variables
) const {

    //Putting assignment value in $s0

   // TO DO: impliment the types, then un comment this stuff

    //if(type != nullptr)
    //{ type->codegen("$s0", stack, bindings, variables); }

    if(name != nullptr)
    { name->codegen("$s0", stack, bindings, variables); }

    std::cout << "sw $s0, " << stack.stackOffset << "($sp)" << std::endl;

     // Storing variable name in variables and type TODO
    struct varData a;
    a.offset = stack.stackOffset;
    a.memSize = 1;
    variables[name->getName()] = a;

    stack.stackOffset += 4;

}

void initDecl::codegen(
    std::string destReg,
    stackData stack,
    std::map<std::string,double> &bindings,
    std::unordered_map<std::string,struct varData> &variables
) const {
    // Getting initiliser and loading into $s0
    if(initializer != nullptr)
        { initializer->codegen("$s0", stack, bindings, variables); }
    else
        { std::cout<<"addiu $s0, $0, $0"<<std::endl;}
}
