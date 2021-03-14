#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>

#include "ast_type.hpp"
#include "unique_name.hpp"


class Statement
    : public Node
{

public:

    NodePtr dec;
    NodePtr expression;
    NodePtr init_expression;
    NodePtr expr;
    NodePtr next_expression;
    NodePtr body;
    NodePtr else_body;
    NodePtr next;
 
    
    Statement( NodePtr _dec, NodePtr _expr, NodePtr _init_expression, NodePtr _expression, NodePtr _next_expression, NodePtr _body, NodePtr _else_body, NodePtr _next)
            : dec(_dec)
            , expression(_expression)
            , init_expression(_init_expression)
            , expr(_expression)
            , next_expression(_next_expression)
            , body(_body)
            , else_body(_else_body)
            , next(_next)
        {}

    virtual ~Statement() 
    {
        delete dec;
        delete expr;
        delete init_expression;
        delete expression;
        delete next_expression;
        delete body;
        delete else_body;
        delete next;
    }


    virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { throw std::runtime_error("Not implemented."); } 


};




class returnState
    : public Node
{      

public:

    NodePtr expression;

    returnState( NodePtr _expression)
    : expression(_expression)
    {}

  virtual ~returnState()
  {
    delete expression;
  }
 
     virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 

        // check if a expression is nullptr, not sure what to do if its return ; ???
				if(expression != nullptr)
				{
          expression->codegen(destReg, stack, bindings, variables); 

          std::cout << "move $v0, " << destReg << std::endl;
        }
       
        
     } 

};


class IfElseState
    : public Node
{      

public:

    NodePtr condition;
    NodePtr If;
    NodePtr Else;

    IfElseState(NodePtr _condition, NodePtr _If, NodePtr _Else)
    : condition(_condition)
    , If(_If)
    , Else(_Else)
    {}

  virtual ~IfElseState()
  {
    delete condition;
    delete If;
    delete Else;
  }
 
     virtual void print(std::ostream &dst) const override
    { throw std::runtime_error("Not implemented."); }

    virtual void codegen(
         std::string destReg,
         stackData stack,
         std::map<std::string,double> &bindings,
	     std::unordered_map<std::string,struct varData> &variables
    ) const { 
      
      // Individual names for jumps 
      std::string ELSE = makeName("ELSE");
      std::string L = makeName("L1");

      // Evaluate condition
      condition->codegen(destReg, stack, bindings, variables);
      std::cout<<"bnez " << destReg << ", " << ELSE << std::endl;
      

      // If condition is true: evaluate If
      if(If != nullptr)
      { If->codegen(destReg, stack, bindings, variables); }  

      std::cout << "j " << L << std::endl;
      std::cout << ELSE << ":" << std::endl;
      
      // Else branch to another location & evaluate else
      if(Else != nullptr)
      { Else->codegen(destReg, stack, bindings, variables); }  

      std::cout << L << ":" << std::endl;
        
     } 

};



#endif
