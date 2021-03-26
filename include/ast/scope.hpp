
#ifndef scope_hpp
#define scope_hpp

#include <string>
#include <unordered_map>


static void scopeDecrement(int32_t &scope, std::unordered_multimap<std::string,struct varData> &variables){

    std::cout << "======" <<std::endl << "current scope = " << scope << std::endl;

    for(const auto& u : variables)
    {
      std::cout<<u.first << "  " << u.second.memSize << "  " << u.second.offset << " " <<u.second.scope <<std::endl;
    }

    std::cout << ".................." << std::endl;

    for ( auto it = variables.begin(); it != variables.end(); it++ )
    {
        if(it->second.scope == scope) { variables.erase(it); }
    }

    for(const auto& u : variables)
    {
      std::cout<<u.first << "  " << u.second.memSize << "  " << u.second.offset << " " <<u.second.scope <<std::endl;
    }


    scope -= 1;
}
/*
static void scopeDecrement(int32_t &scope, std::unordered_multimap<std::string,struct varData> &variables){
    std::unordered_multimap<std::string,struct varData>::const_iterator got = variables.begin();
    while(got != variables.end()){
        if(got->second.scope == scope) { variables.erase(got); }
        got++;
    }
}
*/

#endif
