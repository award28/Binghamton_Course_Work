CC=g++-5
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
