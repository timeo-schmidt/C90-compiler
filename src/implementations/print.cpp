#include "ast.hpp"

// This file contains all function definitions for the text-based print functionality.


// ast_declaration.hpp

void FuncDecl::print(std::ostream &dst) const {
   if(type != nullptr)
   { type->print(dst);}

    if(name != nullptr)
   { name->print(dst);}

    if(code != nullptr)
   { code->print(dst);}

}

void VarDecl::print(std::ostream &dst) const {
  if(type != nullptr)
  { type->print(dst); }

  if(name != nullptr)
  { name->print(dst);
    dst <<  " = "; }

  if(value != nullptr)
  { value->print(dst); }
  else{ dst << "0"; }
}

void initDecl::print(std::ostream &dst) const {
    if(declarator != nullptr)
        { declarator->print(dst); }
}
