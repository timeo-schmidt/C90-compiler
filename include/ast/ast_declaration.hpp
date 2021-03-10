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
         stackData stack,
         std::map<std::string,double> &bindings,
         std::map<std::string,double> &variables
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
         stackData stack,
         std::map<std::string,double> &bindings,
         std::map<std::string,double> &variables
    ) const { throw std::runtime_error("Not implemented."); }


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
         stackData stack,
         std::map<std::string,double> &bindings,
         std::map<std::string,double> &variables
    ) const { 

        std::cout << "f" << ":" <<std::endl;
        std::cout<< "addiu " << "$sp, " << "$sp, " << stack.stackSize << std::endl;
        std::cout<<"nop"<<std::endl;
        std::cout << "sw $ra, " << (-stack.stackSize-4) << "($sp)" <<std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $fp, " << (-stack.stackSize-8) << "($sp)" << std::endl;
        std::cout << "nop" << std::endl; 
        std::cout << "sw $s0, 4($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s1, 8($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s2, 12($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s3, 16($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s4, 20($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s5, 24($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s6, 28($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s7, 32($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "move $fp, $sp" << std::endl;

// store location & name of argument variables //
        std::cout << "nop" << std::endl;
        std::cout << "sw $a0, 36($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a1, 40($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a2, 44($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a3, 48($sp)" << std::endl;

        variables.emplace("argument_0", 36);
        variables.emplace("argument_1", 40);
        variables.emplace("argument_2", 44);
        variables.emplace("argument_3", 48);

        
        stack.stackOffset = 52;

         // check if a code is nullptr for f(){} case
				if(getCode() != nullptr)
				{ getCode()->codegen(destReg, stack, bindings, variables); }

        std::cout << "move $v0, " << destReg << std::endl;

        std::cout << "nop" << std::endl;
        std::cout << "lw $s0, 4($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s1, 8($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s2, 12($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s3, 16($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s4, 20($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s5, 24($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s6, 28($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s7, 32($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $ra, " << (-stack.stackSize-4) << "($sp)" <<std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $fp, " << (-stack.stackSize-8) << "($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "move $sp, $fp" << std::endl;
        std::cout << "jr $ra" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << ".global " << "f" << std::endl;
        std::cout << std::endl;

     }

     

};


#endif
