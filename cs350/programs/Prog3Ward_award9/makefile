CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES= prog3ipc.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=prog3ipc

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
