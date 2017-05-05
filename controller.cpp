#include <fstream>
#include <string>

#include "ssfs.hpp"

using std::string;

Controller::Controller(const char *disk, std::queue<op> &buffer) {
    this->disk = disk;
    this->buffer = buffer;
}

char* Controller::read(std::string &name, int start, int size) {
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

    write.seekp(start);

    size_t length = sizeof(data)/sizeof(data[0]);

    for(int i = 0; i < size;) {
        for(int j = 0; j < length && i < size; j++, i++) {
            //write >> data[j];
        }
    }
    write.close();
    return true;
}

void Controller::execute() {
    op curOp = buffer.back();
    buffer.pop();

    if(curOp.cmd == "CREATE" || curOp.cmd == "IMPORT" || curOp.cmd == "WRITE")
        write(curOp.name, curOp.start, curOp.size, curOp.data); 
    else if(curOp.cmd == "CAT" || curOp.cmd == "READ")
        read(curOp.name, curOp.start, curOp.size);
    else if(curOp.cmd == "LIST") {} //List method goes here
    else if(curOp.cmd == "DELETE") {} //Delete method goes here
    else if(curOp.cmd == "SHUTDOWN") {} //SHUTDOWN EVERYTHING
    else {} //signal pid error, bad command
}
