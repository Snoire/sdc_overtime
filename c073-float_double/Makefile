all : c73
.PHONY : all

c73 : main.o
	cc -o c73 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c73
