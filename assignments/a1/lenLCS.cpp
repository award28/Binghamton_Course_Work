#include <string> 
#include <ctime>

#include "lcs.hpp"

using namespace std;

void LenLCS::execute(const string &x, const string &y, const string &outfile) {
    int lenx = x.length();
    int leny = y.length();
    int c[lenx + 1][leny + 1];
    char b[lenx + 1][leny + 1];
    string retval = "";
    ofstream fout(outfile);

    clock_t begin = clock();

    c[0][0] = 0;

    for(int i = 1; i < lenx + 1; i++) {
        c[i][0] = 0; 
        b[i][0] = 'X';
    }

    for(int i = 0; i < leny + 1; i++) {
        c[0][i] = 0; 
        b[0][i] = 'X'; 
    }

    for(int i = 0; i < lenx; i++) {
        for(int j = 0; j < leny; j++) {
            if(x[i] == y[j]) {
                c[i+ 1][j + 1] = c[i][j] + 1;
                b[i + 1][j + 1] = 'T';
            }
            else if(c[i][j + 1] >= c[i+ 1][j]) {
                c[i + 1][j + 1] = c[i][j + 1];
                b[i + 1][j + 1] = '^';
            }
            else {
                c[i + 1][j + 1] = c[i + 1][j];
                b[i + 1][j + 1] = '<';
            }
        }
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    if(lenx < 11 && leny < 11) {
        for(int i = 0; i < lenx + 1; i++) {
            for(int j = 0; j < leny + 1; j++) {
                fout << c[i][j] << " ";
            }
            fout << endl;
        }
    }

    while(b[lenx][leny] != 'X') {
        if(b[lenx][leny] == 'T') {
            retval = x[lenx - 1] + retval;
            lenx--;
            leny--;
        }
        else if(b[lenx][leny] == '<')
            leny--;
        else
            lenx--;
    }

    fout << retval << endl;;
    fout << elapsed_secs << " seconds";

    fout.close();
}
