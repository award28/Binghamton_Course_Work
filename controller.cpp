#include <deque>
#include <fstream>
#include <string>

#include "ssfs.hpp"

Controller::Controller(const char *disk) {
    this->disk = disk;
}

char* Controller::read(int pos, int numBytes) {
    std::ifstream read;

    read.open(this->disk);

    char *data = "";
    data = "Hello world!";

    read.close();
    return data;
}

bool Controller::write(char data[], int pos, int numBytes) {
    std::ofstream write;

    write.open(this->disk);

    write.close();

    return true;
}

void Controller::addCmd(op cmd) {
    this->buffer.push(cmd);
}
