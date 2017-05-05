#include <fstream>
#include <string>

#include "ssfs.hpp"

using std::string;

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

bool Controller::write(std::string &name, int start, int size, char *data) {
    std::ofstream write;

    write.open(this->disk);

    write.close();

    return true;
}

void Controller::execute() {
    op curOp = buffer.back();
    buffer.pop();

    if(curOp.cmd == "CREATE" || curOp.cmd == "IMPORT" || curOp.cmd == "WRITE")
        write(curOp.name, curOp.start, curOp.size, curOp.data); 
}
