#include <string> 

#include "knapsack.hpp"

using namespace std;

Knapsack::Knapsack(item** items, int size, int capacity) {
    this->visited = 0;
    this->leafVisits = 0;
    this->bound = 0;
    this->items = *items;
    this->size = size;
    this->capacity = capacity;
}
void Knapsack::kwf() {
    int itemFrac[this->size];
    item temp = this->items[0];
    int weight = 0;

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

    for(int i = this->size - 1; i >= 0 && weight < this->capacity; i--) {
        if(weight + this->items[i].first <= this->capacity) {
            weight += this->items[i].first;
            this->bound += this->items[i].second;
            cout << "item: " << i << " Cur: " << this->bound << endl;
        }
        else {
            this->bound += (this->capacity - weight)*itemFrac[i];
            weight += (this->capacity - weight);
            cout << "item: " << i << " Cur: " << this->bound << endl;
        }
    }
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
