CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES= prog2tree.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=prog2tree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
