#include <iostream>
#include <fstream>

#include "ssfs.hpp" 

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]){
	int x, numBlocks, blockSize;
	char* fileName;
	
	if(argc > 4 || argc < 3){
		cout << "Usage: " << argv[0] << " <num blocks> <block size> <disk file name>" << endl;
		exit(1);
	}

	numBlocks = atoi(argv[1]);
	blockSize = atoi(argv[2]);

	if(argc == 4){
		fileName = argv[3];
	}else{
		fileName = (char *)"DISK";
	}

	if(numBlocks < 1024 || numBlocks > 131072){
		cout << "Num Blocks must be between 1024 and 131072 inclusive." << endl;
		exit(1);
	}
	if(blockSize < 128 || blockSize > 512){
		cout << "Block size must be between 128 and 512 inclusive." << endl;
		exit(1);
	}
	if((blockSize & (blockSize - 1)) != 0 || (numBlocks & (numBlocks - 1)) != 0){
		cout << "Block size and num blocks must be powers of 2" << endl;
		exit(1);
	}

	x = (numBlocks * blockSize) - 1;

    std::ofstream fp;
	fp.open(fileName);
	fp.seekp(x);
	fp << '\0';

    fp.seekp(0);
    
    fp << numBlocks << " " << blockSize << "#";

    Inode temp;

    for(int i = 0; i < 32; i++)
        temp.name += "x";

    temp.size = 0;
    for(int i = 0; i < 12; i++)
        temp.dbp[i] = 0;

    for(int i = 0; i < 256; i++) {
        fp << temp.name << " " << temp.size;
        for(int j = 0; j < 35; j++)
            fp << " " << temp.dbp[i % 12];
        fp << "%";
    }
    fp << '#';
        
	fp.close();	

    return 0;
}
