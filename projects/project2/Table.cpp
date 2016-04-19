#include "Table.hpp"

using std::string;
using std::vector;

Table::Table(int numSeats, int ante) {
    this->numSeats = numSeats;
    this->ante = ante;
    this->numEmptySeats = numSeats;
    this->deck = new Deck();
    this->winner = NULL;
}

bool Table::emptySeat() {
    if(!this->numEmptySeats) return false;
    return true;
}

vector<Player> Table::playRound() {
    Card best;
    this->winner = &this->curPlayers.front();
    
    this->deck->shuffle();
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end(); ++it) it->bet(this->ante);
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end(); ++it) {
       it->hand = this->deck->draw();
    }
    best = this->winner->hand;
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end(); ++it) {
        if(best.worth < it->hand.worth) {
            this->winner = &*it;
            best = it->hand;
        }
    }
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end(); ++it) {
        if(&*it != this->winner) this->losers.push_back(*it); 
    }
    
    return this->losers;
}

void Table::addPlayer(Player p) {
    this->curPlayers.push_back(p);
    this->numEmptySeats--;
}

void Table::printWinner() {
    if(this->winner != NULL) {
        std::cout << "The winner is " << this->winner->getName() << " with a budget of " 
            << this->winner->getBudget() << "." << std::endl;
    }
   else std::cout << "You haven't started" << std::endl;
}
