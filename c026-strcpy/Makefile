all : c26
.PHONY : all

c26 : main.o
	cc -o c26 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c26
