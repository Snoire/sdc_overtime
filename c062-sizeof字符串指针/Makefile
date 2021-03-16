all : c62
.PHONY : all
CFLAGS = -Wall

c62 : main.o strlen.o
	cc -o c62 main.o strlen.o
main.o : main.c
	cc -c main.c -g

clean :
	-rm -f *.o *~ cscope* c62
