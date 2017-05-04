#include <iostream>
#include <fstream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]){
	FILE *fp;
	int x, numBlocks, blockSize;
	char* fileName;
	
	if(argc > 4 || argc < 3){
		cout << "Usage: ./" << args[0] << " <num blocks> <block size> <disk file name>" << endl;
		exit(1);
	}

	numBlocks = atoi(argv[1]);
	blockSize = atoi(argv[2]);
	if(argc == 4){
		fileName = argv[3];
	}else{
		fileName = "DISK";
	}

	if(numBlocks < 1024 || numBlocks > 131072){
		cout << "Num Blocks must be between 1024 and 128000 inclusive." << endl;
		exit(1);
	}
	if(blockSize < 128 || blockSize > 512){
		cout << "Block size must be between 128 and 512 inclusive." << endl;
		exit(1);
	}
	if(blockSize & (blockSize - 1) != 0 || numBlocks & (numBlocks - 1) != 0){
		cout << "Block size and num blocks must be powers of 2" << endl;
		exit(1);
	}

	x = numBlocks * blockSize - 1;

    ofstream fp;
	fp.open(fileName, "wb");
	fp.seekp(x);
	fp << '\0';
	fp.close();	
}
