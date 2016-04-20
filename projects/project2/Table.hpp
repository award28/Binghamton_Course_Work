#ifndef TABLE_HPP
#define TABLE_HPP
#include "Player.hpp"
#include "Deck.hpp"
#include <vector>

class Table {
    private:
        int numSeats;
        int numEmptySeats;
        int ante;
        Player *winner;
        Deck *deck;
        std::vector<Player> curPlayers;
    public:
        Table(int num_seats, int ante);
        bool emptySeat();
        std::vector<Player> playRound();
        void addPlayer(Player p);
        void printWinner();
};
#endif
