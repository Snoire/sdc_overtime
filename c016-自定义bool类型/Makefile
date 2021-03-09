all : c16
.PHONY : all

c16 : main.o
	cc -o c16 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c16
