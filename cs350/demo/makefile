CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES= demo.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=demo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
