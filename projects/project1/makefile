CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES=MovieChart.cpp program1.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
