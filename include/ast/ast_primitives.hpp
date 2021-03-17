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
    // Constructors & Destructors
    Variable(const std::string &_id)
        : id(_id)
    {}

    // Getters & Setters
    const std::string getId() const
        { return this->id; }

    virtual std::string getName() const override
        { return this->id; }

    // Function Declarations
    virtual void print(std::ostream &dst) const override;

     virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

class Number
    : public Expression
{
private:
    double value;
public:
    // Constructor & Destructor
    Number(double _value)
        : value(_value)
    {}

    // Getters & Setters
    double getValue() const
    { return value; }

    // Function Declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        int &stack,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


#endif
