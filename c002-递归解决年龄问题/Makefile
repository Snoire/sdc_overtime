all : c2
.PHONY : all

c2 : main.o
	cc -o c2 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c2
