#include <iostream>
#include "Transition.hpp"

Transition::Transition(int fromState, int toState, char readSymbol, char writeSymbol, char motion) {
    this->fromState = fromState;
    this->toState = toState;;
    this->readSymbol = readSymbol;
    this->writeSymbol = writeSymbol;
    this->motion = motion;
}

int Transition::getFrom() { return this->fromState; }

int Transition::getTo() { return this->toState; }

char Transition::getRead() { return this->readSymbol; }

char Transition::getWrite() { return this->writeSymbol; }

char Transition::getMotion() { return this->motion; }
