
#ifndef unique_name_hpp
#define unique_name_hpp

#include <string>
#include <vector>

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
    return "_"+base+"_"+std::to_string(makeNameUnq++);
}

static std::vector<std::string> start_labels;
static std::string makeStartLabel() {
    std::string start_lbl = "_START_"+std::to_string(makeNameUnq++);
    start_labels.push_back(start_lbl);
    return start_lbl;
}

static std::vector<std::string> exit_labels;
static std::string makeExitLabel() {
    std::string exit_lbl =  "_EXIT_"+std::to_string(makeNameUnq++);
    exit_labels.push_back(exit_lbl);
    return exit_lbl;
}

#endif
