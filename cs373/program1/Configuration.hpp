#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP
#include <iostream>
#include "State.hpp"
#include "Transition.hpp"

class Configuration {
    private:
        int stateId;
        std::string value;
        int readIndex;
        bool executed;
    public:
        Configuration(int stateId, std::string value, int readIndex, bool executed);
        int getCurrentState();
        int getReadIndex();
        bool getStatus();
};
#endif
