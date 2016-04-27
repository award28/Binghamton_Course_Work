CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES=Sort.cpp lab8.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab8

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
