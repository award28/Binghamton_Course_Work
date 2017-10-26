CFLAGS=-g -Wall -Wextra -std=c11
ARFLAGS=rcs
SOURCES=bitmap.c memory_manager.c
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
TEST_OBJECTS=$(OBJECTS) test_main.o
HEADERS=common.h interposition.h memory_manager.h
TARGET=test_mem_mngr
CC=gcc


all: memory_manager.a $(TARGET)

$(TARGET): $(TEST_OBJECTS)
	$(CC) -O2 $(CFLAGS) -o $@ $^

$(OBJECTS): $(HEADERS)
	$(CC) -O2 $(CFLAGS) -c $*.c

memory_manager.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

%.o:%.c
	$(CC) -static $(CFLAGS) -c -o $@ $<

clean:
	-rm $(TARGET) memory_manager.a *.o
