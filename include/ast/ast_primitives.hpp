#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include "reg_alloc.hpp"

#include <string>
#include <iostream>


class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // If the binding does not exist, this will throw an error
        return bindings.at(id);
    }    

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
         std::map<std::string,double> &variables
    ) const
    {
    // find variable stack location
    double location = variables.at("a");

    // load into register 
    std::cout << "lw "<< destReg << ", "<< location << "($sp)" << std::endl;
    }

};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<value;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        return value;
    }

     virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
         std::map<std::string,double> &variables
    ) const { 

            std::cout << "addiu " << destReg << ", $0, " << getValue() << std::endl;
    }

};


#endif
