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
	-rm $(SEX) $(DEX) *.o

test: $(DEX) $(SEX)
	@echo 'making disk....'
	./ssfs_mkdsk 1024 256
	@echo 'running....'
	./ssfs DISK test
	@echo 'clean'
	@rm -f DISK
	clean
