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
    NodePtr declarationSpecifiers;
    NodePtr initDeclarator;
    NodePtr compoundStatement;

    // Constructor
    Decl( NodePtr _declarationSpecifiers,  NodePtr _initDeclarator, NodePtr _compoundStatement):
        declarationSpecifiers(_declarationSpecifiers),
        initDeclarator(_initDeclarator),
        compoundStatement(_compoundStatement)
    {}

    // Destructor
    virtual ~Decl()
    {
        delete declarationSpecifiers;
        delete initDeclarator;
        delete compoundStatement;
    }

    // Getters and Setters

   virtual NodePtr getDeclarationSpecifiers() const override
        { return declarationSpecifiers; }

   virtual NodePtr getInitDeclarator() const override
        { return initDeclarator; }

   virtual NodePtr getCompoundStatement() const override
        { return compoundStatement; }

    virtual std::string getName() const override {
        return initDeclarator->getName();
    }

    // Function declarations
    virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

    virtual void codegen(
         std::string destReg,
         struct Data &data,
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
    FuncDecl(NodePtr _declarationSpecifiers,  NodePtr _initDeclarator, NodePtr _compoundStatement)
        : Decl(_declarationSpecifiers, _initDeclarator, _compoundStatement) {}


    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         struct Data &data,
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
    VarDecl(NodePtr _declarationSpecifiers,  NodePtr _initDeclarator)
        : Decl(_declarationSpecifiers, _initDeclarator, nullptr) {}

    // Function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         struct Data &data,
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
   virtual NodePtr getDeclerator() const override
        { return declarator; }

   virtual NodePtr getInitializer() const override
        { return initializer; }

    virtual std::string getName() const override {
        return declarator->getName();
    }

    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        struct Data &data,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


class funcDeclarator
    : public Node
{
public:

    // Members
    NodePtr functionName;
    NodePtr parameterList;

    // Constructor & Destructor
    funcDeclarator(NodePtr _functionName, NodePtr _parameterList ):
        functionName(_functionName),
        parameterList(_parameterList)
    {}

    virtual ~funcDeclarator()
    {
        delete functionName;
        delete parameterList;
    }

    // Getters & Setters
    virtual NodePtr getFunctionName() const override
        { return functionName; }

    virtual NodePtr getParameterList() const override
        { return parameterList; }

    virtual std::string getName() const override
        {return functionName->getName();}
    
    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        struct Data &data,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

class paramDecl
    : public Node
{
public:

    // Members
    NodePtr paramType;
    NodePtr paramName;
    NodePtr next;

    // Constructor & Destructor
    paramDecl(NodePtr _aramType, NodePtr _paramName, NodePtr _next ):
        paramType(_aramType),
        paramName(_paramName),
        next(_next)
    {}

    virtual ~paramDecl()
    {
        delete paramType;
        delete paramName;
        delete next;
    }

    // Getters & Setters
    virtual NodePtr getParamType() const override
        { return paramType; }

    virtual NodePtr getParamName() const override
        { return paramName; }

    virtual NodePtr getNext() const override
        { return next; }

    virtual void setNext(NodePtr _nextptr) override
        { next=_nextptr; }

    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        struct Data &data,
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
        struct Data &data,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};



#endif
