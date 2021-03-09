all : c39
.PHONY : all

c39 : main.o
	cc -o c39 main.o
main.o : main.c
	cc -g -c main.c

clean :
	-rm -f *.o *~ cscope* c39
