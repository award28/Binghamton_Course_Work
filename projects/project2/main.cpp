#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

#include "cache.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Incorrect number of arguments. Correct format:" 
             << "\n./cache-sim <input_trace> <output_file>" << endl;
        exit(0);
    }
    long long addr;
    string type, instruction;
    ofstream fout;
    unsigned long long dCacheSize[4] = {1, 4, 16, 32};
    fout.open(argv[2]);
    ifstream fin(argv[1]);
    std::vector<std::pair<bool, unsigned long long> > traces;

    while(getline(fin, instruction)) {
        stringstream s(instruction);
        s >> hex >> type >> addr;
        traces.push_back(std::make_pair(type == "S", addr));
    }

    Direct *d = new Direct(traces);
    for (int i = 0; i < 4; i++) {
        d->execute(1024 * dCacheSize[i]);
        if (i) cout << " ";
        cout << d->hits << "," << d->total << ";";
    }
    cout << endl;

    SA *sa = new SA(traces, false, false, false);
    for (int i = 2; i <= 16; i *= 2) {
        sa->execute(i);
        if (i != 2) cout << " ";
        cout << sa->hits << "," << sa->total << ";";
    }
    cout << endl;

    FullyLRU *fullyLru = new FullyLRU(traces);
    fullyLru->execute();
    cout << fullyLru->hits << "," << fullyLru->total << ";" << endl;

    FullyHot *fullyHot = new FullyHot(traces);
    fullyHot->execute();
    cout << fullyHot->hits << "," << fullyHot->total << ";" << endl;

    SA *saWrite = new SA(traces, false, true, false);
    for (int i = 2; i <= 16; i *= 2) {
        saWrite->execute(i);
        if (i != 2) cout << " ";
        cout << saWrite->hits << "," << saWrite->total << ";";
    }
    cout << endl;

    SA *saPrefetch = new SA(traces, true, false, false);
    for (int i = 2; i <= 16; i *= 2) {
        saPrefetch->execute(i);
        if (i != 2) cout << " ";
        cout << saPrefetch->hits << "," << saPrefetch->total << ";";
    }
    cout << endl;

    SA *saOnMiss = new SA(traces, true, false, true);
    for (int i = 2; i <= 16; i *= 2) {
        saOnMiss->execute(i);
        if (i != 2) cout << " ";
        cout << saOnMiss->hits << "," << saOnMiss->total << ";";
    }
    cout << endl;
}
