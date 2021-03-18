#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>
#include <unordered_map>
#include <map>
#include <fstream>


// Auxillary struct types
struct type {
    std::string kind;
    struct type *subtype;
    struct param_list *params;
    type(std::string kind_in, struct type *subtype_in, struct param_list *params_in) {
        kind=kind_in;
        subtype=subtype_in;
        params=params_in;
    }
};

struct param_list {
    std::string *name;
    struct type *type;
    struct param_list *next;
    param_list(std::string *name_in, struct type *type_in, struct param_list *next_in) {
        name=name_in;
        type=type_in;
        next=next_in;
    }
};

struct stackData
{
	int32_t stackSize;   // Stores size of stack frame, need to find way of determining this
	int32_t stackOffset; // Stores offset value of the lowest free memory
};

struct varData
{
	int32_t offset;
	int32_t memSize;
};

class Node;
typedef const Node *NodePtr;

// Base Node class
class Node
{
public:

    // Constructor
    virtual ~Node() {}

    // Getters implemented by child
    virtual NodePtr         getType()                    const { throw std::runtime_error("getType() is not implemented."); }
    virtual double          getValue()                   const { throw std::runtime_error("getValue() is not implemented."); }
    virtual NodePtr         getCode()                    const { throw std::runtime_error("getCode() is not implemented."); }
    virtual NodePtr         getNext()                    const { throw std::runtime_error("getNext() is not implemented."); }
    virtual std::string     getName()                    const { throw std::runtime_error("getName() is not implemented."); }
    virtual NodePtr         getDeclerator()              const { throw std::runtime_error("getDeclerator() is not implemented."); }
    virtual NodePtr         getInitilizer()              const { throw std::runtime_error("getInitilizer() is not implemented."); }
    virtual NodePtr         getDeclarationSpecifiers()   const { throw std::runtime_error("getDeclarationSpecifiers() is not implemented."); }
    virtual NodePtr         getInitDeclarator()          const { throw std::runtime_error("getInitDeclarator() is not implemented."); }
    virtual NodePtr         getCompoundStatement()       const { throw std::runtime_error("getCompoundStatement() is not implemented."); }
    virtual NodePtr         getInitializer()             const { throw std::runtime_error("getInitializer() is not implemented."); }
    virtual int             getSize()                    const { throw std::runtime_error("getSize() is not implemented."); }
    virtual NodePtr         getFunctionName()            const { throw std::runtime_error("getFunctionName() is not implemented."); }
    virtual NodePtr         getParameterList()           const { throw std::runtime_error("getParameterList() is not implemented."); }
    virtual NodePtr         getParamType()               const { throw std::runtime_error("getParamType() is not implemented."); }
    virtual NodePtr         getParamName()               const { throw std::runtime_error("getParamName() is not implemented."); }
    // Setters implemented by child
    virtual void            setNext(NodePtr _nextptr)          { throw std::runtime_error("setNext() is not implemented."); }

    // Function declarations (being overriden by child)
    virtual void print(std::ostream &dst) const { throw std::runtime_error("print() is not implemented."); }
    virtual void draw_tree_node(std::ofstream& dotfile) const { throw std::runtime_error("draw_tree_node() is not implemented."); }
    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { throw std::runtime_error("codegen() is not implemented."); };

};


#endif
