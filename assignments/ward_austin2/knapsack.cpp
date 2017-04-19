#include <string> 

#include "knapsack.hpp"

using namespace std;

Knapsack::Knapsack(item** items, int size, int capacity) {
    this->visited = 0;
    this->leafVisits = 0;
    this->items = *items;
    this->size = size;
    this->capacity = capacity;
}
void Knapsack::execute() {
    int itemFrac[this->size];
    item temp = this->items[0];

    for(int i = 0; i < this->size; i++) 
        itemFrac[i] = this->items[i].second/this->items[i].first;

    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size - i - 1; j++) {
            if (itemFrac[j] > itemFrac[j + 1]) {
                itemFrac[j] = itemFrac[j] ^ itemFrac[j + 1];
                itemFrac[j + 1] = itemFrac[j + 1] ^ itemFrac[j];
                itemFrac[j] = itemFrac[j] ^ itemFrac[j + 1];

                temp = this->items[j];
                this->items[j] = this->items[j + 1];
                this->items[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < this->size; i++)
        cout << "item info: " << this->items[i].first << "," << this->items[i].second << " frac: " << itemFrac[i] << endl; 
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
