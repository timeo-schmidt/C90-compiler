#include "ast.hpp"

// This file contains all function definitions for the code generation functionality.


//////////////////////////////////////////////
// ast_declaration.hpp
//////////////////////////////////////////////

void Decl::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for Decl::");
}

void FuncDecl::draw_tree_node(std::ofstream& dotfile) const {
    dotfile << "node[shape=record];" << std::endl;
    dotfile << "id" << this << "[label=\"{ Decl |{<type> type|<name> name|<value> value|<code> code|<next> next}}\"];" << std::endl;
    NodePtr type = this->getType();
    if(type) {
        dotfile << "id" << this << ":type -> id" << type << ";" << std::endl;
        type->draw_tree_node(dotfile);
    }

    std::string name = this->getName();
    if(1) {
        dotfile << "id" << this << ":name -> id" << name << ";" << std::endl;
        dotfile << "id" << name << "[label=\"{ " << name << " }\"];" << std::endl;
    }

    NodePtr value = this->getValue();
    if(value) {
        dotfile << "id" << this << ":value -> id" << value << ";" << std::endl;
        value->draw_tree_node(dotfile);
    }

    NodePtr code = this->getCode();
    if(code) {
        dotfile << "id" << this << ":code -> id" << code << ";" << std::endl;
        code->draw_tree_node(dotfile);
    }

    NodePtr next = this->getNext();
    if(next) {
        dotfile << "id" << this << ":next -> id" << next << ";" << std::endl;
        next->draw_tree_node(dotfile);
    }
};

void VarDecl::draw_tree_node(std::ofstream& dotfile) const {
    dotfile << "node[shape=record];" << std::endl;
    dotfile << "id" << this << "[label=\"{ Decl |{<type> type|<name> name|<value> value|<code> code|<next> next}}\"];" << std::endl;
    NodePtr type = this->getType();
    if(type) {
        dotfile << "id" << this << ":type -> id" << type << ";" << std::endl;
        type->draw_tree_node(dotfile);
    }

    std::string name = this->getName();
    if(1) {
        dotfile << "id" << this << ":name -> id" << name << ";" << std::endl;
        dotfile << "id" << name << "[label=\"{ " << name << " }\"];" << std::endl;
    }

    NodePtr value = this->getValue();
    if(value) {
        dotfile << "id" << this << ":value -> id" << value << ";" << std::endl;
        value->draw_tree_node(dotfile);
    }

    NodePtr code = this->getCode();
    if(code) {
        dotfile << "id" << this << ":code -> id" << code << ";" << std::endl;
        code->draw_tree_node(dotfile);
    }

    NodePtr next = this->getNext();
    if(next) {
        dotfile << "id" << this << ":next -> id" << next << ";" << std::endl;
        next->draw_tree_node(dotfile);
    }
};

void initDecl::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for initDecl::");
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
};



//////////////////////////////////////////////
// ast_statement.hpp
//////////////////////////////////////////////

void Statement::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for Statement::");
};

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
