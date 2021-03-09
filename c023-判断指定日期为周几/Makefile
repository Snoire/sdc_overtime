all : c23
.PHONY : all

c23 : main.o
	cc -o c23 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c23
