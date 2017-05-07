#include <fstream>
#include <sstream>
#include <string>

#include "ssfs.hpp"

using std::string;

Controller::Controller(std::string &disk, std::queue<op> *buffer) {
    string temp;

    this->disk = disk;
    this->buffer = buffer;

    char delimeter('#');

    std::fstream tdisk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    std::string superBlock;
    std::getline(tdisk, superBlock, delimeter);
    std::stringstream s(superBlock);

    getline(s, temp, '\0');
    this->sb.numBlocks = std::stoi(temp);
    getline(s, temp, '\0');
    this->sb.blockSize = std::stoi(temp);

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
    Inode inode = findInode(name);
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    char *data = new char[size];

    disk.seekp(inode.dbp[0] + start);
    disk.read(data, size);
    disk.close();

    return std::string(data);
}

bool Controller::write(std::string &name, int start, int size, std::string &data) {
    InodeData inodeData = createInode(name);
    Inode inode = inodeData.first;
    int pos = inodeData.second;

    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    disk.seekp(inode.dbp[0] + start);

    for(int i = 0; i < size;) {
        for(int j = 0; j < data.length() && i < size; j++, i++) {
            disk << data[j];
            disk.seekg(disk.tellg());
        }
    }

    inode.size = size;

    disk.close();
    updateInode(inode, pos);
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
    else if(curOp.cmd == "LIST") {
        std::cout << list() << std::endl;
    } 
    else if(curOp.cmd == "DELETE") {} //Delete method goes here
    else if(curOp.cmd == "SHUTDOWN") {} //SHUTDOWN EVERYTHING
    else {} //signal pid error, bad command
    return true;
}

std::string Controller::list() {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekp(this->inodeStart);

    std::string retVal, temp, fakeName(33, 'x');
    int count = 0;
    do {
        std::getline(disk, temp, '%');
        std::stringstream s(temp);
        
        getline(s, temp, '\0');
        std::stringstream nameStream(temp);
        getline(nameStream, temp, ' ');
         if(temp != fakeName) {
            retVal.append(temp);
            getline(s, temp, '\0');
            retVal.append(" " + temp + '\n');
         }
         else 
             getline(s, temp, '\0');

        for(int i = 0; i < 12; i++)
            getline(s, temp, '\0');

        getline(s, temp, '\0');
        getline(s, temp, '\0');

        count++;
    } while(count < 256);

    disk.close();
    return retVal;
}

Inode Controller::findInode(std::string &name) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekp(this->inodeStart);

    std::string temp; 
    Inode inode;
    bool found = false;
    int pos;
    int count = 0;
    do {
        if(!found)
            pos = disk.tellg();

        std::getline(disk, temp, '%');
        std::stringstream s(temp);
        
        getline(s, temp, '\0');
        std::stringstream nameStream(temp);
        getline(nameStream, temp, ' ');
        inode.name = temp;
        getline(s, temp, '\0');
        getline(s, temp, '\0');
        inode.size = std::stoi(temp);

        for(int i = 0; i < 12; i++) {
            getline(s, temp, '\0');
            inode.dbp[i] = std::stoi(temp);
        }

        getline(s, temp, '\0');
        inode.ibp = std::stoi(temp);
        getline(s, temp, '\0');
        inode.dibp = std::stoi(temp);

        count++;
    } while(inode.name != name && count < 256);

    if(count < 256) {
        disk.close();
        return inode;
    }

    inode.size = -1;

    disk.close();
    return inode;
}

void Controller::updateInode(Inode inode, int pos) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekg(pos);

    unsigned long long val;
    string temp;

    std::getline(disk, temp, '\0');
    val = disk.tellg();
    disk.seekg(val);
    std::cout << inode.size << std::endl;
    disk << inode.size;

    disk.seekg(pos);

    std::getline(disk, temp, '\0');
    val = disk.tellg();
    disk.seekg(val);
    std::getline(disk, temp, '\0');
    std::cout << temp << std::endl;


    std::getline(disk, temp, '%');

    disk.close();
}
InodeData Controller::createInode(std::string &name) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekp(this->inodeStart);
    
    std::string temp, fakeName(33, 'x');

    Inode inode, replace;
    bool found = false;
    int pos, newPos;
    int count = 0;
    do {
        if(!found)
            newPos = disk.tellg();
        pos = disk.tellg();

        std::getline(disk, temp, '%');
        std::stringstream s(temp);
        
        getline(s, temp, '\0');
        std::stringstream nameStream(temp);
        getline(nameStream, temp, ' ');
        inode.name = temp;
        getline(s, temp, '\0');
        inode.size = std::stoi(temp);

        for(int i = 0; i < 12; i++) {
            getline(s, temp, '\0');
            inode.dbp[i] = std::stoi(temp);
        }

        getline(s, temp, '\0');
        inode.ibp = std::stoi(temp);
        getline(s, temp, '\0');
        inode.dibp = std::stoi(temp);

        if(!found && inode.name == fakeName) {
            replace = inode;
            found = true;
        }
        count++;
    } while(inode.name != name && count < 256);

    if(count < 256) {
        disk.close();
        return std::make_pair(inode, pos);
    }

    if(found) {
        found = false;
        disk.seekg(newPos);

        replace.name = name;

        unsigned long long val;
        int nameSize = 33;
        for(char& c : name) {
            disk << c;
            val = disk.tellg();
            disk.seekg(val);
            nameSize--;
        }
        while(nameSize--){
            disk << ' ';
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

        std::getline(disk, temp, '\0');
        std::getline(disk, temp, '\0');

        val = disk.tellg();
        disk.seekg(val);

        disk << replace.dbp[0];

        disk.seekg(newPos);
        std::getline(disk, temp, '%');

        disk.close();
        return std::make_pair(replace, newPos);
    }

    inode.size = -1;

    disk.close();
    return std::make_pair(inode, pos);
}   
