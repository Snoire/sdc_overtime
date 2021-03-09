all : c32
.PHONY : all

c32 : main.o
	cc -o c32 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c32
