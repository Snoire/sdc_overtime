all : c64
.PHONY : all

c64 : main.o
	cc -o c64 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c64
