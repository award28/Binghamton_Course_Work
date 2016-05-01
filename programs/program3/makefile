CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES= Map.cpp City.cpp program3.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program3

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
