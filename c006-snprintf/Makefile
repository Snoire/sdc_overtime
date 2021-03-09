all : c6
.PHONY : all

c6 : main.o
	cc -o c6 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c6
