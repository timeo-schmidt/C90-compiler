#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>


class Operator
    : public Node
{
private:
    NodePtr  left;
    NodePtr  right;

public:

    // Constructor & Destructor
    Operator(NodePtr  _left, NodePtr  _right)
        : left(_left)
        , right(_right)
    {}

    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    // Getters and Setters
    virtual const char *getOpcode() const =0;

    NodePtr getLeft() const
    { return left; }

    NodePtr getRight() const
    { return right; }

    // Function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        int &stack,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override { throw std::runtime_error("Not implemented."); }

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

class AddOperator
    : public Operator
{
protected:
    // Getter and Setter
    virtual const char *getOpcode() const override
        { return "+"; }

public:

    // Constructors & Destructors
    AddOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

    // Function declarations
     virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override;




};

class SubOperator
    : public Operator
{
protected:
    // Getters & Setters
    virtual const char *getOpcode() const override
        { return "-"; }

public:
    // Constructors
    SubOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

    // Function declarations
    virtual void codegen(
        std::string destReg,
        int &stack,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override;



};


class MulOperator
    : public Operator
{
protected:
    // Getters & Setters
    virtual const char *getOpcode() const override
        { return "*"; }

public:
    // Constructors
    MulOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

    // Function declarations


};

class DivOperator
    : public Operator
{
protected:
    // Getters & Setters
    virtual const char *getOpcode() const override
        { return "/"; }
public:
    // Constructors
    DivOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

    // Function declarations


};

class ExpOperator
    : public Operator
{
protected:
    // Getters & Setters
    virtual const char *getOpcode() const override
        { return "^"; }
public:
    // Constructors
    ExpOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

    // Function declarations


};

class LShiftOperator
    : public Operator
{
protected:
    // Getters & Setters
    virtual const char *getOpcode() const override
        { return "<<"; }
public:
    // Constructors
    LShiftOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    // Function declarations


};

class RShiftOperator
    : public Operator
{
protected:
    // Getters & Setters
    virtual const char *getOpcode() const override
        { return ">>"; }
public:
    // Constructors
    RShiftOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

    // Function declarations


};

#endif
