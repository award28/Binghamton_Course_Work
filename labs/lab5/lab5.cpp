#include <iostream>
#include "Deck.hpp"
using namespace std;

int main() {
    Deck *deck1 = new Deck();
    Deck *deck2 = new Deck();

    for(int i = 0; i < 52; i++) {
        Card card = deck1->draw();
        cout << card.getSuit() << " " << card.getValue() << endl;
    }

    deck2->shuffle();

    for(int i = 0; i < 52; i++) {
        Card card = deck2->draw();
        cout << card.getSuit() << " " << card.getValue() << endl;
    }
}

