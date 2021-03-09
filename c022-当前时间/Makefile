all : c22
.PHONY : all

c22 : main.o
	cc -o c22 main.o -Wall -Werror
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c22
