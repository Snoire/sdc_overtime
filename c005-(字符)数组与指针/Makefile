all : c5
.PHONY : all

c5 : main.o
	cc -o c5 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c5
