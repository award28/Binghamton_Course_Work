CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES= state.cpp transition.cpp transitionList.cpp Configuration.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ward_p1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
