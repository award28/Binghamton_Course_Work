#include<iostream>
#include<string>

#include "knapsack.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc != 3) {
        cerr << "You have an incorrect number of arguments." << endl;
        exit(0);
    }

    item sackInfo;
    string data;
    string d = ",";
    int loc;
    int i = 0;

    ifstream infile(argv[1]);

    getline(infile, data);
    loc = data.find(d);
    
    sackInfo.first = atoi(data.substr(0, loc).c_str());
    sackInfo.second = atoi(data.substr(loc + 1, data.length()).c_str());

    item *items = (item *) malloc (sizeof(item) * (sackInfo.first));

    while(getline(infile, data)) {
        loc = data.find(d);
        items[i].first = atoi(data.substr(0, loc).c_str());
        items[i].second = atoi(data.substr(loc + 1, data.length()).c_str());
        i++;
    }

    Knapsack *ks = new Knapsack(&items, sackInfo.first, sackInfo.second);
    ks->kwf();
    ks->execute(0, 0, 0);
    ks->print(argv[2]);

    free(items);
    infile.close();
    return 0;
}
