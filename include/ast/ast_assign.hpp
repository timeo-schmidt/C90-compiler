#ifndef ast_assign_hpp
#define ast_assign_hpp

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <memory>

#include "ast_type.hpp"



class VarAssign
    : public Node
{

public:

    NodePtr var;
    NodePtr expr;

    VarAssign(NodePtr _var, NodePtr _expr):
        var(_var),
        expr(_expr)
    {}

    virtual ~VarAssign()
    {
        delete var;
        delete expr;
    }

    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        struct Data &data,
        std::map<std::string,double> &bindings,
       std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};



class functionCall
    : public Node
{

public:

    NodePtr functName;
    NodePtr params;

    functionCall(NodePtr _functName, NodePtr _params):
        functName(_functName),
        params(_params)
    {}

    virtual ~functionCall()
    {
        delete functName;
        delete params;
    }

    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual bool isArray() const override
        {return 0;}

    virtual void codegen(
        std::string destReg,
        struct Data &data,
        std::map<std::string,double> &bindings,
       std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


class storeParams
    : public Node
{

public:

    NodePtr param;
    NodePtr next;

    storeParams(NodePtr _param, NodePtr _next):
        param(_param),
        next(_next)
    {}

    virtual ~storeParams()
    {
        delete param;        
        delete next;

    }


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
       std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


class arrayAssign
    : public Node
{

public:

    NodePtr name;
    NodePtr arrayLocation;

    arrayAssign(NodePtr _name, NodePtr _arrayLocation):
        name(_name),
        arrayLocation(_arrayLocation)
    {}

    virtual ~arrayAssign()
    {
        delete name;        
        delete arrayLocation;

    }



    virtual std::string getName() const override {
        return name->getName();
    }
    virtual int getValue() const override
       { return arrayLocation->getValue(); }

    virtual bool isArray() const override
        {return 1;}

    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        struct Data &data,
        std::map<std::string,double> &bindings,
       std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


#endif
