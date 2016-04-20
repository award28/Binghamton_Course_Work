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
    if(this->numEmptySeats <= 0) return false;
    return true;
}

vector<Player> Table::playRound() {
    Card best;
    Player winner = this->curPlayers.front();
    int numOfPlayers = this->numSeats - this->numEmptySeats;
    this->deck = new Deck();
    std::vector<Player> losers;
    this->deck->shuffle();
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end(); ++it) it->bet(this->ante);
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end(); ++it) it->hand = this->deck->draw();
    
    best = winner.hand;
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end(); ++it) {
        if(best.getValue() == it->hand.getValue()) {
            if(best.worth < it->hand.worth) {
                winner = *it;
                best = it->hand;
            }
        }
        else if(best.getValue() < it->hand.getValue()) {
            winner = *it;
            best = it->hand;
        }
    }
    for(auto it = this->curPlayers.begin(); it != this->curPlayers.end();) {
        if(it->getName() != winner.getName()) {
            losers.push_back(*it);
            this->curPlayers.erase(it);
            this->numEmptySeats++;
        }    
        else ++it;
    }
    this->curPlayers.front().collectWinnings(this->ante*numOfPlayers);
    this->winner = &this->curPlayers.front();
    return losers;
}

void Table::addPlayer(Player p) {
    this->curPlayers.push_back(p);
    this->numEmptySeats--;
}

void Table::printWinner() {
    if(this->winner != NULL) {
        std::cerr << "\n\tWinner: " << this->winner->getName() << std::endl;
        std::cerr << "\tWinnings: " << this->winner->getBudget() << std::endl;
    }
   else std::cerr << "You haven't started" << std::endl;
}
