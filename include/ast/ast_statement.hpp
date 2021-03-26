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
         struct Data &data,
         std::map<std::string,double> &bindings,
         std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


class breakState
    : public Node
{

public:

    // Constructor and Destructor
    breakState() {}

    virtual ~breakState() { }

    // Function Declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         struct Data &data,
         std::map<std::string,double> &bindings,
         std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

class continueState
    : public Node
{

public:

    // Constructor and Destructor
    continueState() {}

    virtual ~continueState() { }

    // Function Declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         struct Data &data,
         std::map<std::string,double> &bindings,
         std::unordered_multimap<std::string,struct varData> &variables
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
         struct Data &data,
         std::map<std::string,double> &bindings,
	     std::unordered_multimap<std::string,struct varData> &variables
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
         struct Data &data,
         std::map<std::string,double> &bindings,
	     std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

class ForState
    : public Node
{

public:

    // Members
    // for(int i=0; i<10; i++) { code }
    NodePtr init_expr;  // int i=0;
    NodePtr cond_expr;  // i<10
    NodePtr next_expr;  // i++ (this is optional, the initialiser can be modified in the for-body)
    NodePtr code;       // { code }

    // Constructors & Destructors
    ForState(NodePtr _init_expr, NodePtr _cond_expr, NodePtr _next_expr, NodePtr _code):
        init_expr(_init_expr),
        cond_expr(_cond_expr),
        next_expr(_next_expr),
        code(_code)
    {}

    virtual ~ForState() {
        delete init_expr;
        delete cond_expr;
        delete next_expr;
        delete code;
    }

    // Function declarations
    virtual void codegen(
         std::string destReg,
         struct Data &data,
         std::map<std::string,double> &bindings,
	     std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

#endif
