#include "TransitionList.hpp"

TransitionList::TransitionList(int stateId) {
    this->stateId = stateId;
}

void TransitionList::addTransition(Transition transition) {
   this->transitionList.push_back(transition); 
}

std::vector<Transition> TransitionList::getTransitionList() {
    return this->transitionList;
}

int TransitionList::getSize() {
    return this->transitionList.size();
}
