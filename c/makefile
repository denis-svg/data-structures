exec: stack.o queue.o expression.o 
	g++ -o exec stack.o queue.o expression.o -lm

stack.o: include/stack.c
		g++ -c -o stack.o include/stack.c
queue.o: include/queue.c
	g++ -c -o queue.o include/queue.c
expression.o: expression.c
	g++ -c -o expression.o expression.c

clean:
	rm stack.o queue.o expression.o exec
