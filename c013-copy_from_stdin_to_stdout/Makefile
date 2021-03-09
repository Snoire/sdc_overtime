all : c13
.PHONY : all

c13 : main.o
	cc -o c13 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c13
