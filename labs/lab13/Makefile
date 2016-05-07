SHELL=/bin/tcsh

all: sequential parallel

sequential : sequential.c search.h search.c
	gcc -g -Wall -m32 -o sequential sequential.c search.c
	
parallel : parallel.c search.h search.c
	gcc -g -Wall -m32 -o parallel parallel.c search.c
	
test: sequential parallel
	time ./sequential file1.txt those file1.txt these file1.txt them file2.txt these file3.txt them 
	time ./parallel      file1.txt those file1.txt these file1.txt them file2.txt these file3.txt them
		
clean:
	-rm sequential parallel
