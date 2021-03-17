#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <memory>

#include "ast_type.hpp"


class Decl
    : public Node
{
public:

    // Members
    NodePtr type;
    NodePtr name;
    NodePtr value;
    NodePtr code;
    NodePtr next;

    // Constructor
    Decl( NodePtr _type,  NodePtr _name, NodePtr _value, NodePtr _code, NodePtr _next):
        type(_type),
        name(_name),
        value(_value),
        code(_code),
        next(_next)
    {}

    // Destructor
    virtual ~Decl()
    {
        delete type;
        delete name;
        delete value;
        delete code;
        delete next;
    }

    // Getters and Setters
    NodePtr getType() const
        { return type; }

    NodePtr getDeclValue() const
        { return value; }

    NodePtr getCode() const
        { return next; }

    NodePtr getNext() const
        { return next; }

    virtual std::string getName() const override {
        return name->getName();
    }

    // Function declarations
    virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override { throw std::runtime_error("Not implemented."); }

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


class FuncDecl
    : public Decl
{

public:

    // Constructor
    FuncDecl(NodePtr _type,  NodePtr _name, NodePtr _value, NodePtr _code, NodePtr _next)
        : Decl(_type, _name, _value, _code, _next) {}


    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};



class VarDecl
    : public Decl
{
public:
    // Constructor
    VarDecl(NodePtr _type,  NodePtr _name, NodePtr _value, NodePtr _code, NodePtr _next)
        : Decl(_type, _name, _value, _code, _next) {}


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



class initDecl
    : public Node
{
public:

    // Members
    NodePtr declarator;
    NodePtr initializer;

    // Constructor & Destructor
    initDecl(NodePtr _declarator, NodePtr _initializer ):
        declarator(_declarator),
        initializer(_initializer)
    {}

    virtual ~initDecl()
    {
        delete declarator;
        delete initializer;
    }

    // Getters & Setters
    NodePtr getDeclerator() const
        { return declarator; }

    NodePtr getInitilizer() const
        { return initializer; }

    virtual std::string getName() const override {
        return declarator->getName();
    }

    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        int &stack,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

class NextState
    : public Node
{

public:

    NodePtr state;
    NodePtr next;

    NextState(NodePtr _state, NodePtr _next)
    : state(_state)
    , next(_next)
    {}

  virtual ~NextState()
  {
    delete state;
    delete next;
  }

   // Member function declarations
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
