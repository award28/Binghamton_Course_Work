all: lab3

lab3: lab3.o MovieChart
	g++ lab3.o MovieChart.o -o lab3

MovieChart: MovieChart.cpp MovieChart.h  User.h
	g++ -c MovieChart.cpp

lab3.o: lab3.cpp MovieChart.h 
	g++ -c lab3.cpp

clean:
	rm -f *.o lab3
