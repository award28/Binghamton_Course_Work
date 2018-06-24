#include "predictors.hpp"

std::string Tournament::prediction(const branches& vec) {
    int size = 2048;
    int btable[size];
    int gtable[size];
    int selector[size];
    int index;
    int ghr = 0;
    bool bc;
    bool gc;

    std::fill_n(btable, size, 3);
    std::fill_n(gtable, size, 3);
    std::fill_n(selector, size, 0);

    int correct = 0;
    int total = 0;

    for(auto cur : vec) {
        index = cur.first & (size - 1);
        bc = saturatingBimodal(cur, btable, index);
        gc = gShare(cur, gtable, index, ghr);
        
        //Same
        if(bc == gc) {
            if(bc)
                correct++;
        }
        //Different
        else {
            if(selector[index] < 2) {
                if(gc) {
                    correct++;
                    selector[index] = 0;
                }
                else
                    selector[index]++;
            }
            else {
                if(bc) {
                    correct++;
                    selector[index] = 3;
                }
                else
                    selector[index]--;
            }
        }
        total++;
    }

    return  std::to_string(correct) + "," + std::to_string(total) + ";";
}

bool Tournament::saturatingBimodal(const branch branch, int *table, int index) {
    bool correct = false;

    if(table[index] > 1 && branch.second == "T") {
        correct = true;
        table[index] = 3;
    }
    else if(table[index] < 2 && branch.second == "NT") {
        correct = true;
        table[index] = 0;
    }
    else if(table[index] > 1)
        table[index]--;
    else
        table[index]++;

    return correct;
}

bool Tournament::gShare(const branch branch, int *table, int index, int &ghr) {
    bool correct = false;
    int mask = (1 << 11) - 1;

    if(table[index^ghr] > 1 && branch.second == "T") {
        correct = true;;
        table[index^ghr] = 3;
    }
    else if(table[index^ghr] < 2 && branch.second == "NT") {
        correct = true;
        table[index^ghr] = 0;
    }
    else if(table[index^ghr] > 1)
        table[index^ghr]--;
    else
        table[index^ghr]++;
    ghr = (ghr << 1) + (branch.second == "T");
    ghr = mask & ghr;
    
    return correct;
}
