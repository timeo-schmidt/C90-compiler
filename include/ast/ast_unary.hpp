#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>

class Unary
    : public Node
{
private:
    // Members
    NodePtr expr;
protected:

    // Constructor
    Unary(const NodePtr _expr)
        : expr(_expr)
    {}
public:

    // Destructor
    virtual ~Unary()
    {
        delete expr;
    }

    // Getters & Setters
    virtual const char *getOpcode() const =0;

    NodePtr  getExpr() const
        { return expr; }

    // Function Declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         struct Data &data,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};

class NegOperator
    : public Unary
{
public:

    // Constructor
    NegOperator(const NodePtr  _expr)
        : Unary(_expr)
    {}

    // Getters & Setters
    virtual const char *getOpcode() const override {
        return "-";
    }

    // Function declarations


};


class UnaryExpression
    : public Unary
{
private:

    // Member
    std::string ope;

public:

    // Constructor
    UnaryExpression(const std::string _ope, const NodePtr  _expr ) :
        Unary(_expr),
        ope(_ope)
    {}

    // Getters & Setters
    virtual const char *getOpcode() const override {
        return ope.c_str();
    }

    // Function declarations


};



#endif
