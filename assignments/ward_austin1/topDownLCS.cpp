#include <string> 
#include <ctime>

#include "lcs.hpp"

using namespace std;

int TopDownLCS::execute(const std::string &x, const std::string &y, int curX, int lenX, int curY, int lenY) {
    if( curX == lenX || curY == lenY) 
        return 0;
    else if(x[curX] == y[curY]) 
        return 1 + execute(x, y, curX+1, lenX, curY+1, lenY);
    else 
        return max(execute(x, y, curX+1, lenX, curY, lenY), execute(x, y, curX, lenX, curY+1, lenY));
}

void TopDownLCS::lcs(const std::string &x, const std::string &y, const std::string &outfile) {
    int subseq; 
    ofstream fout(outfile);

    clock_t begin = clock();

   subseq = execute(x, y, 0, x.length(), 0, y.length()); 

    clock_t end = clock();
    double time = double(end - begin) / CLOCKS_PER_SEC;

    fout << subseq << endl;
    fout << time << " seconds";

    fout.close();
}
