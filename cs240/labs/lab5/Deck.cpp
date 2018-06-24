#include <iostream>
#include <deque>
#include <algorithm>
#include "Deck.hpp"
using namespace std;

Deck::Deck() {
    for(int i = 1; i < 14; i++) {
        for(int j = 1; j <= 4; j++) {
            this->deck.push_back(Card(i, j));
        }
    }
}

void Deck::shuffle() {
    std::random_shuffle(this->deck.begin(), this->deck.end());
}

Card Deck::draw() {
    Card temp = this->deck.front();
    this->deck.pop_front();
    return temp;
}
