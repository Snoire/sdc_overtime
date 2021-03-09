all : c55
.PHONY : all

c55 : main.o
	cc -o c55 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c55
