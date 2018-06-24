all: printStack
.PHONY: clean test



printStack: fact.c printStack.h printStack.c
	gcc -g -m32 -oprintStack fact.c printStack.c
	
test: printStack
	./printStack >log.txt;
	
printStack.lst : printStack.c
	gcc -c -Wa,-a,-ad printStack.c > printStack.lst
	
clean:
	-rm printStack printStack.lst log.txt
