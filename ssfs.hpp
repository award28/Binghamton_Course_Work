#ifndef SSFS_HPP
#define SSFS_HPP
#include <iostream>

struct SuperBlock {  
    int dataBlocks;
    int numInodes;
};

class Controller {
    public:
        Controller(char disk[]);
        char* read();
        bool write(char data[]);
    private:
        char* disk;
};

#endif
