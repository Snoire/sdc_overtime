all : c29
.PHONY : all

c29 : main.o
	cc -o c29 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c29
