#include <deque>
#include <fstream>

#include "ssfs.hpp"

Controller::Controller(char disk[]) {
    this->disk = disk;
}

char* Controller::read() {
    std::ifstream read;

    read.open(this->disk);

    char *data = "";
    data = "Hello world!";

    read.close();
    return data;
}

bool Controller::write(char data[]) {
    std::ofstream write;

    write.open(this->disk);

    write.close();

    return true;
}
