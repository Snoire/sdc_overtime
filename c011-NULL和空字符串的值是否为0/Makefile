all : c11
.PHONY : all

c11 : main.o
	cc -o c11 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c11
