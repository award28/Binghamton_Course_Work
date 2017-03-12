#include "predictors.hpp"

std::string GShare::prediction(const branches& vec, int gsize) {
    int size = 2048;
    int table[size];
    int index;
    int mask = (1 << gsize) - 1;
    int ghr = 0;

    std::fill_n(table, size, 3);

    int correct = 0;
    int total = 0;
    for(auto cur : vec) {
        index = cur.first & (size - 1);
        if(table[index^ghr] > 1 && cur.second == "T") {
            correct++;
            table[index^ghr] = 3;
        }
        else if(table[index^ghr] < 2 && cur.second == "NT") {
            correct++;
            table[index^ghr] = 0;
        }
        else if(table[index^ghr] > 1)
            table[index^ghr]--;
        else
            table[index^ghr]++;
        total++;
         ghr = (ghr << 1) + (cur.second == "T");
         ghr = mask & ghr;
    }

    return  std::to_string(correct) + "," + std::to_string(total) + ";";
}
