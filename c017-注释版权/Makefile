all : c17
.PHONY : all

c17 : main.o
	cc -o c17 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c17
