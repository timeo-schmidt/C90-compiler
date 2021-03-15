#ifndef ast_primitives_hpp
#define ast_primitives_hpp

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

    virtual std::string getName() const override
    {
        return id;
    }

     virtual void codegen(
         std::string destReg,
         struct mem stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 

            // find variable stack location and TO DO:check size of variable but should check type...
            struct varData info;
            
           info = variables.at(id);
           int32_t location = info.offset;
            // load into register 
            std::cout << "lw $0, "<< location << "($sp)" << std::endl;
            std::cout << "nop" << std::endl;
            std::cout << "sw $s0, " << *stack.size << "($sp)" << std::endl;
            std::cout << "nop" << std::endl;

            *stack.size += 4;

         
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

     virtual void codegen(
         std::string destReg,
         struct mem stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 

            // load into register 
            std::cout << "addi $0, $0, "<< value << std::endl;
            std::cout << "nop" << std::endl;
            std::cout << "sw $s0, " << *stack.size << "($sp)" << std::endl;
            std::cout << "nop" << std::endl;

           *stack.size += 4;

    }

};


#endif
