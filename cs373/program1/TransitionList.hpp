#ifndef TRANSITIONLIST_HPP
#define TRANSITIONLIST_HPP
#include <iostream>
#include <vector>
#include "State.hpp"
#include "Transition.hpp"

class TransitionList {
    private:
        std::vector<Transition> transitionList; 
        int stateId;
    public:
        TransitionList(int stateId);
        void addTransition(Transition transition);
        std::vector<Transition> getTransitionList();
        int getSize();
};
#endif
