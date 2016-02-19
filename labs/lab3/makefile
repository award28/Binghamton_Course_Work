all: lab3

lab3: lab3.o User.o
	g++ lab3.o User.o -o lab3

User: User.cpp
	g++ -c User.cpp

lab3.o: lab3.cpp
	g++ -c lab3.cpp

clean:
	rm -f *.o lab3
