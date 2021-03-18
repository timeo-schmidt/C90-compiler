#include "ast.hpp"

// This file contains all function definitions for the text-based print functionality.



//////////////////////////////////////////////
// ast_declaration.hpp
//////////////////////////////////////////////



void FuncDecl::print(std::ostream &dst) const {
    /*std::cout << "FuncDecl" << std::endl;
    if(type != nullptr)
    { std::cout<<"FromType"<<std::endl; type->print(dst); }

    if(name != nullptr)
    { std::cout<<"FromName"<<std::endl; name->print(dst); }

    if(code != nullptr)
    { std::cout<<"FromCode"<<std::endl; code->print(dst); }
*/
  throw std::runtime_error("Not implemented.");

}

void VarDecl::print(std::ostream &dst) const {
   /* std::cout << "VarDecl" << std::endl;
    if(type != nullptr) {
        type->print(dst);
    }

    if(name != nullptr) {
        name->print(dst);
        dst <<  " = ";
    }

    if(value != nullptr) {
        value->print(dst);
    } else {
        dst << "0";
    }
*/
  throw std::runtime_error("Not implemented.");
}

void funcDeclarator::print(std::ostream &dst) const {
    throw std::runtime_error("Not implemented.");
}

void paramDecl::print(std::ostream &dst) const {
    throw std::runtime_error("Not implemented.");
}

void initDecl::print(std::ostream &dst) const {
    if(declarator != nullptr)
        { declarator->print(dst); }
}

void NextState::print(std::ostream &dst) const {
    throw std::runtime_error("Not implemented.");
}



//////////////////////////////////////////////
// ast_functions.hpp
//////////////////////////////////////////////

void Function::print(std::ostream &dst) const {
    dst<<getFunction()<<"( ";
    arg->print(dst);
    dst<<" )";
}



//////////////////////////////////////////////
// ast_operators.hpp
//////////////////////////////////////////////

void Operator::print(std::ostream &dst) const {
    dst<<"( ";
    left->print(dst);
    dst<<" ";
    dst<<getOpcode();
    dst<<" ";
    right->print(dst);
    dst<<" )";
}



//////////////////////////////////////////////
// ast_primitives.hpp
//////////////////////////////////////////////

void Variable::print(std::ostream &dst) const {
    dst<<id;
}

void Number::print(std::ostream &dst) const {
    dst<<value;
}



//////////////////////////////////////////////
// ast_statement.hpp
//////////////////////////////////////////////


void returnState::print(std::ostream &dst) const {
    throw std::runtime_error("Not implemented.");
}

void IfElseState::print(std::ostream &dst) const {
    throw std::runtime_error("Not implemented.");
}

void WhileState::print(std::ostream &dst) const {
    throw std::runtime_error("Not implemented.");
}



//////////////////////////////////////////////
// ast_unary.hpp
//////////////////////////////////////////////

void Unary::print(std::ostream &dst) const {
    dst << "( ";
    dst << getOpcode();
    dst << " ";
    expr->print(dst);
    dst << " )";
}


//////////////////////////////////////////////
// ast_type.hpp
//////////////////////////////////////////////

void Type::print(std::ostream &dst) const {
    std::cout<<"Kind to be found"<<std::endl;
}

//////////////////////////////////////////////
// ast_assign.hpp
//////////////////////////////////////////////

void VarAssign::print(std::ostream &dst) const {
    throw std::runtime_error("Not implemented.");
}
