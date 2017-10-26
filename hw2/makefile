CFLAGS=-g -std=c11 -Wall -Wextra -Werror
CC=gcc

all: switch_column dir_stat oz_demo

switch_column: switch_column.c
	$(CC) $(CFLAGS) -o switch_column switch_column.c

dir_stat: dir_stat.c
	$(CC) $(CFLAGS) -o dir_stat dir_stat.c

oz_demo: oz_demo.c
	$(CC) $(CFLAGS) -o oz_demo oz_demo.c

clean:
	rm -rf *.dSYM oz_demo dir_stat switch_column 
