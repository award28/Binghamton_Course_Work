CFLAGS=-g -Wall -Wextra -std=c11
ARFLAGS=rcs
SOURCES=bitmap.c memory_manager.c
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
CC=gcc


all: memory_manager.a

memory_manager.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

%.o:%.c
	$(CC) -static $(CFLAGS) -c -o $@ $<

clean:
	-rm $(TARGET) memory_manager.a *.o
