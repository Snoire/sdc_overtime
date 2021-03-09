all : c76
.PHONY : all

c76 : main.o
	cc -o c76 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c76
