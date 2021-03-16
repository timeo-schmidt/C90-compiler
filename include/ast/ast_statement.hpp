#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

#include "ast_type.hpp"
#include "unique_name.hpp"


class Statement
    : public Node
{

public:

    // Members
    NodePtr dec;
    NodePtr expression;
    NodePtr init_expression;
    NodePtr expr;
    NodePtr next_expression;
    NodePtr body;
    NodePtr else_body;
    NodePtr next;


    // Constructors & Destructors
    Statement(  NodePtr _dec,
                NodePtr _expr,
                NodePtr _init_expression,
                NodePtr _expression,
                NodePtr _next_expression,
                NodePtr _body,
                NodePtr _else_body,
                NodePtr _next):

                dec(_dec),
                expression(_expression),
                init_expression(_init_expression),
                expr(_expression),
                next_expression(_next_expression),
                body(_body),
                else_body(_else_body),
                next(_next)
        {}

    virtual ~Statement()
    {
        delete dec;
        delete expr;
        delete init_expression;
        delete expression;
        delete next_expression;
        delete body;
        delete else_body;
        delete next;
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

#endif
