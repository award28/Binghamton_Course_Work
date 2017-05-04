CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES=ssfs_mkdsk.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ssfs

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o

t:
	make
	./$(EXECUTABLE)
	make clean
