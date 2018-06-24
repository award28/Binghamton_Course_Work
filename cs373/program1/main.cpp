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
        string line;
        string info;
        int id;
        int q, r;
        char a, b, x; 
        vector<State> states;
        vector<Transition> transitions;
        vector<TransitionList> tLists;

        int bounds = atoi(argv[3]);
        string inFile = argv[1];
        string input = argv[2];
        string result = "";
        string append = "";
                
        fin.open(inFile);

        if(fin.is_open()) {
            while(fin.good()) {
                fin >> line;

                if(fin.eof()) 
                    break;

                if(line == "state") {
                   fin >> id >> info; states.push_back(State(id, info));
                }
                else {
                    fin >> q >> a >> r >> b >> x;
                    transitions.push_back(Transition(q, r, a, b, x));
                }
            }
        }
        else 
            cout << "Unable to open file" << endl;
       
        int lastState = 0;
        for(Transition curTrans : transitions)
            if(curTrans.getTo() > lastState) lastState = curTrans.getTo();

        if(states.back().getId() != lastState) 
            states.push_back(State(lastState, "normal"));

        vector<State>::iterator next = states.begin();
        next++;

        for(vector<State>::iterator it = states.begin(); it < states.end(); it++) {
            for(int i = it->getId() + 1; i < next->getId(); i++)
                states.insert(states.begin() + i, State(i, "normal"));
            next++;
        }
       
        for(int i = 0; i <= lastState; i++){
           tLists.push_back(TransitionList(i));
        }

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
        bool rejectFound = false;
        Configuration config = Configuration(startStateId, input, move, false); 

        //Start simulation
        for(; bounds > 0 && !breakOut; bounds--) {
            for(Transition curTrans : tLists[config.getCurrentState()].getTransitionList()){
                 
                if (input[config.getReadIndex()] == curTrans.getRead()) {
                    if(curTrans.getMotion() == 'L') 
                        move--;
                    else 
                        move++;
                    
                    input[config.getReadIndex()] = curTrans.getWrite();
                    config = Configuration(curTrans.getTo(), input, move, false); 
                    break;
                }
            }
            if(!rejectFound) {
                for(State curState : states) {
                    if(curState.getId() == config.getCurrentState()) {
                        if(curState.getInfo() == "reject") {
                            append = "reject ";
                            result.append(append);
                            for(State rejects : states) {
                                if(rejects.getInfo() == "reject") {
                                    append = to_string(rejects.getId());
                                    result.append(append);
                                    append = " ";
                                    result.append(append);
                                }
                            }
                            append = '\n';
                            result.append(append);
                            rejectFound = true;
                        }
                    }
                }            
            }
            for(State curState : states) {
                if(curState.getId() == config.getCurrentState()) {
                    if(curState.getInfo() == "accept") {
                        result = "";
                        append = "accept ";
                        result.append(append);
                        for(State accepts : states) {
                            if(accepts.getInfo() == "accept") {
                                append = to_string(accepts.getId());
                                result.append(append);
                                append = " ";
                                result.append(append);
                            }
                        }
                        append = '\n';
                        result.append(append);
                        breakOut = true;
                        break;     
                    }
                }
            }

            if(config.getReadIndex() < 0 || config.getReadIndex() >= input.size()) {
                cout << "bounds" << endl;
                breakOut = true;
                break;
            }
        }
        if(bounds == 0 && !result.length()) 
            cout << "quit" << endl;
        else
            cout << result;
        fin.close();
    }
    else if(argc < 4) 
        cout << "Too few arguments" << endl;
    else 
        cout << "Too many arguments" << endl;
}
