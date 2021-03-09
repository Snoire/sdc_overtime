

all : c20
.PHONY : all

c20 : main.o
	cc -o c20 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c20
