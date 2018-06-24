CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES= knapsack.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=BestFirstSearch

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
