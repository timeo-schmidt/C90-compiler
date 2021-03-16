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
    NodePtr kind;
    NodePtr subType;
    NodePtr paramList;


    // Constructors & Destructors
    Type( NodePtr _kind, NodePtr _subType,  NodePtr _paramList):
        kind(_kind),
        subType( _subType),
        paramList(_paramList)
    {}

    virtual ~Type()
    {
        delete kind;
        delete subType;
        delete paramList;
    }

    // Getters & Setters
    NodePtr getKind() const
    { return kind; }

    NodePtr getSubType() const
    { return subType; }

    NodePtr getParamList() const
    { return paramList; }

    // Function declarations
    virtual void print(std::ostream &dst) const override;

};


#endif
