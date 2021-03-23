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

    dotfile << "id" << this << "[label=\"{ VarDecl |{<declarationSpecifiers> declarationSpecifiers|<initDeclarator> initDeclarator}}\"];" << std::endl;

    if(declarationSpecifiers!=nullptr) {
        dotfile << "id" << this << ":declarationSpecifiers -> id" << declarationSpecifiers << ";" << std::endl;
        declarationSpecifiers->draw_tree_node(dotfile);
    }

    if(initDeclarator!=nullptr) {
        dotfile << "id" << this << ":initDeclarator -> id" << initDeclarator << ";" << std::endl;
        initDeclarator->draw_tree_node(dotfile);
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

void funcDeclarator::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ funcDeclarator |{<functionName> functionName|<parameterList> parameterList}}\"];" << std::endl;

    if(functionName!=nullptr) {
        dotfile << "id" << this << ":functionName -> id" << functionName << ";" << std::endl;
        functionName->draw_tree_node(dotfile);
    }

    if(parameterList!=nullptr) {
        dotfile << "id" << this << ":parameterList -> id" << parameterList << ";" << std::endl;
        parameterList->draw_tree_node(dotfile);
    }

};

void paramDecl::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ paramDecl |{<paramType> paramType|<paramName> paramName|<next> next}}\"];" << std::endl;

    if(paramType!=nullptr) {
        dotfile << "id" << this << ":paramType -> id" << paramType << ";" << std::endl;
        paramType->draw_tree_node(dotfile);
    }

    if(paramName!=nullptr) {
        dotfile << "id" << this << ":paramName -> id" << paramName << ";" << std::endl;
        paramName->draw_tree_node(dotfile);
    }

    if(next!=nullptr) {
        dotfile << "id" << this << ":next -> id" << next << ";" << std::endl;
        next->draw_tree_node(dotfile);
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

void WhileState::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ WhileState |{<expr> expression | <statem> statement}}\"];" << std::endl;

    if(expr!=nullptr) {
        dotfile << "id" << this << ":expr -> id" << expr << ";" << std::endl;
        expr->draw_tree_node(dotfile);
    }

    if(statem!=nullptr) {
        dotfile << "id" << this << ":statem -> id" << statem << ";" << std::endl;
        statem->draw_tree_node(dotfile);
    }

};

void ForState::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ ForState |{<init_expr> init_expr | <cond_expr> cond_expr| <next_expr> next_expr| <code> code}}\"];" << std::endl;

    if(init_expr!=nullptr) {
        dotfile << "id" << this << ":init_expr -> id" << init_expr << ";" << std::endl;
        init_expr->draw_tree_node(dotfile);
    }

    if(cond_expr!=nullptr) {
        dotfile << "id" << this << ":cond_expr -> id" << cond_expr << ";" << std::endl;
        cond_expr->draw_tree_node(dotfile);
    }

    if(next_expr!=nullptr) {
        dotfile << "id" << this << ":next_expr -> id" << next_expr << ";" << std::endl;
        next_expr->draw_tree_node(dotfile);
    }

    if(code!=nullptr) {
        dotfile << "id" << this << ":code -> id" << code << ";" << std::endl;
        code->draw_tree_node(dotfile);
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



//////////////////////////////////////////////
// ast_type.hpp
//////////////////////////////////////////////

void Type::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ Type |{<kind> "<< kind <<" | <subType> (subType)}}\"];" << std::endl;

    if(subType!=nullptr) {
        dotfile << "id" << this << ":subType -> id" << subType << ";" << std::endl;
        subType->draw_tree_node(dotfile);
    }


};



//////////////////////////////////////////////
// ast_assign.hpp
//////////////////////////////////////////////


void VarAssign::draw_tree_node(std::ofstream& dotfile) const {

    dotfile << "id" << this << "[label=\"{ VarAssign |{<var> var | <expr> expr}}\"];" << std::endl;

    if(var!=nullptr) {
        dotfile << "id" << this << ":var -> id" << var << ";" << std::endl;
        var->draw_tree_node(dotfile);
    }

    if(expr!=nullptr) {
        dotfile << "id" << this << ":expr -> id" << expr << ";" << std::endl;
        expr->draw_tree_node(dotfile);
    }

};
