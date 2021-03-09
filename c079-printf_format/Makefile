all : c79
.PHONY : all

c79 : main.o
	cc -o c79 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c79
