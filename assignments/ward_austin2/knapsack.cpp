#include <string> 
#include <algorithm>

#include "knapsack.hpp"

using namespace std;

Knapsack::Knapsack(item** items, int size, int capacity) {
    this->visited = 0;
    this->leafVisits = 0;
    this->bound = 0;
    this->maxProfit = 0;
    this->items = *items;
    this->size = size;
    this->capacity = capacity;
    for(int i = 0; i < size; i++)
        this->include.push_back("no");
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
        }
        else {
            this->bound += (this->capacity - weight)*itemFrac[i];
            weight += (this->capacity - weight);
        }
    }
}

void Knapsack::execute(int index, int profit, int weight) {
    this->visited++;
    if (weight <= this->capacity && profit > this->maxProfit) {
        //save better solution
        this->maxProfit = profit; // save new profit

        this->numbest.clear();

        for(int i = 0; i < this->include.size(); i++)
            if(this->include[i] == "yes")
                this->numbest.push_back(i);
    }

    if(promising(index, weight, profit)) {
        this->include[index + 1] = "yes";
        execute(index + 1, profit + this->items[index + 1].second, weight + this->items[index + 1].first);
        this->include[index + 1] = "no";
        execute(index + 1, profit, weight);
    }
    else
        this->leafVisits++;
}

bool Knapsack::promising(int i, int weight, int profit) {
    if(weight >= this->capacity) 
        return false;
    return (kwfAux(i + 1, weight, profit) > this->maxProfit);
}

int Knapsack::kwfAux(int index, int weight, int profit) {
    int itemFrac[this->size];
    int bound = profit;

    for(int i = index; i < this->size; i++) 
        itemFrac[i] = this->items[i].second/this->items[i].first;

    for(int i = this->size - 1; i >= index && weight < this->capacity; i--) {
        if(weight + this->items[i].first <= this->capacity) {
            weight += this->items[i].first;
            bound += this->items[i].second;
        }
        else {
            bound += (this->capacity - weight)*itemFrac[i];
            weight += (this->capacity - weight);
        }
    }
    return bound;
}

void Knapsack::print(const std::string &outfile) {
    ofstream fout(outfile);
    fout << this->size << "," << this->maxProfit << "," << this->numbest.size() << endl;
    fout << this->visited << "," << this->leafVisits << endl;
    for(int i = this->numbest.size() - 1; i >= 0; i--)
        fout << this->items[this->numbest[i]].first << "," << this->items[this->numbest[i]].second << endl;

    fout.close();
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

}
*/
