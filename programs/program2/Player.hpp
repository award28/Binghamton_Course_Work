#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "Card.hpp"

class Player {
    private:
        std::string name;
        int budget;
    public:
        Card hand;
        Player(std::string name, int budget);
        std::string getName();
        int getBudget();
        bool bet(int amount);
        void collectWinnings(int amount);
};
#endif
