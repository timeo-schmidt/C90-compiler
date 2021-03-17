#include "ast.hpp"

// This file contains all function definitions for the code generation functionality.


//////////////////////////////////////////////
// ast_declaration.hpp
//////////////////////////////////////////////

void Decl::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for Decl::");
}

void FuncDecl::draw_tree_node(std::ofstream& dotfile) const {
/*
    dotfile << "id" << this << "[label=\"{ Decl |{<type> type|<name> name|<value> value|<code> code|<next> next}}\"];" << std::endl;

    if(declarationSpecifiers) {
        dotfile << "id" << this << ":type -> id" << type << ";" << std::endl;
        type->draw_tree_node(dotfile);
    }

    std::string name = this->getName();
    if(name.length()!=0) {
        dotfile << "id" << this << ":name -> id" << declarationSpecifiers << ";" << std::endl;
        dotfile << "id" << declarationSpecifiers << "[label=\"{ " << declarationSpecifiers << " }\"];" << std::endl;
    }

    if(value) {
        dotfile << "id" << this << ":value -> id" << value << ";" << std::endl;
        value->draw_tree_node(dotfile);
    }

    if(code) {
        dotfile << "id" << this << ":code -> id" << code << ";" << std::endl;
        code->draw_tree_node(dotfile);
    }
*/

  throw std::runtime_error("Not implemented.");
};

void VarDecl::draw_tree_node(std::ofstream& dotfile) const {
   /* dotfile << "id" << this << "[label=\"{ Decl |{<type> type|<name> name|<value> value|<code> code|<next> next}}\"];" << std::endl;

    if(type) {
        dotfile << "id" << this << ":type -> id" << type << ";" << std::endl;
        type->draw_tree_node(dotfile);
    }

    std::string name = this->getName();
    if(name.length()!=0) {
        dotfile << "id" << this << ":name -> id" << name << ";" << std::endl;
        dotfile << "id" << name << "[label=\"{ " << name << " }\"];" << std::endl;
    }

    if(value) {
        dotfile << "id" << this << ":value -> id" << value << ";" << std::endl;
        value->draw_tree_node(dotfile);
    }

    if(code) {
        dotfile << "id" << this << ":code -> id" << code << ";" << std::endl;
        code->draw_tree_node(dotfile);
    }

    if(next) {
        dotfile << "id" << this << ":next -> id" << next << ";" << std::endl;
        next->draw_tree_node(dotfile);
    }
*/
  throw std::runtime_error("Not implemented.");
};

void initDecl::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for initDecl::");
};

void NextState::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for NextState::");
};
//////////////////////////////////////////////
// ast_operators.hpp
//////////////////////////////////////////////

void Operator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for Operator::");
};

void AddOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for AddOperator::");
};

void SubOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for SubOperator::");
};

void MulOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for MulOperator::");
};

void DivOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for DivOperator::");
};

void ExpOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for ExpOperator::");
};

void LShiftOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for LShiftOperator::");
};

void RShiftOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for RShiftOperator::");
};



//////////////////////////////////////////////
// ast_primitives.hpp
//////////////////////////////////////////////

void Variable::draw_tree_node(std::ofstream& dotfile) const {
    //throw std::runtime_error("draw_tree_node() is not implemented for Variable::");
    dotfile << "id" << this << "[label=\"{ Variable | {" << this->getId() << "} }\"];" << std::endl;
};

void Number::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for Number::");
    dotfile << "id" << this << "[label=\"{ Number | {" << this->getValue() << "} }\"];" << std::endl;
};



//////////////////////////////////////////////
// ast_statement.hpp
//////////////////////////////////////////////

void returnState::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for returnState::");
};

void IfElseState::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for IfElseState::");
};



//////////////////////////////////////////////
// ast_unary.hpp
//////////////////////////////////////////////

void Unary::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for Unary::");
};

void NegOperator::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for NegOperator::");
};

void UnaryExpression::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for UnaryExpression::");
};
