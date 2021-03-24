#ifndef ast_type_hpp
#define ast_type_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>


class Type
    : public Node
{

public:

    // Members
    std::string kind;
    NodePtr subType;

    // Constructors & Destructors
    Type( const std::string &_kind, NodePtr _subType):
        kind(_kind),
        subType( _subType)
    {}

    virtual ~Type()
    {
        delete subType;
    }

    // Getters & Setters

    virtual int getSize() const override {
        if(kind == "int") { return 1; }
        else if(kind == "float")  { return 1; }
        else if(kind == "double") { return 2; }

    }

    NodePtr getSubType() const
    { return subType; }

       // Function Declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         struct Data &data,
         std::map<std::string,double> &bindings,
	     std::unordered_multimap<std::string,struct varData> &variables
    ) const override;

    virtual void draw_tree_node(std::ofstream& dotfile) const override;

};


#endif
