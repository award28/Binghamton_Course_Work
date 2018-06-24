CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES=clock.cpp lru.cpp opt.cpp rand.cpp fifo.cpp prog4pages.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=prog4pages

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
