
#ifndef scope_hpp
#define scope_hpp

#include <string>
#include <unordered_map>


static void scopeDecrement(int32_t &scope, std::unordered_multimap<std::string,struct varData> &variables){
    for ( auto it = variables.begin(); it != variables.end(); ++it )
    {  
        if(it->second.scope == scope) { variables.erase(it); }
    }    
    scope -= 1;
}

#endif