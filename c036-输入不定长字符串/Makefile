all : c36
.PHONY : all

c36 : main.o
	cc -o c36 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c36
