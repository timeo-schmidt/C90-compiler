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
protected:
    Operator(NodePtr  _left, NodePtr  _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const =0;

    NodePtr  getLeft() const
    { return left; }

    NodePtr  getRight() const
    { return right; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<"( ";
        left->print(dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(dst);
        dst<<" )";
    }

     virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { throw std::runtime_error("Not implemented."); } 
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}
    
     virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 
            // Getting left side of addition 
           getLeft()->codegen("$s0", stack, bindings, variables);
            // Getting left side of addition 
            getLeft()->codegen("$s1", stack, bindings, variables);

            // getting sum and storing destReg
            std::cout << "add " << destReg <<", $s1, $s0" << std::endl;

     } 


};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}
    
     virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 
            // Getting left side of addition 
           getLeft()->codegen("$s0", stack, bindings, variables);
            // Getting left side of addition 
            getLeft()->codegen("$s1", stack, bindings, variables);

            // getting sum and storing destReg
            std::cout << "sub " << destReg <<", $s1, $s0" << std::endl;

     } 

};


class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

};

class ExpOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    ExpOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}


};

class LShiftOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<<"; }
public:
    LShiftOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

};

class RShiftOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">>"; }
public:
    RShiftOperator(NodePtr  _left, NodePtr  _right)
        : Operator(_left, _right)
    {}

};

#endif
