#include "predictors.hpp"

std::string SingleBimodal::prediction(const branches& vec, int tsize) {
    int size = std::pow(2, tsize);
    int table[size];
    int index;

    std::fill_n(table, size, 1);

    int correct = 0;
    int total = 0;
    for(auto cur : vec) {
        index = cur.first & (size - 1);
        if(table[index] && cur.second == "T")
            correct++;
        else if(!table[index] && cur.second == "NT")
            correct++;
        else if(table[index])
            table[index]--;
        else
            table[index]++;
        total++;
    }

    return  std::to_string(correct) + "," + std::to_string(total) + ";";
}
