all : c62
.PHONY : all

c62 : main.o
	cc -o c62 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c62
