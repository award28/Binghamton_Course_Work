#ifndef TRANSITION_HPP
#define TRANSITION_HPP
#include <iostream> 

class Transition {
    private:
        int fromState;
        int toState;
        char readSymbol;
        char writeSymbol;
        char motion;
    public:
        Transition(int fromState, int toState, char readSymbol, char writeSymbol, char motion);
        int getFrom();
        int getTo();
        char getRead();
        char getWrite();
        char getMotion();
};
#endif
