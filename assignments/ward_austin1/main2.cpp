#include<iostream>
#include<fstream>
#include<string>

#include "lcs.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc != 4) {
        cerr << "You have an incorrect number of arguments." << endl;
        exit(0);
    }

    string x, y;

    ifstream xfile(argv[1]);
    ifstream yfile(argv[2]);

    getline(xfile, x);
    getline(yfile, y);

    xfile.close();
    yfile.close();

    TopDownLCS *td = new TopDownLCS();
    td->lcs(x.c_str(), y.c_str(), argv[3]);

    return 0;
}
