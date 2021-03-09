all : c8
.PHONY : all

c8 : main.o
	cc -o c8 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c8
