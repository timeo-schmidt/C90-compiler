#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

#include "ast_type.hpp"


class Decl
    : public Node
{
public:

    NodePtr type;
    NodePtr name;
    NodePtr value;
    NodePtr code;
    NodePtr next;

    protected: 
    
        Decl( NodePtr _type,  NodePtr _name, NodePtr _value, NodePtr _code, NodePtr _next)
            : type(_type)
            , name(_name) 
            , value(_value)
            , code(_code)           
            , next(_next)
        {}

    virtual ~Decl() 
    {
        delete type;
        delete name;
        delete value;
        delete code;
        delete next;
    }

    NodePtr getType() const
    { return type; }
    
    NodePtr getName() const
    { return name; }


    NodePtr getValue() const
    { return value; }

    NodePtr getCode() const
    { return next; }

    NodePtr getNext() const
    { return next; }

    virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { throw std::runtime_error("Not implemented."); } 


};




class FuncDecl
    : public Decl
{      

public:
    FuncDecl(NodePtr _type,  NodePtr _name, NodePtr _value, NodePtr _code, NodePtr _next)
    : Decl(_type, _name, _value, _code, _next)
    {}



    virtual void print(std::ostream &dst) const override
    {
       if(type != nullptr)
       { type->print(dst);} 

        if(name != nullptr)
       { name->print(dst);} 

        if(code != nullptr)
       { code->print(dst);} 
       
       
    }  

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 
        name->print(std::cout);
        std::cout << ":" <<std::endl;
        std::cout<< "addiu " << "$sp, " << "$sp, " << stack.stackSize << std::endl;
        std::cout<<"nop"<<std::endl;
        std::cout << "sw $ra, " << (-stack.stackSize-4) << "($sp)" <<std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $fp, " << (-stack.stackSize-8) << "($sp)" << std::endl;
        std::cout << "nop" << std::endl; 
        std::cout << "sw $s0, 4($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s1, 8($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s2, 12($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s3, 16($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s4, 20($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s5, 24($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s6, 28($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s7, 32($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "move $fp, $sp" << std::endl;

// store location & name of argument variables //
// this will need to be updated when argument variables can be other types //
        std::cout << "nop" << std::endl;
        std::cout << "sw $a0, 36($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a1, 40($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a2, 44($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a3, 48($sp)" << std::endl;

				// storing argument variables to memory 
				// will need to change when arguments can be of different types 
        struct varData a; a.offset = 36; a.memSize = 1;
			  variables["argument_0"] = a;
				a.offset = 40; a.memSize = 1;
			  variables["argument_1"] = a;
				a.offset = 44; a.memSize = 1;
			  variables["argument_2"] = a;
				a.offset = 48; a.memSize = 1;
			  variables["argument_3"] = a;

			  stack.stackOffset = 52;

        // check if a code is nullptr for f(){} case
				if(code != nullptr)
				{ code->codegen(destReg, stack, bindings, variables); }

        std::cout << "move $v0, " << destReg << std::endl;

        std::cout << "nop" << std::endl;
        std::cout << "lw $s0, 4($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s1, 8($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s2, 12($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s3, 16($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s4, 20($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s5, 24($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s6, 28($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s7, 32($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $ra, " << (-stack.stackSize-4) << "($sp)" <<std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $fp, " << (-stack.stackSize-8) << "($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "move $sp, $fp" << std::endl;
        std::cout << "jr $ra" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << ".global ";
        name->print(std::cout);
        std::cout << std::endl;
     } 

};



class VarDecl
    : public Decl
{
public:
    VarDecl(NodePtr _type,  NodePtr _name, NodePtr _value, NodePtr _code, NodePtr _next)
    : Decl(_type, _name, _value, _code, _next)
    {}


    virtual void print(std::ostream &dst) const override
    {
      if(type != nullptr)
      { type->print(dst); }
      
      if(name != nullptr)
      { name->print(dst);
        dst <<  " = "; }
      
      if(value != nullptr)
      { value->print(dst); }
      else{ dst << "0"; }


    }

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 

        //Putting assignment value in $s0
        if(type != nullptr)
        { type->codegen("$s0", stack, bindings, variables); }
        if(value != nullptr)
        { value->codegen("$s0", stack, bindings, variables); }
        else
        { std::cout<< "add $s0, $0, $0 " << std::endl; }

        std::cout << "sw $s0, " << stack.stackOffset << "($sp)" << std::endl;

        struct varData a; 
        a.offset = stack.stackOffset; 
        a.memSize = 1;
        variables["test_name"] = a;

        stack.stackOffset += 4;
}


};



#endif
