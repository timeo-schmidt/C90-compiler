#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "reg_alloc.hpp"

#include <string>
#include <iostream>
#include <map>

#include <memory>

struct stackData
{
	int32_t stackSize;
	int32_t stackOffset;
};




class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
public:
    virtual ~Expression()
    {}

    // Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const =0;

    // Evaluate the tree using the given mapping of variables to numbers
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
         std::map<std::string,double> &variables
    ) const { throw std::runtime_error("Not implemented."); }
};


#endif
