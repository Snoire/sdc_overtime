all : c12
.PHONY : all

c12 : main.o
	cc -o c12 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c12
