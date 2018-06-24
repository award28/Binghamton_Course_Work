#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <map>

class Card {
    private:
        int value;
        int suit;
    public:
        int worth;
        Card() { this->value = -1; this->suit = -1; this->worth = -1; }
        Card(int value, int suit) { this->value = value; this->suit = suit; this->worth = value*suit; }
        int getValue() { return this->value; }
        std::string getSuit() { return suitStr.find(this->suit)->second; }
        std::map<int, std::string> suitStr = {
            {std::pair<int, std::string>(1,"Heart")},
            {std::pair<int, std::string>(2,"Spade")},
            {std::pair<int, std::string>(3,"Diamond")},
            {std::pair<int, std::string>(4,"Club")}
        };
};
#endif
