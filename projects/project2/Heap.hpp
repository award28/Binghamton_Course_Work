#ifndef HEAP_HPP
#define HEAP_HPP
class Heap {
    public:
        Heap(string fileName);
        Heap(const Heap& copy);
        void addPlayer(Player newPlayer);
        Player getPlayer();
        std::vector<Player> getArray();
        bool empty();
        unsigned int size();
};
#endif
