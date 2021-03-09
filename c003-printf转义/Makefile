#注释

all : c3
.PHONY : all

c3 : main.o
	cc -o c3 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c3
