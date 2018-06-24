#include "predictors.hpp"

std::string NotTaken::prediction(const branches& vec) {
    int correct = 0;
    int total = 0;
    for(auto cur : vec) {
        if(cur.second == "NT")
            correct++;
        total++;
    }

    return  std::to_string(correct) + "," + std::to_string(total) + ";";
}
