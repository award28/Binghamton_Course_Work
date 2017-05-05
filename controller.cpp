#include <fstream>
#include <string>

#include "ssfs.hpp"

using std::string;

void Controller::execute() {
}

Controller::Controller(const char *disk, std::queue<op> &buffer) {
    this->disk = disk;
    this->buffer = buffer;
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
