CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES=Deck.cpp lab5.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab5

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
