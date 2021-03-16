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


// Base Node class
class Node
{
public:

    // Constructor
    virtual ~Node() {}

    // Function declarations
    virtual void print(std::ostream &dst) const =0;

    virtual std::string getName() const { throw std::runtime_error("getName() is not implemented."); }

    virtual void draw_tree_node(std::ofstream& dotfile) const { throw std::runtime_error("draw_tree_node() is not implemented."); }

    virtual void codegen(
         std::string destReg,
         int &stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { throw std::runtime_error("codegen() is not implemented."); };

};

typedef const Node *NodePtr;


#endif
