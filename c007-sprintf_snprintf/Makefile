all : c7
.PHONY : all

c7 : main.o
	cc -o c7 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c7
