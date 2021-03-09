all : c4
.PHONY : all

c4 : main.o
	cc -o c4 main.o
main.o : main.c
	cc -g -c main.c

clean :
	-rm -f *.o *~ cscope* c4
