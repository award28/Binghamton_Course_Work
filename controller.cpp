#include <fstream>
#include <sstream>
#include <string>

#include "ssfs.hpp"

using std::string;

Controller::Controller(std::string &disk, std::queue<op> *buffer) {
    string temp;

    this->shutdown = false;
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

bool Controller::execute() {
    op curOp = buffer->front();
    buffer->pop();

    string out;
    // std::cout << curOp.cmd << std::endl;
    out += curOp.cmd + "\n";
    if(curOp.cmd == "CREATE" || curOp.cmd == "IMPORT" || curOp.cmd == "WRITE")
        write(curOp.name, curOp.start, curOp.size, curOp.data); 
    else if(curOp.cmd == "READ") {
        // std::cout << read(curOp.name, curOp.start, curOp.size) << std::endl;
        out += read(curOp.name, curOp.start, curOp.size) + "\n";
    }
    else if(curOp.cmd == "CAT") {
        // std::cout << cat(curOp.name) << std::endl;
        out += cat(curOp.name) + "\n";
    }
    else if(curOp.cmd == "LIST") {
        // std::cout << list() << std::endl;
        out += list() + "\n";
    } 
    else if(curOp.cmd == "DELETE") {
        if(deleteFile(curOp.name))
            // std::cout << "Success: File deleted." << std::endl;
            out += "Success: File deleted.\n";
        else
            // std::cout << "Error: File " << curOp.name << " could not be found." << std::endl;
            out += "Error: File " + curOp.name + " could not be found.\n";
        
    } //Delete method goes here
    else if(curOp.cmd == "SHUTDOWN") {
        shutdown = true;
    } //SHUTDOWN EVERYTHING
    else {} //signal pid error, bad command
    // std::cout << "controller out: " << out << std::endl;
    *curOp.response = out;
    if (shutdown) *curOp.response = "exit";
    pthread_cond_signal(curOp.cond);
    return shutdown;
}

std::string Controller::read(std::string &name, int start, int size) {
    InodeData inodeData = findInode(name);
    Inode inode = inodeData.first;
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    std::vector<int> posArr = posArray(inode);
    char *data;
    string content = "";
    int bytesLeft;

    if(size - start > inode.size) 
        bytesLeft = inode.size - start;
    else
        bytesLeft = size - start;

    int index = floor(start/128);
    int offset = start % 128;

    if(index)
        posArr.erase(posArr.begin(), posArr.begin() + index);

    data = new char[128];

    disk.seekp(posArr.front() + offset);
    posArr.erase(posArr.begin());

    if(bytesLeft > 128) {
        disk.read(data, 128);
        bytesLeft -= 128;
        content += data;

        for(auto pos : posArr) {
            disk.seekp(pos);
            if(bytesLeft > 128) {
                disk.read(data, 128);
                bytesLeft -= 128;
            }
            else
                disk.read(data, bytesLeft);
            content += data;
        }
    }
    else {
        disk.read(data, bytesLeft);
        content += data;
    }

    disk.close();

    return std::string(content);
}

bool Controller::write(std::string &name, int start, int size, std::string &data) {
    bool finished = false;
    int available = 0;
    int bytesLeft;

    for(int i = 0; i < this->bitmap.second; i++) {
        if(!this->bitmap.first[i])
            available += this->sb.blockSize;
    }

    if(available < size - start)
        return false;

    InodeData inodeData = createInode(name);
    Inode inode = inodeData.first;
    int pos = inodeData.second;
    int dataLeft = data.length();
    
    if(inode.size == -1)
        return false;
    
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    disk.seekp(inode.dbp[0] + start);

    for(int j = 0; j < this->sb.blockSize && dataLeft--; j++) {
        disk << data[j];
        disk.seekg(disk.tellg());
    }

    for(int i = 1; i < 12 && dataLeft; i++) {
        inode.dbp[i] = findFreePos();
        disk.seekp(inode.dbp[i]);
        for(int j = 0; j < this->sb.blockSize && dataLeft--; j++) {
        disk << data[j];
        disk.seekg(disk.tellg());
        }
   }

    inode.size = size;

    disk.close();
    updateInode(inode, pos);
    return true;
}

std::string Controller::cat(std::string &name) {
    InodeData inodeData = findInode(name);
    Inode inode = inodeData.first;

    if(inode.size == -1)
        return "Error: No file with name " + name + " found.";

    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    char *data = new char[inode.size];

    disk.seekp(inode.dbp[0]);
    disk.read(data, inode.size);
    disk.close();

    return std::string(data);
}

bool Controller::import(std::string &name, std::string &file) {
    std::ifstream fin(file);

    if(!fin.good())
        return false;
    std::string contents {std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>()};
    fin.close();

    write(name, 0, contents.length(), contents);

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
            std::stringstream sizeStream(temp);
            getline(sizeStream, temp, 'x');
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

InodeData Controller::findInode(std::string &name) {
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
        std::stringstream sizeStream(temp);
        getline(sizeStream, temp, 'x');
        inode.size = std::stoi(temp);

        for(int i = 0; i < 12; i++) {
            getline(s, temp, '\0');
            sizeStream.str(temp);
            getline(sizeStream, temp, 'x');
            inode.dbp[i] = std::stoi(temp);
        }

        getline(s, temp, '\0');
        sizeStream.str(temp);
        getline(sizeStream, temp, 'x');
        inode.ibp = std::stoi(temp);
        getline(s, temp, '\0');
        sizeStream.str(temp);
        getline(sizeStream, temp, 'x');
        inode.dibp = std::stoi(temp);

        count++;
    } while(inode.name != name && count < 256);

    if(count < 256) {
        disk.close();
        return std::make_pair(inode, pos);
    }

    inode.size = -1;

    disk.close();
    return std::make_pair(inode, pos);
}

void Controller::updateInode(Inode inode, int pos) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekg(pos);

    unsigned long long val;
    string temp;

    std::getline(disk, temp, '\0');
    val = disk.tellg();
    disk.seekg(val);
    disk << inode.size;

    disk.seekg(pos);

    std::getline(disk, temp, '\0');
    val = disk.tellg();
    disk.seekg(val);
    std::getline(disk, temp, '\0');


    std::getline(disk, temp, '%');

    disk.close();
}

bool Controller::deleteFile(std::string &name) {
    InodeData inodeData = findInode(name);
    Inode inode = inodeData.first;
    int pos = inodeData.second;

    if(inode.size == -1)
        return false;

    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary );
    disk.seekp(pos);

    std::string fakeName(33, 'x'), fakeNum(10, 'x');
    fakeNum[0] = '0';

    for(int i = 0; i < 12; i++)
        if(inode.dbp[i])
            this->bitmap.first[(inode.dbp[i] - this->filesStart)/this->sb.blockSize] = false;
    /*
    if(inode.ibp)
        this->bitmap.first[(inode.ibp - this->fileStart)/this->sb.blockSize] = false;
    if(inode.dibp)
        this->bitmap.first[(inode.dibp - this->fileStart)/this->sb.blockSize] = false;
        */

    disk.seekg(pos);

    unsigned long long val;
    for(char& c : fakeName) {
        disk << c;
        val = disk.tellg();
        disk.seekg(val);
    }
    
    //Delete inode numbers
    for(int i = 0; i < 15; i++) {
        disk << '\0';
        val = disk.tellg();
        disk.seekg(val);
        for(char& c : fakeNum) {
            disk << c;
            val = disk.tellg();
            disk.seekg(val);
        }
    }

    disk.close();
    return true;
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
        std::stringstream sizeStream(temp);
        getline(sizeStream, temp, 'x');
        inode.size = std::stoi(temp);

        for(int i = 0; i < 12; i++) {
            getline(s, temp, '\0');
            sizeStream.str(temp);
            getline(sizeStream, temp, 'x');
            inode.dbp[i] = std::stoi(temp);
        }

        getline(s, temp, '\0');
        sizeStream.str(temp);
        getline(sizeStream, temp, 'x');
        inode.ibp = std::stoi(temp);
        getline(s, temp, '\0');
        sizeStream.str(temp);
        getline(sizeStream, temp, 'x');
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

std::vector<int> Controller::posArray(Inode inode) {
    std::vector<int> arr, ibp, dibp;
    for(int i = 0; i < 12; i++)
        if(inode.dbp[i])
            arr.push_back(inode.dbp[i]);

    //ibp = ibpArray(inode.ibp);
    return arr;
}

std::vector<int> Controller::ibpArray(int ibp) {
    std::fstream disk(this->disk, std::fstream::in | std::fstream::out | std::fstream::binary);
    disk.seekg(ibp);
    std::string temp;
    std::vector<int> resArr;

    std::getline(disk, temp, '%');
    std::stringstream s(temp);

    getline(s, temp, '\0');
    std::stringstream sizeStream(temp);
    getline(sizeStream, temp, 'x');
    resArr.push_back(std::stoi(temp));

    for(int i = 0; i < floor(this->sb.blockSize/11); i++) {
        getline(s, temp, '\0');
        sizeStream.str(temp);
        getline(sizeStream, temp, 'x');
        resArr.push_back(std::stoi(temp));
    }

    disk.close();
    return resArr;
}

int Controller::findFreePos() {
    bool found = false;
    int ret;

    for(int i = 0; i < this->bitmap.second && !found; i++) {
        if(!this->bitmap.first[i]) {
            ret = this->filesStart + (i * this->sb.blockSize);
            this->bitmap.first[i] = true;
            found = true;
        }
    }

    return ret;
}
