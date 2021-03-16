#include "ast.hpp"

// This file contains all function definitions for the visual drawing functionality.


// void draw_tree_node(std::ofstream& dotfile) const {
//     dotfile << "node[shape=record];" << std::endl;
//     dotfile << "id" << this << "[label=\"{ Decl |{<type> type|<name> name|<value> value|<code> code|<next> next}}\"];" << std::endl;
//
//     NodePtr type = this->getType();
//     if(type) {
//         dotfile << "id" << this << ":type -> id" << type << ";" << std::endl;
//         type->draw_tree_node(dotfile);
//     }
//
//     NodePtr name = this->getName();
//     if(name) {
//         dotfile << "id" << this << ":name -> id" << name << ";" << std::endl;
//         name->draw_tree_node(dotfile);
//     }
//
//     NodePtr value = this->getValue();
//     if(value) {
//         dotfile << "id" << this << ":value -> id" << value << ";" << std::endl;
//         value->draw_tree_node(dotfile);
//     }
//
//     NodePtr code = this->getCode();
//     if(code) {
//         dotfile << "id" << this << ":code -> id" << code << ";" << std::endl;
//         code->draw_tree_node(dotfile);
//     }
//
//     NodePtr next = this->getNext();
//     if(next) {
//         dotfile << "id" << this << ":next -> id" << next << ";" << std::endl;
//         next->draw_tree_node(dotfile);
//     }
// }
