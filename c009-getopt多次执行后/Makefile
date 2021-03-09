all : c9
.PHONY : all

c9 : main.o
	cc -o c9 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c9
