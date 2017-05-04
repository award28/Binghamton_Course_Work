#ifndef SSFS_HPP
#define SSFS_HPP
#include <iostream>

struct SuperBlock {  
    int dataBlocks;
    int numInodes;
};

class Controller {
    public:
        char* read();
        bool write(char data[]);
    private:
        bool bitmap[256] = {false};
        bool inodeTable[256] = {false};
};

#endif
