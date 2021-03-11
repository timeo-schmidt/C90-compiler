#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>


class Expression;

typedef const Expression *ExpressionPtr;


class Expression
    : public Node
{
public:
    virtual ~Expression()
    {}

   virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

   
};


#endif
