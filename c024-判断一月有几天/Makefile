all : c24
.PHONY : all

c24 : main.o
	cc -o c24 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c24
