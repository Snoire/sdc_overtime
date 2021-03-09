all : c61
.PHONY : all

c61 : main.o
	cc -o c61 main.o
main.o : main.c
	cc -c main.c

clean :
	-rm -f *.o *~ cscope* c61
