#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "State.hpp"
#include "Transition.hpp"
#include "TransitionList.hpp"
#include "Configuration.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc == 4) {
        ifstream fin;
        std::string line;
        std::string info;
        int id;
        int q, r;
        char a, b, x; 
        std::vector<State> states;
        std::vector<Transition> transitions;
        std::vector<TransitionList> tLists;

        std::string inFile = argv[1];
        std::string input = argv[2];
        int bounds = atoi(argv[3]);
                
        fin.open(inFile);

        if(fin.is_open()) {
            while(fin.good()) {
                fin >> line;

                if(fin.eof()) break;

                if(line == "state") {
                   fin >> id >> info; states.push_back(State(id, info));
                }
                else {
                    fin >> q >> a >> r >> b >> x;
                    transitions.push_back(Transition(q, r, a, b, x));
                }
            }
        }
        else std::cout << "Unable to open file" << std::endl;
       
        int lastState = 0;
        for(Transition curTrans : transitions)
            if(curTrans.getTo() > lastState) lastState = curTrans.getTo();

        if(states.back().getId() != lastState) 
            states.push_back(State(lastState, "normal"));

        vector<State>::iterator next = states.begin();
        next++;

        for(vector<State>::iterator it = states.begin(); it < states.end(); it++) {
            for(int i = it->getId() + 1; i < next->getId(); i++) {
                states.insert(states.begin() + i, State(i, "normal"));
            }
            next++;
        }
       
        for(int i = 0; i <= lastState; i++)
           tLists.push_back(TransitionList(i));

        for(Transition curTrans : transitions)
            tLists[curTrans.getFrom()].addTransition(curTrans);
        
        int startStateId;

        for(State curState : states) {
            if(curState.getInfo() == "start") {
                startStateId = curState.getId();
                break;
            }
        }
        
        int move = 0;
        bool breakOut = false;
        Configuration config = Configuration(startStateId, input, move, false); 

        //Start simulation
        for(; bounds > 0 && !breakOut; bounds--) {
            for(Transition curTrans : tLists[config.getCurrentState()].getTransitionList()){
                 
                if (input[config.getReadIndex()] == curTrans.getRead()) {
                    if(curTrans.getMotion() == 'L') move--;
                    else move++;
                    
                    input[config.getReadIndex()] = curTrans.getWrite();
                    config = Configuration(curTrans.getTo(), input, move, false); 
                    break;
                }
            }
            for(State curState : states) {
                if(curState.getId() == config.getCurrentState()) {
                    if(curState.getInfo() == "accept") {
                        std::cout << "accept ";
                        for(State accepts : states) {
                            if(accepts.getInfo() == "accept")
                                std::cout << accepts.getId() << " ";
                        }
                        std::cout << std::endl;
                        breakOut = true;
                        break;
                    }
                }
            }
            if(config.getReadIndex() < 0 || config.getReadIndex() >= input.size()) {
                std::cout << "bounds" << std::endl;
                break;
            }
        }

        if(bounds == 0) std::cout << "quit" << std::endl;
        fin.close();
    }
    else if(argc < 4) std::cout << "Too few arguments" << std::endl;
    else std::cout << "Too many arguments" << std::endl;
}
