#include <string> 
#include <ctime>

#include "knapsack.hpp"

using namespace std;

Knapsack::Knapsack(item** items, int size) {
    this->visited = 0;
    this->leafVisits = 0;
    this->items = *items;
    this->size = size;
}
void Knapsack::execute() {
    for(int i = 0; i < this->size; i++) 
        cout << this->items[i].first << "," << this->items[i].second << endl;
}

/*
void Knapsack::lcs(const std::string &x, const std::string &y, const std::string &outfile) {
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
*/
