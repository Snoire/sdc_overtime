all : c10
.PHONY : all

c10 : main.o
	cc -o c10 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c10
