#ifndef DECK_HPP
#define DECK_HPP
#include <iostream>
#include <deque>
#include "Card.hpp"

class Deck {
    public:
        std::deque<Card> deck;
        Deck(void);
        void shuffle();
        Card draw();
};
#endif
