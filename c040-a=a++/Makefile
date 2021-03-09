all : c40
.PHONY : all

c40 : main.o
	cc -o c40 main.o
main.o : main.c
	cc -g -c main.c

clean :
	-rm -f *.o *~ cscope* c40
