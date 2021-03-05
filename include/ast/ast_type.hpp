#ifndef ast_type_hpp
#define ast_type_hpp

#include "reg_alloc.hpp"

#include <string>
#include <iostream>
#include <map>

#include <memory>

/*
typedef enum {
    TYPE_VOID,
    TYPE_BOOLEAN,
    TYPE_CHARACTER,
    TYPE_INTEGER,
    TYPE_STRING,
    TYPE_ARRAY,
    TYPE_FUNCTION
} type_t;
*/

// atm just accepts types needs developing!!
// needs sub types
class Type
    : public Expression
{
private:
    std::string kind;
public:
    Type(const std::string &_kind)
        : kind(_kind)
    {}

    const std::string getKind() const
    { return kind; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<kind;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // If the binding does not exist, this will throw an error
        return bindings.at(kind);
    } 

     virtual void codegen(
         std::string destReg,
         std::map<std::string,double> &bindings
    ) const { throw std::runtime_error("Not implemented."); }   
    
};

#endif
