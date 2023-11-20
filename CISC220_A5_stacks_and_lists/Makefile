# Makefile for Assignment 5
list_test : list_test.c list_utils.o list.o
	gcc -o list_test list_test.c list_utils.o list.o

stack_test : stack_test.c stack_utils.o stack.o
	gcc -o stack_test stack_test.c stack_utils.o stack.o

list_utils.o : list_utils.h list_utils.c
	gcc -c list_utils.c

stack_utils.o : stack_utils.h stack_utils.c
	gcc -c stack_utils.c

list.o : list.c list.h
	gcc -c list.c

stack.o : stack.c stack.h
	gcc -c stack.c

clean :
	rm *.o