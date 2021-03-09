all : c28
.PHONY : all

c28 : main.o
	cc -o c28 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c28
