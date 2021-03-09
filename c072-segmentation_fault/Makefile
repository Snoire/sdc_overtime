all : c72
.PHONY : all

c72 : main.o
	cc -o c72 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c72
