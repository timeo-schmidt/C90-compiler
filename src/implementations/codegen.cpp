#include "ast.hpp"
#include <utility>
// This file contains all function definitions for the code generation functionality.



//////////////////////////////////////////////
// ast_declaration.hpp
//////////////////////////////////////////////

void FuncDecl::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    std::cout << initDeclarator->getName();
    std::cout << ":" <<std::endl;
    std::cout<< "addiu " << "$sp, " << "$sp, " << "-8000"  << std::endl;
    std::cout<<"nop"<<std::endl;
    std::cout << "sw $ra, 4($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $fp, 8($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s0, 12($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s1, 16($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s2, 20($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, 24($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s4, 28($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s5, 32($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s6, 36($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s7, 40($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "move $fp, $sp" << std::endl;
    std::cout << "nop" << std::endl;
    
    data.stack  = 44;
    data.scope  += 1;
    // Evaluating arguments

    if(initDeclarator != nullptr)
	{initDeclarator->codegen(destReg, data,  bindings, variables); }
	

    // check if a code is nullptr for f(){} case
	if(compoundStatement != nullptr)
	{compoundStatement->codegen(destReg, data,  bindings, variables); }
    
   // std::cout<<data.scope<<std::endl;
   //scopeDecrement(data.scope, variables);
   // std::cout<<data.scope<<std::endl;
    
    std::cout << ".global ";
    std::cout << initDeclarator->getName() << std::endl;
    std::cout << std::endl;
    
    }


void VarDecl::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {

    //Variable information:
    struct varData a;

    a.memSize = (declarationSpecifiers->getSize());

    // TO DO: impliment the types, then un comment this stuff
    //if(type != nullptr)
    //{ declarationSpecifiers->codegen("$s0", data, bindings, variables); }

    if(initDeclarator != nullptr)
    { initDeclarator->codegen("$s0", data,  bindings, variables); }

    //std::cout << "sw $s0, " << stack  << "($sp)" << std::endl;

    // Storing variable name in variables
    a.offset = data.stack - 4;
    a.scope = data.scope;
    //variables[initDeclarator->getName()] = a;
    std::pair <std::string,struct varData> b;
    b = std::make_pair(initDeclarator->getName(),a);
    variables.insert(b);
    //variables.insert(std::pair<std::string,struct varData>(initDeclarator->getName(),a));
    //variables[initDeclarator->getName()] = a;

   // stack  += 4;

}

void funcDeclarator::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    if(parameterList != nullptr)
    {parameterList->codegen("$a0", data,  bindings, variables);}
}

void paramDecl::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    // Storing parameter information
    struct varData a; 
    a.offset = data.stack; 
    a.memSize = paramType->getSize();
    a.scope = data.scope;
    //variables.insert(std::make_pair<std::string,struct varData>(paramName->getName(),a));
    std::pair <std::string,struct varData> b;
    b = std::make_pair(paramName->getName(),a);
    variables.insert(b);



    // Storing parameter value
    std::cout << "sw " << destReg << ", " << data.stack<< "($sp)" << std::endl;
    data.stack+= 4;

    // Checking and doing next parameter
    if(next != nullptr)
    {
        int reg = ((destReg[2]) - '0');
        reg += 1;
        std::string x = "$a";
        x += reg + '0';

        next->codegen(x, data,  bindings, variables);
    }
}

void initDecl::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {
    // Getting initiliser and loading into $s0
    if(initializer != nullptr)
        { initializer->codegen("$s0", data, bindings, variables); }
    else
        {
            std::cout<<"sw $0, " << data.stack<< "($sp)" << std::endl;
            data.stack +=4;
            //std::cout<< "addiu " << "$sp, " << "$sp, " << 8  << std::endl;

        }
}

void NextState::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {
    // Evaluate current statement
    state->codegen(destReg, data, bindings, variables);

    // Evaluate next statement
    next->codegen(destReg, data, bindings, variables);
}


//////////////////////////////////////////////
// ast_operators.hpp
//////////////////////////////////////////////

void AddOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
    ) const {

    // Getting left side of addition and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);

    // Getting left side of addition
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;


    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    std::cout << "add $s3, $s1, $s0" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}


void SubOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of addition and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);

    // Getting left side of addition
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;


    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    std::cout << "sub $s3, $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}


void MulOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of mul and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of mul and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;

   
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    // Will need to change for different types

    std::cout << "mul $s3, $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}

void DivOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;

   
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    // Will need to change for different types

    std::cout << "div $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "mflo $3" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}


void LShiftOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::cout << "sllv $s3, $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}

void RShiftOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::cout << "srlv $s3, $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}

// NOTE: slt doesnt seem to work for either 10>10 or 10<10, passes for both ???????

void LThanOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::cout << "slt $s3, $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}

void GThanOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::cout << "slt $s3, $s1, $s0" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}

// FOR NOW works cause slt is broken ...

void LEThanOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    // Check if equal
    std::string EQUAL = makeName("EQUAL");
    std::string END = makeName("END");

    std::cout << "beq $s0, $s1, " << EQUAL << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "slt $s3, $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "j " << END << std::endl;
    std::cout << EQUAL << ":" << std::endl;
    std::cout << "add $s3, $0, $0" << std::endl;
    std::cout << END << ":" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack  += 4;

}

void GEThanOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::string EQUAL = makeName("EQUAL");
    std::string END = makeName("END");

    std::cout << "beq $s0, $s1, " << EQUAL << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "slt $s3, $s1, $s0" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "j " << END << std::endl;
    std::cout << EQUAL << ":" << std::endl;
    std::cout << "add $s3, $0, $0" << std::endl;
    std::cout << END << ":" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    
    data.stack  += 4;

}

void EQOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::string EQUAL = makeName("EQUAL");
    std::string END = makeName("END");

    std::cout << "beq $s1, $s0, " << EQUAL << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "add $s3, $0, $0" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "j " << END << std::endl;
    std::cout << EQUAL << ":" << std::endl;
    std::cout << "addi $s3, $0, 1" << std::endl;
    std::cout << END << ":" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    
    data.stack  += 4;

}

void NEOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::string EQUAL = makeName("EQUAL");
    std::string END = makeName("END");

    std::cout << "beq $s1, $s0, " << EQUAL << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "addi $s3, $0, 1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "j " << END << std::endl;
    std::cout << EQUAL << ":" << std::endl;
    std::cout << "addi $s3, $0, 0" << std::endl;
    std::cout << END << ":" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    
    data.stack  += 4;

}

//&& (logical and operator)

void ANDOperator::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

    // Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    std::string FALSE = makeName("FALSE");
    std::string END = makeName("END");

    std::cout << "beq $s0, $0, " << FALSE << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "beq $s1, $0, " << FALSE << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "addi $s3, $0, 1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "j " << END << std::endl;
    std::cout << FALSE << ":" << std::endl;
    std::cout << "addi $s3, $0, 0" << std::endl;
    std::cout << END << ":" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    
    data.stack  += 4;

}
void OROperator::codegen(
    std::string destReg,
    struct Data &data, 
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {
    throw std::runtime_error("OROperator::codegen not implemented.");
}

void BW_ANDOperator::codegen(
    std::string destReg,
    struct Data &data, 
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {
    throw std::runtime_error("BW_ANDOperator::codegen not implemented.");
}

void BW_ExclusiveOrOperator::codegen(
    std::string destReg,
    struct Data &data, 
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {
    throw std::runtime_error("BW_ExclusiveOrOperator::codegen not implemented.");
}

void BW_InclusiveOrOperator::codegen(
    std::string destReg,
    struct Data &data, 
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {
    throw std::runtime_error("BW_InclusiveOrOperator::codegen not implemented.");
}

// & bitwise operator:
/*
// Getting left side of div and loading into register
    getLeft()->codegen(destReg, data, bindings, variables);
  
    // Getting left side of div and loading into register
    getRight()->codegen(destReg, data, bindings, variables);

    // getting sum and storing destReg
    std::cout << "lw $s0, " << (data.stack - 8) <<"($sp)" << std::endl; // values will need to change when they start taking up more than one memory location
    std::cout << "nop" << std::endl;
 
    std::cout << "lw $s1, " << (data.stack - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;


    // Will need to change for different types

    std::cout << "and $s3, $s0, $s1" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s3, " << data.stack  << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    
    data.stack  += 4;

*/


//////////////////////////////////////////////
// ast_primitives.hpp
//////////////////////////////////////////////

void Variable::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

       // find variable stack location and TO DO:check size of variable but should check type...
        int kitkat = 0;
        int32_t location;
        int32_t size;
        for(int i = data.scope; i > -1; i--)
        {
            for(const auto& u : variables)
            {
                if( u.first == id && u.second.scope == i )
                {
                    location = u.second.offset;
                    size = u.second.memSize;
                    kitkat = 1;
                    break;
                } 
            }
        if(kitkat == 1)
        { break; }
        }
    
        //info = variables.at(id) ;
       

        // load into register
        std::cout << "lw $s0, "<< location<< "($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s0, " << data.stack  << "($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        data.stack += 4;

}

void Number::codegen(
    std::string destReg,
    struct Data &data,
    std::map<std::string,double> &bindings,
    std::unordered_multimap<std::string,struct varData> &variables
) const {

        // load into register
        std::cout << "addi $s0, $0, "<< value << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s0, " << data.stack  << "($sp)" << std::endl;
        std::cout << "nop" << std::endl;

        data.stack += 4;
}



//////////////////////////////////////////////
// ast_statement.hpp
//////////////////////////////////////////////

void returnState::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {

     // check if a expression is nullptr, not sure what to do if its return ; ???
	if(expression != nullptr)
	{ expression->codegen(destReg, data, bindings, variables); }

    std::cout << "nop" << std::endl;
    std::cout << "lw $s0, " << (data.stack  - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "move $v0, $s0" << std::endl;

    std::cout << "nop" << std::endl;
    std::cout << "lw $s0, 12($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s1, 16($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s2, 20($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s3, 24($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s4, 28($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s5, 32($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s6, 36($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $s7, 40($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $ra, 4($sp)" <<std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "lw $fp, 8($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "move $sp, $fp" << std::endl;
    std::cout << "jr $ra" << std::endl;
    std::cout << "nop" << std::endl;

}

void IfElseState::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {

    data.scope += 1;

    // Individual names for jumps
    std::string ELSE = makeName("ELSE");
    std::string L = makeName("L1");

    // Evaluate condition
    condition->codegen(destReg, data, bindings, variables);
    std::cout << "nop" << std::endl;
    std::cout << "lw $s0, " << (data.stack  - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout<<"beq $s0, $0, " << ELSE << std::endl;
    std::cout << "nop" << std::endl;

    // If condition is true: evaluate If
    if(If != nullptr)
    { If->codegen(destReg, data, bindings, variables); }

    std::cout << "j " << L << std::endl;
    std::cout << ELSE << ":" << std::endl;

    // Else branch to another location & evaluate else
    if(Else != nullptr)
    { Else->codegen(destReg, data, bindings, variables); }

    std::cout << L << ":" << std::endl;

    scopeDecrement(data.scope, variables);

 }

void WhileState::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {

    data.scope += 1;

    // Individual names for jumps
    std::string START = makeName("START");
    std::string EXIT = makeName("EXIT");

    // START
    std::cout << START << ":" << std::endl;

    // Evaulating expression
    expr->codegen(destReg, data, bindings, variables);
    std::cout << "nop" << std::endl;
    std::cout << "lw $s0, " << (data.stack  - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    // Checking if expression is true (if not jumpt to exit)
    std::cout<<"beq $s0, $0, " << EXIT << std::endl;
    std::cout << "nop" << std::endl;

    // Evaluating statement
    statem->codegen(destReg, data, bindings, variables);

    // Jumping to start
    std::cout << "j " << START << std::endl;

    // EXIT
    std::cout << EXIT << ":" << std::endl;

   // scopeDecrement(data.scope, variables);
}


void ForState::codegen(
     std::string destReg,
     struct Data &data, 
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    data.scope += 1;    
    throw std::runtime_error("Not implemented.");
    scopeDecrement(data.scope, variables);
}



//////////////////////////////////////////////
// ast_unary.hpp
//////////////////////////////////////////////

void Unary::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    throw std::runtime_error("Not implemented.");
}




//////////////////////////////////////////////
// ast_type.hpp
//////////////////////////////////////////////

void Type::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    throw std::runtime_error("Not implemented.");
}



//////////////////////////////////////////////
// ast_assign.hpp
//////////////////////////////////////////////

void VarAssign::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
      int kitkat = 0;
        int32_t location;
        int32_t size;
        std::string name = var->getName();
        for(int i = data.scope; i > -1; i--)
        {
            for(const auto& u : variables)
            {
                if( u.first == name && u.second.scope == i )
                {
                    location = u.second.offset;
                    size = u.second.memSize;
                    kitkat = 1;
                    break;
                } 
            }
        if(kitkat == 1)
        { break; }
        }

    // Obtaining variable memory location (will need to be updated when types)
   

    // Get new value
    expr->codegen(destReg, data, bindings, variables);
    std::cout << "lw $s0, " << (data.stack  - 4) <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;
    std::cout << "sw $s0, " << location <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;

}


void functionCall::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    
    // Loading parameter values to argument registers 
    if(params != nullptr)
    { params->codegen("$a0", data, bindings, variables);}



    // Calling function
    std::cout << "jal " << functName->getName() << std::endl;
    
    std::cout << "sw $v0, " << data.stack <<"($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    data.stack += 4;


}

void storeParams::codegen(
     std::string destReg,
     struct Data &data,
     std::map<std::string,double> &bindings,
     std::unordered_multimap<std::string,struct varData> &variables
) const {
    
    if(param != nullptr)
    { param->codegen(destReg, data, bindings, variables); }
   
    std::cout << "lw " << destReg << ", " << (data.stack-4) << "($sp)" << std::endl;
    std::cout << "nop" << std::endl;

    if(next != nullptr)
        {
            int reg = ((destReg[2]) - '0');
            reg += 1;
            std::string x = "$a";
            x += reg + '0';

            next->codegen(x, data,  bindings, variables);
        }
}