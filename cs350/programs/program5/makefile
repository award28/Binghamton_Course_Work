CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS= -lpthread
DISK=ssfs_mkdsk.cpp
SSFS=controller.cpp disk_op.cpp main.cpp
DOBJECTS=$(DISK:.cpp=.o)
SOBJECTS=$(SSFS:.cpp=.o)
DEX=ssfs_mkdsk
SEX=ssfs

all: $(SSFS) $(SEX) $(DISK) $(DEX)
$(SEX): $(SOBJECTS)
	$(CC) $(LDFLAGS) $(SOBJECTS) -o $@

$(DEX): $(DOBJECTS)
	$(CC) $(LDFLAGS) $(DOBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(SEX) $(DEX) *.o DISK

test: $(DEX) $(SEX)
	./ssfs_mkdsk 1024 128
	./ssfs DISK test
	make clean
