all : c30
.PHONY : all

c30 : main.o
	cc -o c30 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c30
