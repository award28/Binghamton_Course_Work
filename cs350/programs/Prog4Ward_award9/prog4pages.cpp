#include <iostream>
#include <fstream>
#include <random>

#include "replacements.hpp"

using namespace std;

void randArr(int arr[]) {
    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < numAccesses; i++)
        arr[i] = (rand() % (100)) + 1;
}

void eightyTwenty(int arr[]) {
    for(int i = 0; i < numAccesses; i ++) {
        if(i % 5)
            arr[i] = (rand() % (20)) + 1;
        else
            arr[i] = (rand() % (80)) + 21;
    }
}

void repeating(int arr[]) {
    for(int i = 0; i < numAccesses; i ++) {
            arr[i] = (i % (50)) + 1;
    }
}

int main(int argc, char *argv[]) {
    int arr[numAccesses];
    string retval;
    ofstream nfout("no-locality.csv");
    ofstream efout("80-20.csv");
    ofstream lfout("looping.csv");

    for(int i = 0; i < 3; i++) {
        if(!i) {
            randArr(arr);
            nfout << "#Cache Size,FIFO,Random,LRU,Clock,Optimal" << endl;
        }
        else if(i == 1) {
            eightyTwenty(arr);
            efout << "#Cache Size,FIFO,Random,LRU,Clock,Optimal" << endl;
        }
        else {
            repeating(arr);
            lfout << "#Cache Size,FIFO,Random,LRU,Clock,Optimal" << endl;
        }

        for(int j = 5; j < 101; j += 5) {
            retval = std::to_string(j) + ",";
            Fifo *fifo = new Fifo(arr);
            retval += fifo->execute(j) + ",";
            Rand *rand = new Rand(arr);
            retval += rand->execute(j) + ",";
            Lru *lru = new Lru(arr);
            retval += lru->execute(j) + ",";
            Clock *clock = new Clock(arr);
            retval += clock->execute(j) + ",";
            Opt *opt = new Opt(arr);
            retval += opt->execute(j);

        if(!i)
            nfout << retval << endl;
        else if(i == 1)
            efout << retval << endl;
        else
            lfout << retval << endl;
        }
    }

    return 0;
}
