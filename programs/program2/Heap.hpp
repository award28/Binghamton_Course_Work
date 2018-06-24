#ifndef HEAP_HPP
#define HEAP_HPP
#include "Player.hpp"
#include <vector>

class Heap {
    private:
        std::vector<Player> players;
    public:
        Heap(std::string fileName);
        Heap(const Heap& copy);
        void addPlayer(Player newPlayer);
        Player getPlayer();
        std::vector<Player> getArray();
        bool empty();
        unsigned int size();
};
#endif
