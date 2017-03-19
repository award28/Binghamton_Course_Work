#include <string> 
#include <ctime>

#include "lcs.hpp"

using namespace std;
/*
array L;

int lcs_length(char * AA, char * BB)
{
    A = AA; B = BB;
    allocate storage for L;
    for (i = 0; i <= m; i++)
        for (j = 0; j <= m; j++)
            L[i,j] = -1;

    return subproblem(0, 0);
}

int subproblem(int i, int j) {
    if (L[i,j] < 0) {
        if (A[i] == '\0' || B[j] == '\0') L[i,j] = 0;
        else if (A[i] == B[j]) L[i,j] = 1 + subproblem(i+1, j+1);
        else L[i,j] = max(subproblem(i+1, j), subproblem(i, j+1));
    }
    return L[i,j];
}
*/

int Memoization::execute(const std::string &x, const std::string &y, int curX, int lenX, int curY, int lenY, int *arr) {
    if (arr[curX * curY] < 0) {
        if (curX == lenX || curY == lenY) 
            arr[curX * curY] = 0;
        else if (x[curX] == y[curY]) 
            arr[curX * curY] = 1 + execute(x, y, curX+1, lenX, curY+1, lenY, arr);
        else 
            arr[curX * curY] = max(execute(x, y, curX+1, lenX, curY, lenY, arr), execute(x, y, curX, lenX, curY+1, lenY, arr));
    }
    return arr[curX * curY];
}

void Memoization::lcs(const std::string &x, const std::string &y, const std::string &outfile) {
    int retval; 
    int size = x.length() * y.length();
    int checked[size];
    ofstream fout(outfile);

    std::fill_n(checked, size, -1);

    clock_t begin = clock();

    retval = execute(x, y, 0, x.length(), 0, y.length(), checked); 

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    fout << retval << endl;
    fout << elapsed_secs << " seconds";

    fout.close();
}
