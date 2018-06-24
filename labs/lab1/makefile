all: lab1

lab1: lab1.o Hello.o
	g++ lab1.o Hello.o -o lab1

Hello.o: Hello.cpp
	g++ -c Hello.cpp

lab1.o: lab1.cpp
	g++ -c lab1.cpp

clean:
	rm -f *.o lab1 Hello
