all : c34
.PHONY : all

c34 : main.o
	cc -o c34 main.o
main.o : main.c
	cc -g -c main.c -Wall

clean :
	-rm -f *.o *~ cscope* c34
