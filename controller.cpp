#include <fstream>
#include <sstream>
#include <string>

#include "ssfs.hpp"

using std::string;

Controller::Controller(std::string &disk, std::queue<op> *buffer) {
    this->disk = disk;
    this->buffer = buffer;

    char delimeter('#');

    std::fstream tdisk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    std::string superBlock;
    std::getline(tdisk, superBlock, delimeter);
    std::stringstream s(superBlock);

    s >> this->sb.numBlocks >> this->sb.blockSize;

    this->inodeStart = tdisk.tellg();

    tdisk.close();
}

std::string Controller::read(std::string &name, int start, int size) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    char *data = new char[size];

    disk.seekp(start);
    disk.read(data, size);
    disk.close();

    return std::string(data);
}

bool Controller::write(std::string &name, int start, int size, char *data) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekp(start);

    std::string newData(data);

    for(int i = 0; i < size;) {
        for(int j = 0; j < newData.length() && i < size; j++, i++) {
            disk << newData[j];
        }
    }

    disk.close();
    return true;
}

bool Controller::execute() {
    if(buffer->empty())
        return false;

    op curOp = buffer->front();
    buffer->pop();

    std::cout << curOp.cmd << std::endl;

    if(curOp.cmd == "CREATE" || curOp.cmd == "IMPORT" || curOp.cmd == "WRITE")
        write(curOp.name, curOp.start, curOp.size, curOp.data); 
    else if(curOp.cmd == "CAT" || curOp.cmd == "READ")
        read(curOp.name, curOp.start, curOp.size);
    else if(curOp.cmd == "LIST") {} //List method goes here
    else if(curOp.cmd == "DELETE") {} //Delete method goes here
    else if(curOp.cmd == "SHUTDOWN") {} //SHUTDOWN EVERYTHING
    else {} //signal pid error, bad command
    return true;
}
