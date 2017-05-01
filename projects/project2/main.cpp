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
    int addr;
    string type, instruction;
    ofstream fout;
    unsigned int dCacheSize[4] = {1, 4, 16, 32};
    fout.open(argv[2]);
    ifstream fin(argv[1]);
    vector<memInstruction> traces;

    while(getline(fin, instruction)) {
        stringstream s(instruction);
        s >> hex >> type >> addr;
        traces.push_back(memInstruction(type == "S", addr));
    }

    DMapped *dMapped = new DMapped(traces);
    for (int i = 0; i < 4; i++) {
        dMapped->execute(1024 * dCacheSize[i]);
        if (i) cout << " ";
        cout << dMapped->numHits << "," << dMapped->numHits + dMapped->numMisses << ";";
    }
    cout << endl;
    

}
