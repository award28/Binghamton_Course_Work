CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS= -pthread

all: run 

run: 
	$(CC) $(LDFLAGS) fig1.c -o fig1
	$(CC) $(LDFLAGS) fig2.c -o fig2
	$(CC) $(LDFLAGS) fig3.c -o fig3
	$(CC) $(LDFLAGS) fig3_poor1.c -o fig3_poor1
	$(CC) $(LDFLAGS) fig3_poor2.c -o fig3_poor2
	$(CC) $(LDFLAGS) pc_v1.c -o pc_v1
	$(CC) $(LDFLAGS) fig6_broken.c -o fig6_broken
	$(CC) $(LDFLAGS) fig8_broken2.c -o fig8_broken2
	$(CC) $(LDFLAGS) fig10_finally.c -o fig10_finally
	$(CC) $(LDFLAGS) fig1112_final.c -o fig1112_final
	$(CC) $(LDFLAGS) fig13_covering.c -o fig13_covering

clean:
	rm fig1 fig2 fig3 fig3_poor1 fig3_poor2 pc_v1 fig6_broken fig8_broken2 fig10_finally fig1112_final fig13_covering

t:
	make
	./fig1
	./fig2
	./fig3
	./fig3_poor1
	./fig3_poor2
	./fig6_broken
	./fig8_broken2
	./fig10_finally
	./fig1112_final
	./fig13_covering
	make clean
	./pc_v1
