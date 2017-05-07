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

    std::getline(tdisk, superBlock, delimeter);

    this->filesStart = tdisk.tellg();

    int size = floor((this->sb.blockSize*this->sb.numBlocks - this->filesStart)/this->sb.blockSize);
    
    this->bitmap.first = (bool *) malloc(sizeof(bool) * size);
    this->bitmap.second = size;

    for(int i = 0; i < size; i++)
        this->bitmap.first[i] = false;

    tdisk.close();
}

std::string Controller::read(std::string &name, int start, int size) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    char *data = new char[size];

    disk.seekp(this->filesStart + start);
    disk.read(data, size);
    disk.close();

    return std::string(data);
}

bool Controller::write(std::string &name, int start, int size, std::string &data) {
    Inode inode = createInode(name);

    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    disk.seekp(inode.dbp[0] + start);

    for(int i = 0; i < size;) {
        for(int j = 0; j < data.length() && i < size; j++, i++) {
            disk << data[j];
            disk.seekg(disk.tellg());
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
    else if(curOp.cmd == "CAT" || curOp.cmd == "READ") {
        std::cout << read(curOp.name, curOp.start, curOp.size) << std::endl;
    }
    else if(curOp.cmd == "LIST") {} //List method goes here
    else if(curOp.cmd == "DELETE") {} //Delete method goes here
    else if(curOp.cmd == "SHUTDOWN") {} //SHUTDOWN EVERYTHING
    else {} //signal pid error, bad command
    return true;
}

Inode Controller::createInode(std::string &name) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekp(this->inodeStart);
    
    std::string temp, fakeName(32, 'x');

    Inode inode, replace;
    bool found = false;
    int pos;
    int count = 0;
    do {
        if(!found)
            pos = disk.tellg();

        std::getline(disk, temp, '%');
        std::stringstream s(temp);

        s >> inode.name >> inode.size;

        for(int i = 0; i < 12; i++)
            s >> inode.dbp[i];

        s >> inode.ibp >> inode.dibp;

        if(!found && inode.name == fakeName) {
            replace = inode;
            found = true;
        }
        count++;
    } while(inode.name != name && count < 256);

    std::cout << count << std::endl;

    if(count < 256) {
        disk.close();
        return inode;
    }

    if(found) {
        found = false;
        disk.seekg(pos);

        replace.name = name;

        std::cout << name << std::endl;
        unsigned long long val;
        for(char& c : name) {
            disk << c;
            val = disk.tellg();
            disk.seekg(val);
        }

        for(int i = 0; i < this->bitmap.second && !found; i++) {
            if(!this->bitmap.first[i]) {
                replace.dbp[0] = this->filesStart + (i * this->sb.blockSize);
                this->bitmap.first[i] = true;
                found = true;
            }
        }

        std::getline(disk, temp, ' ');
        std::getline(disk, temp, ' ');

        val = disk.tellg();
        disk.seekg(val);

        disk << replace.dbp[0];

        disk.seekg(pos);
        std::getline(disk, temp, '%');
        std::cout << temp << std::endl;

        disk.close();
        return replace;
    }

    inode.size = -1;

    disk.close();
    return inode;
}   
