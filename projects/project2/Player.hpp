#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
    public:
        Card hand;
        Player(std::string name, int budget);
        std::string getName();
        int getBudget();
        bool bet(int amount);
        void collectWinnings(int amount);
};
#endif
