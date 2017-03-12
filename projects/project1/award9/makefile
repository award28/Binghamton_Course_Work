CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES= tournament.cpp gShare.cpp saturatingBimodal.cpp singleBimodal.cpp taken.cpp notTaken.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=predictors

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
