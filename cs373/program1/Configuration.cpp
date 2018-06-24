#include "Configuration.hpp"

Configuration::Configuration(int stateId, std::string value, int readIndex, bool executed) {
   this->stateId = stateId;
   this->value = value;
   this->readIndex = readIndex;
   this->executed = executed;
}

int Configuration::getCurrentState() {
    return this->stateId;
}

int Configuration::getReadIndex() {
    return this->readIndex;
}

bool Configuration::getStatus() { 
    return this->executed; 
}
