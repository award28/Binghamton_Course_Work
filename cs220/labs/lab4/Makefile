all: calc

calc: calc.c  
	gcc -g -Wall -o calc calc.c 
	
	
test: calc
	./calc "4 * 2"
	./calc "3 + 4 * 2"
	./calc "3 + 4 * 2 ; 2 + 5 * 4 ; 25 / ( 3 + 2)"
	./calc "set x 3 + 2; 325 / x"
	./calc "set x 5; while x set x x - 1;"
	./calc "set x 5; set sum 0; while x { set sum sum + x; set x x - 1 }; sum"
	./calc "set x 1; set fact 2; while 1000-fact { set fact fact * x; set x x+1}; fact"
	
clean:
	rm calc
