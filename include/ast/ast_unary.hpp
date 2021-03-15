#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Node
{
private:
    NodePtr expr;
protected:
    Unary(const NodePtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *getOpcode() const =0;

    NodePtr  getExpr() const
    { return expr; }

    virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        dst << getOpcode();
        dst << " ";
        expr->print(dst);
        dst << " )";
    }

    virtual void codegen(
         std::string destReg,
         struct mem stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { throw std::runtime_error("Not implemented."); } 

};

class NegOperator
    : public Unary
{
public:
    NegOperator(const NodePtr  _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

};


class UnaryExpression
    : public Unary
{
private:

   std::string ope; 

public:
    

    UnaryExpression(const std::string _ope, const NodePtr  _expr )
        : ope(_ope)
        , Unary(_expr)
    {}


    virtual const char *getOpcode() const override
    { 
        return ope.c_str(); 
    }

    
};

#endif
