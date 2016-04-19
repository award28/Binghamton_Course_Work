#ifndef TABLE_HPP
#define TABLE_HPP
#include "Player.hpp"
#include <vector>

class Table {
    public:
        Table(int num_seats, int ante);
        bool emptySeat();
        std::vector<Player> playRound();
        void addPlayer(Player p);
        void printWinner();
};
#endif
