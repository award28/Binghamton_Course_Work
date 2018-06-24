CXXFLAGS=-g -Wall -Wextra -pedantic -std=c++14
SRCEXT=cpp
HEADEREXT=hpp
LDFLAGS=-ldl -pthread
SOURCES=$(shell find . -type f -name "*.$(SRCEXT)")
OBJECTS=$(patsubst %.$(SRCEXT),%.o,$(SOURCES))
HEADERS=$(shell find . -type f -name "*.$(HEADEREXT)")
EXECUTABLE=FuncWrapper
RUN=./$(EXECUTABLE)
RUNV=valgrind --leak-check=full --track-origins=yes $(RUN)
RUNS=perf stat $(RUN)

all: $(EXECUTABLE)

full: 
	make lint && make test && make

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o:%.$(SRCEXT)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	-rm $(EXECUTABLE) src/*.o

clean-swap:
	-rm src/.*.swp src/.nfs*

test: all
	$(RUN)

valgrind: all
	$(RUNV)

bench: all
	$(RUNS)

lint: $(SOURCES) $(HEADERS)
	cpplint $^

.PHONY: clean
