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
    NodePtr paramList;


    // Constructors & Destructors
    Type( const std::string &_kind, NodePtr _subType,  NodePtr _paramList):
        kind(_kind),
        subType( _subType),
        paramList(_paramList)
    {}

    virtual ~Type()
    {
        delete subType;
        delete paramList;
    }

    // Getters & Setters

    virtual int getSize() const override
    {
        if(kind == "int") { return 1; }
        else if(kind == "float")  { return 1; }
        else if(kind == "double") { return 2; }

    }

    NodePtr getSubType() const
    { return subType; }

    NodePtr getParamList() const
    { return paramList; }

       // Function Declarations
    virtual void print(std::ostream &dst) const override;

    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const override;

    //virtual void draw_tree_node(std::ofstream& dotfile) const override;





};


#endif
