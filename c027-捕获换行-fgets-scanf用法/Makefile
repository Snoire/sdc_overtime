all : c27
.PHONY : all

c27 : main.o
	cc -o c27 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c27
