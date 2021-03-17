#include "ast.hpp"

// This file contains all function definitions for the code generation functionality.


//////////////////////////////////////////////
// ast_declaration.hpp
//////////////////////////////////////////////

void Decl::draw_tree_node(std::ofstream& dotfile) const {
    throw std::runtime_error("draw_tree_node() is not implemented for Decl::");
}

void FuncDecl::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ FuncDecl |{<declarationSpecifiers> declarationSpecifiers|<initDeclarator> initDeclarator|<compoundStatement> compoundStatement}}\"];" << std::endl;

    if(declarationSpecifiers!=nullptr) {
        dotfile << "id" << this << ":declarationSpecifiers -> id" << declarationSpecifiers << ";" << std::endl;
        declarationSpecifiers->draw_tree_node(dotfile);
    }

    if(initDeclarator!=nullptr) {
        dotfile << "id" << this << ":initDeclarator -> id" << initDeclarator << ";" << std::endl;
        initDeclarator->draw_tree_node(dotfile);
    }

    if(compoundStatement!=nullptr) {
        dotfile << "id" << this << ":compoundStatement -> id" << compoundStatement << ";" << std::endl;
        compoundStatement->draw_tree_node(dotfile);
    }

};

void VarDecl::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ VarDecl |{<declarationSpecifiers> declarationSpecifiers|<initDeclarator> initDeclarator|<compoundStatement> compoundStatement}}\"];" << std::endl;

    if(declarationSpecifiers!=nullptr) {
        dotfile << "id" << this << ":declarationSpecifiers -> id" << declarationSpecifiers << ";" << std::endl;
        declarationSpecifiers->draw_tree_node(dotfile);
    }

    if(initDeclarator!=nullptr) {
        dotfile << "id" << this << ":initDeclarator -> id" << initDeclarator << ";" << std::endl;
        initDeclarator->draw_tree_node(dotfile);
    }

    if(compoundStatement!=nullptr) {
        dotfile << "id" << this << ":compoundStatement -> id" << compoundStatement << ";" << std::endl;
        compoundStatement->draw_tree_node(dotfile);
    }

};

void initDecl::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ initDecl |{<declarator> declarator|<initializer> initializer}}\"];" << std::endl;

    if(declarator!=nullptr) {
        dotfile << "id" << this << ":declarator -> id" << declarator << ";" << std::endl;
        declarator->draw_tree_node(dotfile);
    }

    if(initializer!=nullptr) {
        dotfile << "id" << this << ":initializer -> id" << initializer << ";" << std::endl;
        initializer->draw_tree_node(dotfile);
    }

};

void NextState::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ initDecl |{<state> state|<next> next}}\"];" << std::endl;

    if(state!=nullptr) {
        dotfile << "id" << this << ":state -> id" << state << ";" << std::endl;
        state->draw_tree_node(dotfile);
    }

    if(next!=nullptr) {
        dotfile << "id" << this << ":next -> id" << next << ";" << std::endl;
        next->draw_tree_node(dotfile);
    }

};



//////////////////////////////////////////////
// ast_operators.hpp
//////////////////////////////////////////////

void Operator::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ Operator " << this->getOpcode() << "|{<left> left|<right> right}}\"];" << std::endl;

    if(left!=nullptr) {
        dotfile << "id" << this << ":left -> id" << left << ";" << std::endl;
        left->draw_tree_node(dotfile);
    }

    if(right!=nullptr) {
        dotfile << "id" << this << ":right -> id" << right << ";" << std::endl;
        right->draw_tree_node(dotfile);
    }
};



//////////////////////////////////////////////
// ast_primitives.hpp
//////////////////////////////////////////////

void Variable::draw_tree_node(std::ofstream& dotfile) const {
    //throw std::runtime_error("draw_tree_node() is not implemented for Variable::");
    dotfile << "id" << this << "[label=\"{ Variable | {" << this->getId() << "} }\"];" << std::endl;
};

void Number::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ Number | {" << this->getValue() << "} }\"];" << std::endl;
};



//////////////////////////////////////////////
// ast_statement.hpp
//////////////////////////////////////////////

void returnState::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ returnState |{<expression> expression}}\"];" << std::endl;

    if(expression!=nullptr) {
        dotfile << "id" << this << ":expression -> id" << expression << ";" << std::endl;
        expression->draw_tree_node(dotfile);
    }

};

void IfElseState::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ IfElseState |{<condition> condition | <If> If| <Else> Else}}\"];" << std::endl;

    if(condition!=nullptr) {
        dotfile << "id" << this << ":condition -> id" << condition << ";" << std::endl;
        condition->draw_tree_node(dotfile);
    }

    if(If!=nullptr) {
        dotfile << "id" << this << ":If -> id" << If << ";" << std::endl;
        If->draw_tree_node(dotfile);
    }

    if(Else!=nullptr) {
        dotfile << "id" << this << ":Else -> id" << Else << ";" << std::endl;
        Else->draw_tree_node(dotfile);
    }

};



//////////////////////////////////////////////
// ast_unary.hpp
//////////////////////////////////////////////

void Unary::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ Unary " << this->getOpcode() << "|{<expr> expr}}\"];" << std::endl;

    if(expr!=nullptr) {
        dotfile << "id" << this << ":expr -> id" << expr << ";" << std::endl;
        expr->draw_tree_node(dotfile);
    }

};
