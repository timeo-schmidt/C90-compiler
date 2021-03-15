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
         struct mem stack,
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
         struct mem stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 
        name->print(std::cout);
        std::cout << ":" <<std::endl;
        std::cout<< "addiu " << "$sp, " << "$sp, " << *stack.size << std::endl;
        std::cout<<"nop"<<std::endl;
        std::cout << "sw $ra, 4($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $fp, 8($sp)" << std::endl;
        std::cout << "nop" << std::endl; 
        std::cout << "sw $s0, 12($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s1, 16($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s2, 20($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s3, 24($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s4, 28($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s5, 32($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s6, 36($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $s7, 40($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "move $fp, $sp" << std::endl;

// store location & name of argument variables //
// this will need to be updated when argument variables can be other types //
        std::cout << "nop" << std::endl;
        std::cout << "sw $a0, 44($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a1, 48($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a2, 52($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "sw $a3, 56($sp)" << std::endl;

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

			  *stack.size = 60;

        // check if a code is nullptr for f(){} case
				if(code != nullptr)
				{code->codegen(destReg, stack,  bindings, variables); }

        std::cout << "nop" << std::endl;
        std::cout << "lw $s0, 12($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s1, 16($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s2, 20($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s3, 24($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s4, 28($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s5, 32($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s6, 36($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $s7, 40($sp)" << std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $ra, 4($sp)" <<std::endl;
        std::cout << "nop" << std::endl;
        std::cout << "lw $fp, 8($sp)" << std::endl;
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
         struct mem stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 

        //Putting assignment value in $s0
        
       // TO DO: impliment the types, then un comment this stuff
        
        //if(type != nullptr)
        //{ type->codegen("$s0", stack, bindings, variables); }
        
        if(name != nullptr)
        { name->codegen("$s0", stack,  bindings, variables); }

        std::cout << "sw $s0, " << *stack.size << "($sp)" << std::endl;

         // Storing variable name in variables and type TODO
        struct varData a; 
        a.offset = *stack.size; 
        a.memSize = 1;
        variables[name->getName()] = a;

        *stack.size += 4;


}
};



class initDecl
    : public Node
{
public:

    NodePtr declerator;
    NodePtr initilizer;
 


    initDecl(NodePtr _declerator, NodePtr _initilizer )
            : declerator(_declerator)
            , initilizer(_initilizer) 
        {}

 

    virtual ~initDecl() 
    {
        delete declerator;
        delete initilizer;
    }

    NodePtr getDeclerator() const
    { return declerator; }
    
    NodePtr getInitilizer() const
    { return initilizer; }

  virtual std::string getName() const override
    {
        return declerator->getName();
    }

  
   virtual void print(std::ostream &dst) const override
    { 
      if(declerator != nullptr)
      { declerator->print(dst); }
    }

    virtual void codegen(
         std::string destReg,
         struct mem stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 


      // Getting initiliser and loading into $s0
        if(initilizer != nullptr)
        { initilizer->codegen("$s0", stack,  bindings, variables); }
        else
        { std::cout<<"addiu $s0, $0, $0"<<std::endl;}





     } 

    
};



#endif
