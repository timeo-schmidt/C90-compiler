#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>

class Function
    : public Expression
{
private:
    ExpressionPtr arg;
protected:
    Function(ExpressionPtr _arg)
        : arg(_arg)
    {}
public:
    virtual ~Function()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    ExpressionPtr getArg() const
    { return arg; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<getFunction()<<"( ";
        arg->print(dst);
        dst<<" )";
    }
    
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // Implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }

    virtual void codegen() const override
    {
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
    
};

class LogFunction
    : public Function
{
public:
    LogFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "log"; }
    
    virtual double evaluate(
        const std::map<std::string, double> &bindings
    ) const override
    {
        double v = getArg()->evaluate(bindings);
        return log(v);
    }
};

class ExpFunction
    : public Function
{
public:
    ExpFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "exp"; }

virtual double evaluate(
        const std::map<std::string, double> &bindings
    ) const override
    {
        double v = getArg()->evaluate(bindings);
        return exp(v);
    }
};

class SqrtFunction
    : public Function
{
public:
    SqrtFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "sqrt"; }

virtual double evaluate(
        const std::map<std::string, double> &bindings
    ) const override
    {
        double v = getArg()->evaluate(bindings);
        return sqrt(v);
    }
};
#endif
