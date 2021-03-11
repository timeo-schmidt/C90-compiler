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

     virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 

            // find variable stack location and TO DO:check size of variable but should check type...
            struct varData info;
            
           info = variables.at("test_name");
           int32_t location = info.offset;
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

     virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 

            // load into register 
            std::cout << "addi "<< destReg <<", $0, "<<  value << std::endl;
    }

};


#endif
