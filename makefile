CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS= -pthreads
DISK=ssfs_mkdsk.cpp
SSFS=controller.cpp main.cpp
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
	-rm $(SEX) $(DEX) *.o
