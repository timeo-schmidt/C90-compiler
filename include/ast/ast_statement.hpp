#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

#include "ast_type.hpp"
#include "unique_name.hpp"



class returnState
    : public Node
{

public:

    // Members
    NodePtr expression;

    // Constructor and Destructor
    returnState( NodePtr _expression):
        expression(_expression)
    {}

    virtual ~returnState() {
        delete expression;
    }

    // Function Declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
         std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


class IfElseState
    : public Node
{

public:

    // Members
    NodePtr condition;
    NodePtr If;
    NodePtr Else;

    // Constructors & Destructors
    IfElseState(NodePtr _condition, NodePtr _If, NodePtr _Else):
        condition(_condition),
        If(_If),
        Else(_Else)
    {}

    virtual ~IfElseState() {
        delete condition;
        delete If;
        delete Else;
    }

    // Function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


class WhileState
    : public Node
{

public:

    // Members
    NodePtr expr;
    NodePtr statem;

    // Constructors & Destructors
    WhileState(NodePtr _expr, NodePtr _statem):
        expr(_expr),
        statem(_statem)
    {}

    virtual ~WhileState() {
        delete expr;
        delete statem;
    }

    // Function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};



#endif
