CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES= Heap.cpp Player.cpp program2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
