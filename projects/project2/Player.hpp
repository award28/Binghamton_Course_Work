#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
    public:
        Card hand;
        Player(string name, int budget);
        string getName();
        int getBudget();
        bool bet(int amount);
        void collectWinnings(int amount);

};
#endif
