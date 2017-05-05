#include <deque>
#include <fstream>
#include <string>

#include "ssfs.hpp"

using std::string;

string Controller::execute(op command) {
    // lock
    Controller.exe_queue.push(command);
    // unlock
}

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
