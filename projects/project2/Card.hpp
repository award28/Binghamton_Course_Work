#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <map>

class Card {
    private:
        int value;
        int suit;
    public:
        Card(int value, int suit) {
            this->value = value; 
            this->suit = suit;
            suitStr.insert(std::pair<int, std::string>(1,"Heart"));
            suitStr.insert(std::pair<int, std::string>(2,"Spade"));
            suitStr.insert(std::pair<int, std::string>(3,"Diamond"));
            suitStr.insert(std::pair<int, std::string>(4,"Club"));        
        }
        int getValue() {return this->value;}
        std::string getSuit() {return suitStr.find(this->suit)->second;}
        std::map<int, std::string> suitStr;
};
#endif
