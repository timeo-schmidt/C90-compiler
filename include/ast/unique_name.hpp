
#ifndef unique_name_hpp
#define unique_name_hpp

#include <string>
#include <vector>

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return "_"+base+"_"+std::to_string(makeNameUnq++);
}


// These are auxillary functions to manage scoped start and exit labels in the codegeneration
static std::string makeStartLabel() {
    std::string start_lbl = "_START_"+std::to_string(makeNameUnq++);
    return start_lbl;
}

static std::string makeExitLabel() {
    std::string exit_lbl =  "_EXIT_"+std::to_string(makeNameUnq++);
    return exit_lbl;
}

static std::string makeCombinedLabel(std::string start_lbl, std::string exit_lbl) {
    return start_lbl + "," + exit_lbl;
}

static std::string getStartLabel(std::string combined_str) {
    int split_pos = combined_str.find(",");
    return combined_str.substr(0,split_pos);
}

static std::string getExitLabel(std::string combined_str) {
    int split_pos = combined_str.find(",");
    return combined_str.substr(split_pos+1);
}

#endif
