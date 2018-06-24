#include "predictors.hpp"

std::string SaturatingBimodal::prediction(const branches& vec, int tsize) {
    int size = std::pow(2, tsize);
    int table[size];
    int index;

    std::fill_n(table, size, 3);

    int correct = 0;
    int total = 0;
    for(auto cur : vec) {
        index = cur.first & (size - 1);
        if(table[index] > 1 && cur.second == "T") {
            correct++;
            table[index] = 3;
        }
        else if(table[index] < 2 && cur.second == "NT") {
            correct++;
            table[index] = 0;
        }
        else if(table[index] > 1)
            table[index]--;
        else
            table[index]++;
        total++;
    }

    return  std::to_string(correct) + "," + std::to_string(total) + ";";
}
