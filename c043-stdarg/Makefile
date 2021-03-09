all : c43
.PHONY : all

c43 : main.o
	cc -o c43 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c43
