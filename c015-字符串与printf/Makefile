all : c15
.PHONY : all

c15 : main.o
	cc -o c15 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c15
