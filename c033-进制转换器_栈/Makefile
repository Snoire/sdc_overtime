all : c33
.PHONY : all

c33 : main.o
	cc -o c33 main.o -Wall -lm
main.o : main.c
	cc -c main.c -Wall

clean :
	-rm -f *.o *~ cscope* c33
