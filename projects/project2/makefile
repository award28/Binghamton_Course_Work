CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=
SOURCES= main.cpp dMapped.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cache-sim

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE) *.o
test: all
	./cache-sim ./traces/trace1.txt out.txt
	diff out.txt ./correct_outputs/trace1_output.txt
	./cache-sim ./traces/trace2.txt out.txt
	diff out.txt ./correct_outputs/trace2_output.txt
	./cache-sim ./traces/trace3.txt out.txt
	diff out.txt ./correct_outputs/trace3_output.txt
