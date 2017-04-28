#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]){
	FILE *fp;
	int x, numBlocks, blockSize;
	char* fileName;
	
	if(argc > 4 || argc < 3){
		printf("Usage: ./%s <num blocks> <block size> <disk file name>\n", argv[0]);
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
		printf("Num Blocks must be between 1024 and 128000 inclusive.\n");	
		exit(1);
	}
	if(blockSize < 128 || blockSize > 512){
		printf("Block size must be between 128 and 512 inclusive.\n");	
		exit(1);
	}
	if(blockSize & (blockSize - 1) != 0 || numBlocks & (numBlocks - 1) != 0){
		printf("Block size and num blocks must be powers of 2\n");
		exit(1);
	}

	x = numBlocks * blockSize - 1;

	fp = fopen(fileName, "wb");
	fseek(fp, x, SEEK_SET);
	fputc('\0', fp);
	fclose(fp);	
}
