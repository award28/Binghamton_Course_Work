#include <deque>
#include <fstream>

#include "ssfs.hpp"
char* Controller::read() {
    std::ifstream read;

    read.open("DISK");

    char *data = "Hello world!";

    read.close();
    return data;
}

bool Controller::write(char data[]) {
    std::ofstream write;

    return true;
}
