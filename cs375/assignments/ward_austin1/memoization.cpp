#include <string> 
#include <ctime>

#include "lcs.hpp"

using namespace std;

int arr[100][100];

int Memoization::execute(const std::string &x, const std::string &y, int curX, int lenX, int curY, int lenY) {
    if (arr[curX][curY] < 0) {
        if (curX == lenX || curY == lenY)
            arr[curX][curY] = 0;
        else if (x[curX] == y[curY])
            arr[curX][curY] = 1 + execute(x, y, curX+1, lenX, curY+1, lenY);
        else 
            arr[curX][curY] = max(execute(x, y, curX+1, lenX, curY, lenY), execute(x, y, curX, lenX, curY+1, lenY));
    }
    return arr[curX][curY];
}

void Memoization::lcs(const std::string &x, const std::string &y, const std::string &outfile) {
    int subseq; 
    ofstream fout(outfile);
    
    for(int i = 0; i < x.length(); i++)
        for(int j = 0; j < y.length(); j++)
            arr[i][j] = -1;

    clock_t begin = clock();

    subseq = execute(x, y, 0, x.length(), 0, y.length()); 

    clock_t end = clock();
    double time = double(end - begin) / CLOCKS_PER_SEC;

    fout << subseq << endl;
    fout << time << " seconds";

    fout.close();
}
