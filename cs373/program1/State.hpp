#ifndef STATE_HPP
#define STATE_HPP
#include <iostream>

class State {
    private:
        int id;
        std::string info;
    public:
        State(int id, std::string);
        int getId();
        std::string getInfo();
};
#endif
