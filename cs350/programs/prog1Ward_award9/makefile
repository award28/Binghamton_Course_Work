CC= gcc
CFLAGS= -o -g -Wall
LDFLAGS=
SORT= prog1sorter.c
GENERATOR= prog1generator.c
SORTOBJ= $(SORT:.c=.o)
GENOBJ= $(GENERATOR:.c=.o)
EXSORT= prog1sorter
EXGEN= prog1generator

all: $(EXSORT) $(EXGEN) 

$(EXSORT): $(SORTOBJ)
	$(CC) $(LDFLAGS) $(SORTOBJ) -o $@

$(EXGEN): $(GENOBJ)
	$(CC) $(LDFLAGS) $(GENOBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXSORT) $(EXGEN) *.o
