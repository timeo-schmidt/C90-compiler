#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include "reg_alloc.hpp"

#include <string>
#include <iostream>
#include <map>

#include <memory>


class Declaration
    : public Expression
{
private:
    ExpressionPtr type;           // should be changed to type once set up 
    ExpressionPtr name;           // using T_VARIABLE in parser to set this up 
    ExpressionPtr next;         // think this will need to be done to allow for the next line of code??

protected:

    Declaration( ExpressionPtr _type,  ExpressionPtr _name, ExpressionPtr _next)
            : type(_type)
            , name(_name)            
            , next(_next)

    {}
public:

     virtual ~Declaration()
    {
        delete type;
        delete name;
        delete next;
    }

    ExpressionPtr getType() const
    { return type; }
    
    ExpressionPtr getName() const
    { return name; }

    ExpressionPtr getNext() const
    { return next; }



    virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
          // Implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    } 

     virtual void codegen(
         std::string destReg,
         std::map<std::string,double> &bindings
    ) const { throw std::runtime_error("Not implemented."); }   


};



class VarDeclaration
    : public Declaration
{

private:
    ExpressionPtr value;        

public:
    VarDeclaration(ExpressionPtr _type, ExpressionPtr _name, ExpressionPtr _value, ExpressionPtr _next)
    : Declaration(_type, _name, _next)
    , value(_value)
    {}

     virtual ~VarDeclaration()
    {
        delete value;
    }

    ExpressionPtr getValue() const
    { return value; }

    virtual void print(std::ostream &dst) const override
    {
        getType()->print(dst);
        dst<<" ";
        getName()->print(dst);
        dst<<" = ";
        getValue()->print(dst);

    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    } 


     virtual void codegen(
         std::string destReg,
         std::map<std::string,double> &bindings
    ) const 
    { 
              throw std::runtime_error("Not implemented.");
    }   


};


class FuncDeclaration
    : public Declaration
{

private:
    ExpressionPtr code;         // for function declarations only I think 

public:
    FuncDeclaration( ExpressionPtr _type, ExpressionPtr _name, ExpressionPtr _code, ExpressionPtr _next)
    : Declaration(_type, _name, _next )
    , code(_code)
    {}

    virtual ~FuncDeclaration()
    {
        delete code;
    }
    
    ExpressionPtr getCode() const
    { return code; }

    virtual void print(std::ostream &dst) const override
    {
        getType()->print(dst);
        dst<<" ";
        getName()->print(dst);
        dst<<" ( code i think:  ";
        getCode()->print(dst);
        dst<<" )";

    }


    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    } 


     virtual void codegen(
         std::string destReg,
         std::map<std::string,double> &bindings
    ) const 
    { 
        throw std::runtime_error("Not implemented.");
    }   


};


#endif
