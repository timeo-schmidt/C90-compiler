#ifndef ast_assign_hpp
#define ast_assign_hpp

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <memory>

#include "ast_type.hpp"



class VarAssign
    : public Node
{

public:

    NodePtr var;
    NodePtr expr;

    VarAssign(NodePtr _var, NodePtr _expr):
        var(_var),
        expr(_expr)
    {}

    virtual ~VarAssign()
    {
        delete var;
        delete expr;
    }

    // Member function declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
        std::string destReg,
        struct Data &data,
        std::map<std::string,double> &bindings,
        std::unordered_map<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


#endif
