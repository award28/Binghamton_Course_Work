CFLAGS=-g -Wall -Wextra -std=c11
HEADERS=hw1.h 
SOURCES=test_main.c hw1_str.c hw1_myprintf.c
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))
TARGET=hw1
CC=gcc

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -O2 $(CFLAGS) -o $@ $^

$(OBJECTS): $(HEADERS)
	$(CC) -O2 $(CFLAGS) -c $*.c

test:
	make clean && make && ./hw1

clean:
	-rm $(TARGET) *.o
