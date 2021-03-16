#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>

class Function
    : public Expression
{
private:
    ExpressionPtr arg;

public:

    // Constructor & Destructor
    Function(ExpressionPtr _arg)
        : arg(_arg)
    {}

    virtual ~Function()
    {
        delete arg;
    }

    // Getters & Setters
    virtual const char * getFunction() const =0;

    ExpressionPtr getArg() const
    { return arg; }

    // Function declarations
    virtual void print(std::ostream &dst) const override;

};

class LogFunction
    : public Function
{
public:

    // Constructor
    LogFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    // Getters & Setters
    virtual const char *getFunction() const
    { return "log"; }

};

class ExpFunction
    : public Function
{
public:

    // Constructor
    ExpFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    // Getters & Setters
    virtual const char *getFunction() const
    { return "exp"; }

};

class SqrtFunction
    : public Function
{
public:

    // Constructor
    SqrtFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    // Getters & Setters
    virtual const char *getFunction() const
    { return "sqrt"; }

};
#endif
